/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH & AntelliJ
 * Version            : V1.0.0
 * Date               : 2026/11/11
 * Description        : Main program body. Should do a CharliePlex setup
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *Multiprocessor communication mode routine:
 *Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 *This routine demonstrates that USART1 receives the data sent by CH341 and inverts
 *it and sends it (baud rate 115200).
 *
 *Hardware connection:PD5 -- Rx
 *                     PD6 -- Tx
 *
 */

#include "debug.h"
#include <stdint.h>


/* Global define */
// Charlieplexing
#define LED_COUNT 8U
#define SCAN_SLOT_US 300U
#define CHASE_INTERVAL_US 150000U

#define CHASE_RUNS 5U
#define RAINBOW_CYCLES 3U

// pwm timing
#define RGB_PWM_SLOT_US 10U

// 0 or 1 to repeat infinitely
// #define REPEAT_SEQUENCE 1U

// Charlieplexing pins - GPIOD
#define PLEX_LINE_MASK (GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4)

#define LED_MASK ((uint8_t)((1U << LED_COUNT) - 1U))

// RGB PINS on GPIOC
#define RGB_R_PIN GPIO_Pin_5
#define RGB_G_PIN GPIO_Pin_4
#define RGB_B_PIN GPIO_Pin_3

#define RGB_MASK (RGB_R_PIN | RGB_G_PIN | RGB_B_PIN)


// buzzer?
#define BUZZER_PIN GPIO_Pin_0


/* Global Variable */
// Charlieplex hardware vals
typedef enum {
    LINE_A = 0,
    LINE_B,
    LINE_C,
    LINE_D,
    LINE_COUNT
} Line;

// line x gpio assignment
// apparently d 5 and 6 is used for uart so good thing I didn't use that
static const uint16_t line_pins[LINE_COUNT] = {
    GPIO_Pin_0, // A - PD0
    GPIO_Pin_2, // B
    GPIO_Pin_3, // C
    GPIO_Pin_4, // D - PD4
};


typedef enum {
    LED_D8 = 0,
    LED_D9,
    LED_D1,
    LED_D3,
    LED_D6,
    LED_D10,
    LED_D4,
    LED_D5,
} LedID;

// Each led needs to know its anode and cathode lines
typedef struct {
    Line anode;
    Line cathode;
} LedDefinition;

// table for led configs
static const LedDefinition leds[LED_COUNT] = {
    {LINE_A, LINE_B},
    {LINE_B, LINE_A},

    {LINE_B, LINE_C},
    {LINE_C, LINE_B},

    {LINE_A,LINE_C},
    {LINE_C,LINE_A},

    {LINE_C,LINE_D},
    {LINE_D,LINE_C},
};

// SETUP GPIO
static void Hardware_init(void) {
    GPIO_InitTypeDef gpio = {0};

    // enable gpio clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);

    // set rgb high (off state)
    GPIO_SetBits(GPIOC, RGB_MASK);

    // set buzzer
    GPIO_ResetBits(GPIOC, BUZZER_PIN);

    // configure rgb and buzzer
    gpio.GPIO_Pin = RGB_MASK | BUZZER_PIN;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_30MHz;

    GPIO_Init(GPIOC, &gpio);
    
}


// setting gpio pins to high impedence should make it better for the lines to be controlled externally  
static void Lines_HighZ(void) {
    GPIO_InitTypeDef gpio = {
        PLEX_LINE_MASK,
        GPIO_Speed_30MHz, // idk if can get away with less for less current draw?
        GPIO_Mode_IN_FLOATING
    };

    GPIO_Init(GPIOD, &gpio);
}

// turn on an led
static void LED_ON(uint8_t led_id) {
    if (led_id >= LED_COUNT) return;
    uint16_t anode_pin = line_pins[leds[led_id].anode];
    uint16_t cathode_pin = line_pins[leds[led_id].cathode];

    // disconnect all charlieplexed lines
    Lines_HighZ();

    GPIO_SetBits(GPIOD, anode_pin);
    GPIO_ResetBits(GPIOD, cathode_pin);

    GPIO_InitTypeDef gpio = {0};
    
    gpio.GPIO_Pin = anode_pin | cathode_pin;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_30MHz;

    GPIO_Init(GPIOD, &gpio);
}

