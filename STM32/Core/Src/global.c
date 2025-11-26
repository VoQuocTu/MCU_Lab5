/*
 * global.c
 *
 *  Created on: Nov 19, 2025
 *      Author: HP
 */

#include "global.h"

uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
int parser_mode = INIT;
int message_mode = INIT;

uint8_t command_flag = 1;
uint8_t command_data[MAX_BUFFER_SIZE];

int ADC_value = 0;
char str[50];
int value_flag = 0;

int RST = 1;
int OK = 0;
