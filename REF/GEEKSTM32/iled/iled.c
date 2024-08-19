/*
 * iled.c
 *
 *  Created on: June 07, 2024
 *      Author: SHUAIWEN CUI
 */

#include "iled.h"

void LED(uint8_t a)// LED R independent control function (0 is off, other values are on)
{
	if(a)HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
	else HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);
}

void LED_Toggle(void){
	HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,1-HAL_GPIO_ReadPin(LED_GPIO_Port,LED_Pin));
}

