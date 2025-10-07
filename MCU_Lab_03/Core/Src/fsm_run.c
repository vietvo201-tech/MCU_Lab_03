/*
 * fsm_run.c
 *
 *  Created on: Oct 7, 2025
 *      Author: tanvietvo
 */
#include "main.h"

#define INIT        0
#define GREEN       1
#define AMBER       2
#define RED_GREEN   3
#define RED_AMBER   4

#define MODE_RED_LONGER   0		//red = green + amber
#define MODE_GREEN_LONGER 1		//green = red + amber

#define MAX_7SEG_LED 4

int traffic_state = MODE_RED_LONGER;
int status = INIT;
int counter_NS = 0;
int counter_EW = 0;

int red_cnt = 5;
int amber_cnt = 2;
int green_cnt = 3;

int led_index = 0;

void traffic_time_init()
{
	if (traffic_state == MODE_RED_LONGER)
	{
		red_cnt = red_cnt;
		green_cnt = green_cnt;
		amber_cnt = red_cnt - green_cnt;
	}
	else if (traffic_state == MODE_GREEN_LONGER)
	{
		red_cnt = red_cnt;
		green_cnt = green_cnt;
		amber_cnt = green_cnt - red_cnt;
	}
}

void fsm_run()
{
	if (isTimerExpired(6) == 1)
	{
		setTimer(6, 1000);
		if (counter_NS > 0)
			counter_NS--;
		if (counter_EW > 0)
			counter_EW--;
	}

	if (traffic_state == MODE_RED_LONGER)
	{
		switch (status)
		{
		case INIT:
			status = GREEN;
			setTimer(2, (green_cnt * 1000));
			setTimer(1, 100);
			setTimer(6, 1000);

			counter_NS = green_cnt;
			counter_EW = red_cnt;
			display_counter();
			break;

		case GREEN:
			HAL_GPIO_WritePin(GPIOB, RED_NORTH_Pin|RED_SOUTH_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GREEN_NORTH_Pin|GREEN_SOUTH_Pin, GPIO_PIN_RESET);

			HAL_GPIO_WritePin(GPIOB, YELLOW_WEST_Pin|YELLOW_EAST_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, RED_WEST_Pin|RED_EAST_Pin, GPIO_PIN_RESET);

			if (isTimerExpired(2) == 1)
			{
				status = AMBER;
				setTimer(3, (amber_cnt * 1000));
				counter_NS = amber_cnt;
				counter_EW = amber_cnt; //đồng bộ với NS
			}
			break;

		case AMBER:
			HAL_GPIO_WritePin(GPIOB, GREEN_NORTH_Pin|GREEN_SOUTH_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, YELLOW_NORTH_Pin|YELLOW_SOUTH_Pin, GPIO_PIN_RESET);

			if (isTimerExpired(3) == 1)
			{
				status = RED_GREEN;
				setTimer(4, (green_cnt * 1000));	//cheat
				counter_NS = red_cnt;
				counter_EW = green_cnt;
			}
			break;

		case RED_GREEN:
			HAL_GPIO_WritePin(GPIOB, YELLOW_NORTH_Pin|YELLOW_SOUTH_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, RED_NORTH_Pin|RED_SOUTH_Pin, GPIO_PIN_RESET);

			HAL_GPIO_WritePin(GPIOB, RED_WEST_Pin|RED_EAST_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GREEN_WEST_Pin|GREEN_EAST_Pin, GPIO_PIN_RESET);

			if (isTimerExpired(4) == 1)
			{
				status = RED_AMBER;
				setTimer(5, (amber_cnt * 1000));
				counter_NS = amber_cnt;		//cheat
				counter_EW = amber_cnt;
			}
			break;

		case RED_AMBER:
			HAL_GPIO_WritePin(GPIOB, GREEN_WEST_Pin|GREEN_EAST_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, YELLOW_WEST_Pin|YELLOW_EAST_Pin, GPIO_PIN_RESET);

			if (isTimerExpired(5) == 1)
			{
				status = GREEN;
				setTimer(2, (green_cnt * 1000));
				counter_NS = green_cnt;
				counter_EW = red_cnt;
			}
			break;
		}
	}
	else if (traffic_state == MODE_GREEN_LONGER)
	{
		switch (status)
		{
		case INIT:
			status = GREEN;
			setTimer(2, (green_cnt * 1000));
			setTimer(1, 100);
			setTimer(6, 1000);

			counter_NS = green_cnt;
			counter_EW = green_cnt + amber_cnt;
			display_counter();
			break;

		case GREEN:
			HAL_GPIO_WritePin(GPIOB, RED_NORTH_Pin|RED_SOUTH_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GREEN_NORTH_Pin|GREEN_SOUTH_Pin, GPIO_PIN_RESET);

			HAL_GPIO_WritePin(GPIOB, YELLOW_WEST_Pin|YELLOW_EAST_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, RED_WEST_Pin|RED_EAST_Pin, GPIO_PIN_RESET);

			if (isTimerExpired(2) == 1)
			{
				status = AMBER;
				setTimer(3, (amber_cnt * 1000));
				counter_NS = amber_cnt;
			}
			break;

		case AMBER:
			HAL_GPIO_WritePin(GPIOB, GREEN_NORTH_Pin|GREEN_SOUTH_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, YELLOW_NORTH_Pin|YELLOW_SOUTH_Pin, GPIO_PIN_RESET);

			if (isTimerExpired(3) == 1)
			{
				status = RED_GREEN;
				setTimer(4, ((red_cnt - amber_cnt) * 1000));	//green of EW road
				counter_NS = red_cnt;
				counter_EW = red_cnt - amber_cnt;
			}
			break;


		case RED_GREEN:
			HAL_GPIO_WritePin(GPIOB, YELLOW_NORTH_Pin|YELLOW_SOUTH_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, RED_NORTH_Pin|RED_SOUTH_Pin, GPIO_PIN_RESET);

			HAL_GPIO_WritePin(GPIOB, RED_WEST_Pin|RED_EAST_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GREEN_WEST_Pin|GREEN_EAST_Pin, GPIO_PIN_RESET);

			if (isTimerExpired(4) == 1)
			{
				status = RED_AMBER;
				setTimer(5, (amber_cnt * 1000));
				counter_NS = amber_cnt;		//cheat
				counter_EW = amber_cnt;
			}
			break;

		case RED_AMBER:
			HAL_GPIO_WritePin(GPIOB, GREEN_WEST_Pin|GREEN_EAST_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, YELLOW_WEST_Pin|YELLOW_EAST_Pin, GPIO_PIN_RESET);

			if (isTimerExpired(5) == 1)
			{
				status = GREEN;
				setTimer(2, (green_cnt * 1000));
				counter_NS = green_cnt;
				counter_EW = green_cnt + amber_cnt;
			}
			break;
		}
	}
}

void display_counter()
{
	if (isTimerExpired(1) == 1)
	{
		setTimer(1, 100);
		switch (led_index)
		{
		case 0:
			update7SEG(0, (counter_NS / 10));
			break;
		case 1:
			update7SEG(1, (counter_NS % 10));
			break;
		case 2:
			update7SEG(2, (counter_EW / 10));
			break;
		case 3:
			update7SEG(3, (counter_EW % 10));
			break;
		}
		led_index++;
		if (led_index >=  MAX_7SEG_LED)
			led_index = 0;
	}
}
