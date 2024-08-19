/**
 * @file bsp_init.c
 * @author SHUAIWEN CUI (SHUAIWEN001 AT e DOT ntu DOT edu DOT sg)
 * @brief
 * @version 1.0
 * @date 2024-07-12
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "bsp_init.h"

/**
 * @name BSP_Init
 * @brief board support package initialization
 * @param None
 * @retval 0
 *
 */
int BSP_Init(void)
{
    // Variables
    int i;
#ifdef MODULE_ENABLE_LED
    // BSP Initialization - LED - flash once to indicate OK
#ifdef BSP_INIT_TEST
    LED_R(1), LED_G(1);
    HAL_Delay(200);
    LED_R(0), LED_G(0);
    HAL_Delay(200);
    LED_R(1), LED_G(1);
#endif
#endif

#ifdef MODULE_ENABLE_KEY
    // BSP Initialization - Key
    // nothing required
#endif

#ifdef MODULE_ENABLE_USART1
#ifdef BSP_INIT_TEST
    // Initialization - Count Down
    for (i = 0; i < 5; i++)
    {
        printf("[INITIALIZATION] Count Down: %d \n\r", 5 - i);
        HAL_Delay(1000);
    }
#endif
    // BSP Initialization - Serial Communication
    MCU_serial_init();
    printf("[INITIALIZATION] Serial Communication - SUCCESS\n\r");
    // MCU_printf("Serial Communication - SUCCESS\n\r"); // not working
#endif

    HAL_Delay(1000);

#ifdef MODULE_ENABLE_SDRAM
    // BSP Initialization - SDRAM
    printf("[INITIALIZATION] SDRAM Initialization - START\n\r");
    SDRAM_Initialization_Sequence();
    printf("[INITIALIZATION] SDRAM W9825G6KH Initialization - FINISHED\r\n");
#ifdef BSP_INIT_TEST
    if (SDRAM_Test() == 0)
    {
        printf("[INITIALIZATION] SDRAM TEST - SUCCESS\r\n");
    }
    else
    {
        printf("[INITIALIZATION] SDRAM TEST - FAIL\r\n");
    }
#endif
#endif

    HAL_Delay(1000);

#ifdef MODULE_ENABLE_MEMORY
    // BSP Initialization - Memory Management
    printf("[INITIALIZATION] Memory Management Initialization - START\n\r");
    memory_init();
    printf("[INITIALIZATION] Memory Management Initialization - FINISHED\n\r");
    HAL_Delay(1000);
#ifdef BSP_INIT_TEST
    printf("[INITIALIZATION] Memory Management Test - START\n\r");
    if(memory_management_test() == 0)
    {
        printf("[INITIALIZATION] Memory Management Test - SUCCESS\n\r");
    }
    else
    {
        printf("[INITIALIZATION] Memory Management Test - FAIL\n\r");
    }
#endif
#endif
HAL_Delay(1000);

    return BSP_INIT_SUCCESS;
}


#ifdef MODULE_ENABLE_USART1

// MicroLib needed for retargetting
// retarget fputc for printf
int fputc(int ch, FILE *f)
{
    uint8_t temp = (uint8_t)ch;
    HAL_UART_Transmit(&huart1, &temp, 1, HAL_MAX_DELAY);
    return ch;
}

// retarget fgetc for scanf
int fgetc(FILE *f)
{
    while (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) == RESET)
        ;                                      // Wait until the data is received
    return (int)(huart1.Instance->RDR & 0xFF); // Read the received data
}
#endif