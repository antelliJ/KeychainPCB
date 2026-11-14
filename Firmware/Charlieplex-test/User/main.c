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
#define LED_COUNT 8
#define SCAN_SLOT_US 300U
#define CHASE_INTERVAL_US 150000U

#define PLEX_LINE_MASK (GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4)

#define LED_MASK ((uint8_t)((1U << LED_COUNT) - 1U))

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
static const uint16_t line_pins[LINE_COUNT] = {
    GPIO_Pin_0, // A
    GPIO_Pin_2, // B
    GPIO_Pin_3, // C
    GPIO_Pin_4, // D
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

    {LINE_C,LINE_D},
    {LINE_D,LINE_C},

    {LINE_A,LINE_C},
    {LINE_C,LINE_A}
};

// setting gpio pins to high impedence should make it better for the lines to be controlled externally  
static void Lines_HighZ(void) {
    GPIO_InitTypeDef gpio = {
        PLEX_LINE_MASK,
        GPIO_Speed_30MHz, // idk if can get away with less for less current draw?
        GPIO_Mode_IN_FLOATING
    };

    GPIO_Init(GPIOD, &gpio);
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
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
#if (SDI_PRINT == SDI_PR_OPEN)
    SDI_Printf_Enable();
#else
    USART_Printf_Init(115200);
#endif
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

    USARTx_CFG();

    while(1)
    {

        while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {
            /* waiting for receiving finish */
        }
        val = (USART_ReceiveData(USART1));
        USART_SendData(USART1, ~val);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        {
            /* waiting for sending finish */
        }
    }
}
