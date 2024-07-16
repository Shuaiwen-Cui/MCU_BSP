/*
 * iled.c
 *
 *  Created on: June 07, 2024
 *      Author: SHUAIWEN CUI
 */

#include "iled.h"

void LED_R(uint8_t state) // LED R independent control function (0 is off, other values are on)
{

	if (state)
	{
		HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
	}
}

void LED_R_Toggle(void)
{
	int state = HAL_GPIO_ReadPin(LED_R_GPIO_Port, LED_R_Pin);
	HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, 1 - state);
}

void LED_G(uint8_t state) // LED R independent control function (0 is off, other values are on)
{

	if (state)
	{
		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
	}
}

void LED_G_Toggle(void)
{
	int state = HAL_GPIO_ReadPin(LED_G_GPIO_Port, LED_G_Pin);
	HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, 1 - state);
}