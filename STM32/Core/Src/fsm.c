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
    int idx = (index_buffer == 0) ? MAX_BUFFER_SIZE - 1 : index_buffer - 1;
    char c = buffer[idx];

    if (c == '!') {
        command_flag = 0;
        parser_mode = 0;
        memset(command_data, 0, MAX_BUFFER_SIZE);
        return;
    }

    if (command_flag == 1) return;

    if (c == '#') {
        command_flag = 1;
        command_data[parser_mode] = 0;

        process_command((char *)command_data);
        return;
    }

    if (parser_mode < MAX_BUFFER_SIZE - 1) {
        command_data[parser_mode++] = c;
    }
}

void process_command(char *cmd) {
    if (strcmp(cmd, "RST") == 0) {
        RST = 0;
        OK = 1;
        value_flag = 1;
        message_mode = SEND;
    }

    else if (strcmp(cmd, "OK") == 0) {
        message_mode = INIT;
        RST = 1;
        OK = 0;
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