// turn off all leds
static void LED_AllOff(void) {
    Lines_HighZ();
}

// LED SCANNER
// 
// use bitmask to select multiple LEDs, the scanner cycles through them
static void LED_ScanStep(uint8_t frame, uint8_t *cursor) {
    if (frame == 0) {
        LED_AllOff();
        Delay_Us(SCAN_SLOT_US);
        return;
    }

    // find which LED should be on next
    for (uint8_t i=0; i < LED_COUNT; i++) {
        uint8_t led = *cursor;

        *cursor = (uint8_t)((*cursor + 1U) % LED_COUNT);

        if (frame & (uint8_t)(1U<<led)) {
            LED_ON(led);

            Delay_Us(SCAN_SLOT_US);

            LED_AllOff();

            return;
        }
    }

    LED_AllOff();
    Delay_Us(SCAN_SLOT_US);
}


// Animation Framework
// animation tells what led should be on at a certain point in time
typedef uint8_t (*AnimationFunction) (
    void *state,
    uint32_t elapsed_us
);

typedef struct {
    AnimationFunction render;
    void *state;
} Animation;

// Animation one - LED Chasing
typedef struct {
    // sequence of LEDs
    const uint8_t *order;
    
    uint8_t count;

    uint8_t position;
    uint8_t completed_runs;

    // time between steps
    uint32_t interval_us;
    // time of next step
    uint32_t next_step_us;
} ChaseState;


// chase sequence order
static const uint8_t chase_order[] = {
    LED_D8,
    LED_D9,
    LED_D10,
    LED_D1,
    LED_D3,
    LED_D4,
    LED_D5,
    LED_D6,
};

static uint8_t Animation_Chase(void *state, uint32_t now_us) {
    ChaseState *chase = (ChaseState *)state;

    if (chase->count == 0) return 0;

    while ((int32_t)(now_us - chase->next_step_us) >= 0) {
        chase->position++;

        if (chase->position >= chase->count) {
            chase->position = 0;

            chase->completed_runs++;
        }

        chase->next_step_us += chase->interval_us;
    }

    // return mask w/ only current LED
    return (uint8_t)(1U << chase->order[chase->position]);
}

// light flash animation
static uint8_t Animation_AllFlash(void *state, uint32_t now_us) {
    (void)state;

    if ((now_us/500000U) % 2U == 0U) return LED_MASK;

    return 0;
}

// RGB setup
// for common anode LED, low = ON, high = OFF
static void RGB_OFF(void) {
    GPIO_SetBits(GPIOC, RGB_MASK);
}

// use software pwm for rgb, from 0-255
static void RGB_ShowColor(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint16_t pwm = 0; pwm < 255; pwm++) {
        uint16_t off_mask = 0;

        // determine which channels should be off
        if (pwm >= red) off_mask |= RGB_R_PIN;

        if (pwm>= green) off_mask |= RGB_G_PIN;

        if (pwm >= blue) off_mask |= RGB_B_PIN;

        // high means off
        GPIO_SetBits(GPIOC, off_mask);

        // remaining pins are on
        uint16_t on_mask = RGB_MASK & (~off_mask);

        GPIO_ResetBits(GPIOC, on_mask);

        Delay_Us(RGB_PWM_SLOT_US);
    }
}


// RGB Rainbow Animation
// converts linear position to rgb color
// r > g > b > r
static void RGB_RainbowColor (
    uint8_t hue,
    uint8_t *red,
    uint8_t *green,
    uint8_t * blue
) {
    if (hue < 85) {
        *red = 255 - (hue * 3);
        *green = hue * 3;
        *blue = 0;
    } else if (hue < 170) {
        hue -= 85;

        *red = 0;
        *green = 255 - (hue * 3);
        *blue = hue * 3;
    } else {
        hue -= 170;

        *red =  hue * 3;
        *green = 0;
        *blue = 255 - (hue * 3);
    }
}

static void RGB_Rainbow(void) {
    for (uint8_t cycle=0; cycle < RAINBOW_CYCLES; cycle++) {
        for (uint16_t hue = 0; hue < 256; hue++) {
            uint8_t r, g ,b;

            RGB_RainbowColor((uint8_t)hue, &r, &g, &b);

            RGB_ShowColor(r, g, b);
        }
    }

    RGB_OFF();
}


