/*
 * software_timer.h
 *
 *  Created on: Nov 19, 2025
 *      Author: HP
 */

#include "software_timer.h"

int timer_counter;
int timer_flag;

void setTimer(int duration) {
	timer_counter = duration / TIME_CYCLE;
	timer_flag = 0;
}

void timerRun(void) {
	if (timer_counter > 0) {
		timer_counter--;
		if (timer_counter <= 0) {
			timer_flag = 1;
		}
	}
}
