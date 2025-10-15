/*
 * led_display.c
 *
 *  Created on: Oct 2, 2025
 *      Author: tanvietvo
 */

#include "main.h"

#define RED   1
#define AMBER 2
#define GREEN 3

const uint8_t bcd_table[10] = {
  0b0000, // 0
  0b0001, // 1
  0b0010, // 2
  0b0011, // 3
  0b0100, // 4
  0b0101, // 5
  0b0110, // 6
  0b0111, // 7
  0b1000, // 8
  0b1001  // 9
};

void led_red_blink()
{
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}

void display7SEG(int led_index, uint8_t num, uint8_t is_on)
{
	if (num < 0 || num >= 10)
	{
		return;
	}

	uint8_t v = bcd_table[num];
	if (is_on == 1)
	{
		switch (led_index)
		{
			case 0:
				HAL_GPIO_WritePin(GPIOA, SEG0_0_Pin, (v & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET); // A (LSB)
				HAL_GPIO_WritePin(GPIOA, SEG0_1_Pin, (v & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET); // B
				HAL_GPIO_WritePin(GPIOA, SEG0_2_Pin, (v & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET); // C
				HAL_GPIO_WritePin(GPIOA, SEG0_3_Pin, (v & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D (MSB)
				break;

			case 1:
				HAL_GPIO_WritePin(GPIOA, SEG1_0_Pin, (v & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET); // A (LSB)
				HAL_GPIO_WritePin(GPIOA, SEG1_1_Pin, (v & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET); // B
				HAL_GPIO_WritePin(GPIOA, SEG1_2_Pin, (v & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET); // C
				HAL_GPIO_WritePin(GPIOA, SEG1_3_Pin, (v & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D (MSB)
				break;

			case 2:
				HAL_GPIO_WritePin(GPIOA, SEG2_0_Pin, (v & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET); // A (LSB)
				HAL_GPIO_WritePin(GPIOA, SEG2_1_Pin, (v & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET); // B
				HAL_GPIO_WritePin(GPIOA, SEG2_2_Pin, (v & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET); // C
				HAL_GPIO_WritePin(GPIOB, SEG2_3_Pin, (v & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D (MSB)
				break;

			case 3:
				HAL_GPIO_WritePin(GPIOB, SEG3_0_Pin, (v & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET); // A (LSB)
				HAL_GPIO_WritePin(GPIOB, SEG3_1_Pin, (v & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET); // B
				HAL_GPIO_WritePin(GPIOB, SEG3_2_Pin, (v & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET); // C
				HAL_GPIO_WritePin(GPIOB, SEG3_3_Pin, (v & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D (MSB)
				break;

			case 4:
				HAL_GPIO_WritePin(GPIOB, SEG4_0_Pin, (v & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET); // A (LSB)
				HAL_GPIO_WritePin(GPIOB, SEG4_1_Pin, (v & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET); // B
				HAL_GPIO_WritePin(GPIOB, SEG4_2_Pin, (v & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET); // C
				HAL_GPIO_WritePin(GPIOB, SEG4_3_Pin, (v & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET); // D (MSB)
				break;
		}
	}
	else
	{
		switch (led_index)
		{
			case 0:
				HAL_GPIO_WritePin(GPIOA, SEG0_0_Pin, (v & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_SET); // A (LSB)
				HAL_GPIO_WritePin(GPIOA, SEG0_1_Pin, (v & 0x02) ? GPIO_PIN_RESET : GPIO_PIN_SET); // B
				HAL_GPIO_WritePin(GPIOA, SEG0_2_Pin, (v & 0x04) ? GPIO_PIN_RESET : GPIO_PIN_SET); // C
				HAL_GPIO_WritePin(GPIOA, SEG0_3_Pin, (v & 0x08) ? GPIO_PIN_RESET : GPIO_PIN_SET); // D (MSB)
				break;

			case 1:
				HAL_GPIO_WritePin(GPIOA, SEG1_0_Pin, (v & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_SET); // A (LSB)
				HAL_GPIO_WritePin(GPIOA, SEG1_1_Pin, (v & 0x02) ? GPIO_PIN_RESET : GPIO_PIN_SET); // B
				HAL_GPIO_WritePin(GPIOA, SEG1_2_Pin, (v & 0x04) ? GPIO_PIN_RESET : GPIO_PIN_SET); // C
				HAL_GPIO_WritePin(GPIOA, SEG1_3_Pin, (v & 0x08) ? GPIO_PIN_RESET : GPIO_PIN_SET); // D (MSB)
				break;

			case 2:
				HAL_GPIO_WritePin(GPIOA, SEG2_0_Pin, (v & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_SET); // A (LSB)
				HAL_GPIO_WritePin(GPIOA, SEG2_1_Pin, (v & 0x02) ? GPIO_PIN_RESET : GPIO_PIN_SET); // B
				HAL_GPIO_WritePin(GPIOA, SEG2_2_Pin, (v & 0x04) ? GPIO_PIN_RESET : GPIO_PIN_SET); // C
				HAL_GPIO_WritePin(GPIOB, SEG2_3_Pin, (v & 0x08) ? GPIO_PIN_RESET : GPIO_PIN_SET); // D (MSB)
				break;

			case 3:
				HAL_GPIO_WritePin(GPIOB, SEG3_0_Pin, (v & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_SET); // A (LSB)
				HAL_GPIO_WritePin(GPIOB, SEG3_1_Pin, (v & 0x02) ? GPIO_PIN_RESET : GPIO_PIN_SET); // B
				HAL_GPIO_WritePin(GPIOB, SEG3_2_Pin, (v & 0x04) ? GPIO_PIN_RESET : GPIO_PIN_SET); // C
				HAL_GPIO_WritePin(GPIOB, SEG3_3_Pin, (v & 0x08) ? GPIO_PIN_RESET : GPIO_PIN_SET); // D (MSB)
				break;
		}
	}
}

void led_blink_2Hz(uint8_t led_color)
{
	if (isTimerExpired(7) == 1)
	{
		if (led_color == RED)
			HAL_GPIO_TogglePin(GPIOB, RED_NS_Pin|RED_EW_Pin);
		else if (led_color == AMBER)
			HAL_GPIO_TogglePin(GPIOB, YELLOW_NS_Pin|YELLOW_EW_Pin);
		else if (led_color == GREEN)
			HAL_GPIO_TogglePin(GPIOB, GREEN_NS_Pin|GREEN_EW_Pin);
		setTimer(7, 500);
	}
}

void display_mode(uint8_t mode)
{
	if (mode < 1 || mode > 4)
	{
		return;
	}

	display7SEG(4, mode, 1);
}
