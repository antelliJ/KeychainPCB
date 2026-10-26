// Google's' sample blink program for the CH32V003

#include "debug.h"

/* Global Variable for bit toggle state */
u8 led_state = 0;

/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 * @brief   Initializes GPIOD Pin 0 (PD0) as a Push-Pull Output
 *********************************************************************/
void GPIO_Toggle_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // 1. Enable the clock for Port D
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    // 2. Configure Pin 0 as a Push-Pull output running at 50MHz
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    // 3. Apply settings to GPIOD
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

int main(void)
{
    // Initialize system configurations & system clock
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    
    // Optional: Initialize UART for debugging output (Default: 115200 baud)
    USART_Printf_Init(115200);
    printf("SystemClk: %d\r\n", SystemCoreClock);
    printf("CH32V003 GPIO Toggle Example\r\n");

    // Initialize the GPIO Pin
    GPIO_Toggle_INIT();

    while(1)
    {
        // Delay for 250 milliseconds
        Delay_Ms(250);
        
        // Toggle PD0 state
        if (led_state == 0) {
            GPIO_WriteBit(GPIOD, GPIO_Pin_0, Bit_SET);
            led_state = 1;
        } else {
            GPIO_WriteBit(GPIOD, GPIO_Pin_0, Bit_RESET);
            led_state = 0;
        }
    }
}
