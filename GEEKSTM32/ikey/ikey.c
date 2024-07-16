/**
 * @file ikey.c
 * @author SHUAIWEN CUI (shuaiwencui at gmail dot com)
 * @brief 
 * @version 1.0
 * @date 2024-07-14
 */

#include "ikey.h"
#include "iled.h"

#if KEY_MODE == 0
/**
 * @name KEY0
 * @brief Read the level of the key interface
 * @param None
 * @retval 1: key pressed, 0: key not pressed
 */
uint8_t KEY0(void)
{
	uint8_t key_status = 0;
	key_status=0;//if key is not pressed, return 0
	if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==GPIO_PIN_RESET){// read the level of the key interface
		HAL_Delay(20);// delay 20ms to avoid jitter
		if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==GPIO_PIN_RESET){ // read the level of the key interface again
			key_status=1;// if the key is pressed, return 1
		}
	}
	while(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==GPIO_PIN_RESET); // wait for the key to be released
	return key_status;
}

/**
 * @name KEY1
 * @brief Read the level of the key interface
 * @param None
 * @retval 1: key pressed, 0: key not pressed
 */
uint8_t KEY1(void)
{
	uint8_t key_status = 0;
	key_status=0;//if key is not pressed, return 0
	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET){// read the level of the key interface
		HAL_Delay(20);// delay 20ms to avoid jitter
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET){ // read the level of the key interface again
			key_status=1;// if the key is pressed, return 1
		}
	}
	while(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET); // wait for the key to be released
	return key_status;
}

#else
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == KEY0_Pin)
    {
		LED_Toggle();
    }
    if(GPIO_Pin == KEY1_Pin)
    {
		LED_Toggle();
    }
}

#endif