// buzzer driver
// generates square wave tone
// fq in Hz, duration in ms
static void Buzzer_Tone(uint16_t frequency, uint16_t duration_ms) {
    if (frequency == 0) {
        GPIO_ResetBits(GPIOC, BUZZER_PIN);
        Delay_Ms(duration_ms);
        return;
    }

    // us half period
    uint32_t half_period_us = 500000UL / frequency;

    // # of complete oscillations
    uint32_t cycles = ((uint32_t)frequency * duration_ms) / 1000UL;

    if (cycles == 0) cycles = 1;

    for (uint32_t i = 0; i < cycles; i++) {
        GPIO_SetBits(GPIOC, BUZZER_PIN);
        Delay_Us(half_period_us);

        GPIO_ResetBits(GPIOC, BUZZER_PIN);
        Delay_Us(half_period_us);
    }

    GPIO_ResetBits(GPIOC, BUZZER_PIN);
}

// buzzer notes
typedef struct {
    uint16_t frequency;
    uint16_t duration_ms;
} Note;

// buzzer song :D
static const Note melody[] = {
    {554,400}, //C#5
    {622,400}, //D#5
    {415,325}, //G#4
    {622,400}, //D#5
    {698,400}, //F5
    {831,125}, //G#5
    {740,125}, //F#5
    {698,125}, //F5
    {554,400}, //C#5
    {622,400}, //D#5
    {415,1000}, //G#4
};

static void Buzzer_PlayTune(void) {
    const uint8_t note_count = sizeof(melody) / sizeof(melody[0]);

    for (uint8_t i = 0; i < note_count; i++) {
        Buzzer_Tone(melody[i].frequency, melody[i].duration_ms);

        Delay_Ms(30);
    }

    GPIO_ResetBits(GPIOC, BUZZER_PIN);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program. THE BIG MAIN FUNC
 *
 * @return  none
 */

int main(void) {
    SystemCoreClockUpdate();
    Delay_Init();

    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    Hardware_init();

    LED_AllOff();

    RGB_OFF();

    // init chase anim
    ChaseState chase = {
        chase_order, sizeof(chase_order) / sizeof(chase_order[0]),
        0, 0, CHASE_INTERVAL_US, CHASE_INTERVAL_US
    };

    // select anim 
    Animation active_animation = {
        Animation_Chase, &chase
    };

    // To use the other animation:
    /*
    active_animation.render = Animation_AllFlash;
    active_animation.state = 0;
    */
    
    uint32_t elapsed_us = 0;
    uint8_t scan_cursor = 0;

    while (1) {
        // STAGE 1 - LED CHASE
        while (chase.completed_runs < CHASE_RUNS) {

            uint8_t frame = active_animation.render(
                active_animation.state, elapsed_us
            );

            // stop if completed
            if (chase.completed_runs >= CHASE_RUNS) break;

            // display frame
            LED_ScanStep(frame, &scan_cursor);

            // update software clock
            elapsed_us += SCAN_SLOT_US;
        }

        LED_AllOff();

        // STAGE 2 - RGB rainbow

        RGB_Rainbow();
        Delay_Ms(100);

        // STAGE 3 - BUZZER
        Buzzer_PlayTune();

        // END 0_0
    }
}



vu8 val;

/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the USART2 & USART3 peripheral.
 *
 * @return  none
 */
void USARTx_CFG(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
// int main(void)
// {
//     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//     SystemCoreClockUpdate();
//     Delay_Init();
// #if (SDI_PRINT == SDI_PR_OPEN)
//     SDI_Printf_Enable();
// #else
//     USART_Printf_Init(115200);
// #endif
//     printf("SystemClk:%d\r\n",SystemCoreClock);
//     printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

//     USARTx_CFG();

//     while(1)
//     {

//         while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
//         {
//             /* waiting for receiving finish */
//         }
//         val = (USART_ReceiveData(USART1));
//         USART_SendData(USART1, ~val);
//         while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
//         {
//             /* waiting for sending finish */
//         }
//     }
// }
