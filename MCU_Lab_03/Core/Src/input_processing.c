/*
 * input_processing.c
 *
 * Created on: Oct 2, 2025
 * Author: tanvietvo
 */

#include "main.h"

#define LED_TYPE_RED   1
#define LED_TYPE_AMBER 2
#define LED_TYPE_GREEN 3

typedef enum {
    INIT,
    GREEN, 		// Trạng thái NS Xanh, EW Đỏ
    AMBER,   	// Trạng thái NS Vàng, EW Đỏ
    RED_GREEN,  // Trạng thái NS Đỏ, EW Xanh
    RED_AMBER   // Trạng thái NS Đỏ, EW Vàng
} TRAFFIC_STATUS;

TRAFFIC_STATUS status = INIT;
int counter_NS = 0;
int counter_EW = 0;

typedef enum {
    MODE_RED_LONGER,
    MODE_GREEN_LONGER
} TRAFFIC_MODE;

enum ButtonState { BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND };
enum ButtonState buttonState[3] = { BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED };

typedef enum MODE {
	MODE_NORMAL,
	MODE_RED_SETTING,
	MODE_AMBER_SETTING,
	MODE_GREEN_SETTING
} MODE;
MODE modes[4] = { MODE_NORMAL, MODE_RED_SETTING, MODE_AMBER_SETTING, MODE_GREEN_SETTING };
int mode_order = -1;

int red_cnt = 5;
int amber_cnt = 2;
int green_cnt = 3;

int tmp_red_cnt = 0;
int tmp_amber_cnt = 0;
int tmp_green_cnt = 0;

TRAFFIC_MODE traffic_state = MODE_RED_LONGER;

