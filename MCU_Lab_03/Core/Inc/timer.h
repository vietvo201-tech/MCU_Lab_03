/*
 * timer.h
 *
 *  Created on: Oct 2, 2025
 *      Author: tanvietvo
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

void setTimer(int index, int duration);
int isTimerExpired(int index);
void timerRun();

#endif /* INC_TIMER_H_ */
