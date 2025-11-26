/*
 * global.h
 *
 *  Created on: Nov 19, 2025
 *      Author: HP
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "fsm.h"
#include "software_timer.h"
#include <stdio.h>
#include "string.h"

#define INIT		0
#define RST_BEGIN	1
#define RST_R		2
#define RST_S		3
#define RST_T		4
#define OK_BEGIN	5
#define OK_O		6
#define OK_K		7

// FOR COMMUNICATION FSM
#define SEND		1
#define WAIT		2

// FOR UART
#define MAX_BUFFER_SIZE 30

#define TIME_CYCLE	10

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern int parser_mode;
extern int message_mode;
extern uint8_t command_flag;
extern uint8_t command_data[MAX_BUFFER_SIZE];

extern uint8_t index_buffer;
extern uint8_t buffer_flag;

extern int ADC_value;
extern char str[50];
extern int value_flag;

extern int RST;
extern int OK;

extern int timer_flag;

#endif /* INC_GLOBAL_H_ */