void fsm_for_input_processing(void)
{
	for (uint8_t i = 0; i < 3; i++)
	{
		switch(buttonState[i])
		{
		case BUTTON_RELEASED:
			if(is_button_pressed(i))
			{
				buttonState[i] = BUTTON_PRESSED;
				if (i == 0)		//When press BTN1
				{
					mode_order++;
					if (mode_order >= 4)
						mode_order = 0;
					if (mode_order == 0)
						status = INIT;	//reset FSM
					else
					{
						HAL_GPIO_WritePin(GPIOB, RED_NS_Pin|RED_EW_Pin|YELLOW_NS_Pin|YELLOW_EW_Pin|GREEN_NS_Pin|GREEN_EW_Pin, GPIO_PIN_SET);
						MODE current_mode = modes[mode_order];
						if (current_mode == MODE_RED_SETTING)
						{
							tmp_red_cnt = red_cnt;
						}
						else if (current_mode == MODE_AMBER_SETTING)
						{
							tmp_amber_cnt = amber_cnt;
						}
						else if (current_mode == MODE_GREEN_SETTING)
						{
							tmp_green_cnt = green_cnt;
						}
					}
				}
				else if (i == 1)
				{
					MODE current_mode = modes[mode_order];

					if (current_mode == MODE_RED_SETTING)
					{
						tmp_red_cnt++;
						if (tmp_red_cnt == 100) tmp_red_cnt = 1;
					}
					else if (current_mode == MODE_AMBER_SETTING)
					{
						tmp_amber_cnt++;
						if (tmp_amber_cnt == 100) tmp_amber_cnt = 1;
					}
					else if (current_mode == MODE_GREEN_SETTING)
					{
						tmp_green_cnt++;
						if (tmp_green_cnt == 100) tmp_green_cnt = 1;
					}
				}
				else if (i == 2)
				{
					MODE current_mode = modes[mode_order];

					if (current_mode == MODE_RED_SETTING)
					{
						red_cnt = tmp_red_cnt;
					}
					else if (current_mode == MODE_AMBER_SETTING)
					{
						amber_cnt = tmp_amber_cnt;
					}
					else if (current_mode == MODE_GREEN_SETTING)
					{
						green_cnt = tmp_green_cnt;
					}
					traffic_time_init();
				}
			}
			break;

		case BUTTON_PRESSED:
			if(!is_button_pressed(i))
			{
				buttonState[i] = BUTTON_RELEASED;
			}
			else
			{
				if(is_button_pressed_1s(i))
				{
					buttonState[i] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;

		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if(!is_button_pressed(i))
			{
				buttonState[i] = BUTTON_RELEASED;
			}
			//todo
			else
			{
				if (i == 1)
				{
					MODE current_mode = modes[mode_order];

					if (current_mode == MODE_RED_SETTING)
					{
						tmp_red_cnt++;
						if (tmp_red_cnt == 100) tmp_red_cnt = 1;
					}
					else if (current_mode == MODE_AMBER_SETTING)
					{
						tmp_amber_cnt++;
						if (tmp_amber_cnt == 100) tmp_amber_cnt = 1;
					}
					else if (current_mode == MODE_GREEN_SETTING)
					{
						tmp_green_cnt++;
						if (tmp_green_cnt == 100) tmp_green_cnt = 1;
					}
				}
			}
			break;
		}
	}
}

void run_background()
{
	if (mode_order < 0) return;

	MODE current_mode = modes[mode_order];
	int mode = mode_order + 1;
	display_mode(mode);

	switch (current_mode)
	{
	case MODE_NORMAL:
		fsm_run();
		count_down();
		display_counter();
		break;

	case MODE_RED_SETTING:
		led_blink_2Hz(LED_TYPE_RED);
		display_setting_counter(tmp_red_cnt);
		break;

	case MODE_AMBER_SETTING:
		led_blink_2Hz(LED_TYPE_AMBER);
		display_setting_counter(tmp_amber_cnt);
		break;

	case MODE_GREEN_SETTING:
		led_blink_2Hz(LED_TYPE_GREEN);
		display_setting_counter(tmp_green_cnt);
		break;
	}
}

void traffic_time_init()
{
	if (red_cnt >= green_cnt)
	{
		traffic_state = MODE_RED_LONGER;
		amber_cnt = red_cnt - green_cnt;
	}
	else
	{
		traffic_state = MODE_GREEN_LONGER;
		amber_cnt = green_cnt - red_cnt;
	}
    status = INIT; // Reset FSM để áp dụng thay đổi ngay lập tức
}

void fsm_run()
{
    switch(status)
    {
        case INIT:
            // --- Giai đoạn 1: NS Xanh, EW Đỏ ---
            status = GREEN;
            setTimer(2, green_cnt * 1000); // Timer cho đèn xanh NS
            setTimer(1, 1000);             // Timer 1s để đếm ngược

            // Thiết lập giá trị counter ban đầu dựa trên mode
            counter_NS = green_cnt;
            if (traffic_state == MODE_RED_LONGER) {
                counter_EW = red_cnt;
            } else { // MODE_GREEN_LONGER
                counter_EW = green_cnt + amber_cnt;
            }
            display_counter();
            break;

        case GREEN:
            // Bật đèn: NS Xanh, EW Đỏ
            HAL_GPIO_WritePin(GPIOB, GREEN_NS_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, RED_NS_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, YELLOW_NS_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, RED_EW_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GREEN_EW_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, YELLOW_EW_Pin, GPIO_PIN_SET);

            if (isTimerExpired(2) == 1) {
                // --- Giai đoạn 2: NS Vàng, EW Đỏ ---
                status = AMBER;
                setTimer(3, amber_cnt * 1000); // Timer cho đèn vàng NS
                setTimer(1, 1000);

                counter_NS = amber_cnt;
                if (traffic_state == MODE_RED_LONGER) {
                    counter_EW = amber_cnt;
                } else {
                	counter_EW = amber_cnt;
                }
            }
            break;

        case AMBER:
            // Bật đèn: NS Vàng, EW Đỏ
            HAL_GPIO_WritePin(GPIOB, YELLOW_NS_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GREEN_NS_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, RED_EW_Pin, GPIO_PIN_RESET);

            if (isTimerExpired(3) == 1) {
                // --- Giai đoạn 3: NS Đỏ, EW Xanh ---
                status = RED_GREEN;
                setTimer(1, 1000);

                if (traffic_state == MODE_RED_LONGER) {
                	setTimer(4, green_cnt * 1000);
                    counter_NS = red_cnt;
                	counter_EW = green_cnt;
                } else { // MODE_GREEN_LONGER
                	setTimer(4, (red_cnt - amber_cnt) * 1000);
                    counter_NS = red_cnt;
                    counter_EW = red_cnt - amber_cnt;
                }
            }
            break;

        case RED_GREEN:
            // Bật đèn: NS Đỏ, EW Xanh
            HAL_GPIO_WritePin(GPIOB, RED_NS_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, YELLOW_NS_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GREEN_EW_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, RED_EW_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, YELLOW_EW_Pin, GPIO_PIN_SET);

            if (isTimerExpired(4) == 1) {
                // --- Giai đoạn 4: NS Đỏ, EW Vàng ---
                status = RED_AMBER;
                setTimer(5, amber_cnt * 1000); // Timer cho đèn vàng EW
                setTimer(1, 1000);

                counter_EW = amber_cnt;
                if (traffic_state == MODE_RED_LONGER) {
                    counter_NS = amber_cnt;
                } else {
                	counter_NS = amber_cnt;
                }
            }
            break;

        case RED_AMBER:
            // Bật đèn: NS Đỏ, EW Vàng
            HAL_GPIO_WritePin(GPIOB, RED_NS_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, YELLOW_EW_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, GREEN_EW_Pin, GPIO_PIN_SET);

            if (isTimerExpired(5) == 1) {
                // Quay lại từ đầu để bắt đầu chu kỳ mới
                status = INIT;
            }
            break;
    }
}

void count_down()
{
	if (isTimerExpired(1) == 1)
	{
		setTimer(1, 1000);
		if (counter_NS > 0)
			counter_NS--;
		if (counter_EW > 0)
			counter_EW--;
	}
}

void display_counter()
{
	display7SEG(0, (uint8_t)(counter_NS / 10), 1);
	display7SEG(1, (uint8_t)(counter_NS % 10), 1);
	display7SEG(2, (uint8_t)(counter_EW / 10), 1);
	display7SEG(3, (uint8_t)(counter_EW % 10), 1);
}

void display_setting_counter(int counter)
{
	display7SEG(0, (counter / 10), 1);
	display7SEG(1, (counter % 10), 1);
}
