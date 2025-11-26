/*
 * fsm.c
 *
 *  Created on: Nov 19, 2025
 *      Author: HP
 */


#include "fsm.h"

void main_fsm(void) {
	if(buffer_flag == 1) {
		command_parser_fsm();
		buffer_flag = 0;
	}
	uart_communication_fsm();
}

void command_parser_fsm() {
	int index;
	if (index_buffer == 0) {
		index = MAX_BUFFER_SIZE - 1;
	}
	else {
		index = index_buffer - 1;
	}

	if (RST == 1) {
		switch(parser_mode) {
		case INIT:
			if (buffer[index] == '!') parser_mode = RST_BEGIN;
			else parser_mode = INIT;
			break;
		case RST_BEGIN:
			if (buffer[index] == 'R') parser_mode = RST_R;
			else parser_mode = INIT;
			break;
		case RST_R:
			if (buffer[index] == 'S') parser_mode = RST_S;
			else parser_mode = INIT;
			break;
		case RST_S:
			if (buffer[index] == 'T') parser_mode = RST_T;
			else parser_mode = INIT;
			break;
		case RST_T:
			if (buffer[index] == '#') {
				RST = 0;
				OK = 1;
				parser_mode = INIT;
				message_mode = SEND;
				value_flag = 1;
			}
			else parser_mode = INIT;
			break;
		default:
			parser_mode = INIT;
			break;
		}
	}

	if (OK == 1) {
		switch (parser_mode) {
		case INIT:
			if (buffer[index] == '!') parser_mode = OK_BEGIN;
			else parser_mode = INIT;
			break;
		case OK_BEGIN:
			if (buffer[index] == 'O') parser_mode = OK_O;
			else parser_mode = INIT;
			break;
		case OK_O:
			if (buffer[index] == 'K') parser_mode = OK_K;
			else parser_mode = INIT;
			break;
		case OK_K:
			if (buffer[index] == '#') {
				message_mode = INIT;
				parser_mode = INIT;
				RST = 1;
				OK = 0;
			}
			else parser_mode = INIT;
			break;
		default:
			parser_mode = INIT;
			break;
		}
	}
}

void uart_communication_fsm(void) {
	switch (message_mode) {
	case INIT:
		break;
	case SEND:
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		if (value_flag) {
			ADC_value = HAL_ADC_GetValue(&hadc1);
			value_flag = 0;
		}
		HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r!ADC=%d#\r\n", ADC_value), 1000);
		setTimer(3000);
		message_mode = WAIT;
		break;
	case WAIT:
		if (timer_flag) {
			message_mode = SEND;
		}
		break;
	default:
		break;
	}
}
