/*
 * led_display.h
 *
 *  Created on: Oct 2, 2025
 *      Author: tanvietvo
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

void led_red_blink();
void display7SEG(int, uint8_t, uint8_t);
void led_blink_2Hz(uint8_t);
void display_mode(uint8_t);

#endif /* INC_LED_DISPLAY_H_ */
