/*
 * led_display.c
 *
 *  Created on: Oct 2, 2025
 *      Author: tanvietvo
 */

#include "main.h"

static uint8_t segPattern[10] =
{
    /* a b c d e f g */
    0b1111110, // 0: a b c d e f
    0b0110000, // 1: b c
    0b1101101, // 2: a b d e g
    0b1111001, // 3: a b c d g
    0b0110011, // 4: b c f g
    0b1011011, // 5: a c d f g
    0b1011111, // 6: a c d e f g
    0b1110000, // 7: a b c
    0b1111111, // 8: a b c d e f g
    0b1111011  // 9: a b c d f g
};

void led_red_blink()
{
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}

void display7SEG(int num)
{
	if (num <= 0 || num >= 10)
	{
		HAL_GPIO_WritePin(GPIOA, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_SET);
		return;
	}

	uint8_t seg = segPattern[num];
	// 7segledANODE -> active-low -> 0 = on and 1 = off
	// COM connected to VCC
	HAL_GPIO_WritePin(GPIOA, SEG0_Pin, !((seg >> 6) & 0x1));
	HAL_GPIO_WritePin(GPIOA, SEG1_Pin, !((seg >> 5) & 0x1)); // 0x11 & 1 = 3 & 1 = 1
	HAL_GPIO_WritePin(GPIOA, SEG2_Pin, !((seg >> 4) & 0x1));
	HAL_GPIO_WritePin(GPIOA, SEG3_Pin, !((seg >> 3) & 0x1));
	HAL_GPIO_WritePin(GPIOA, SEG4_Pin, !((seg >> 2) & 0x1));
	HAL_GPIO_WritePin(GPIOA, SEG5_Pin, !((seg >> 1) & 0x1));
	HAL_GPIO_WritePin(GPIOA, SEG6_Pin, !((seg >> 0) & 0x1));
}

void update7SEG(int index, int counter)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_SET);
	switch (index)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		display7SEG(counter);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		display7SEG(counter);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
		display7SEG(counter);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
		display7SEG(counter);
		break;
	default:
		break;
	}
}
