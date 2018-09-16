/*
 * main.h
 *
 * Created: 11.10.2017 19:24:34
 *  Author: Flo
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <stdbool.h>
#include <inttypes.h>

#define F_CPU 16000000L 
void init_io();
void init_pwmTimer();
void init_ADC();
int16_t freeRam();
void test();
void testflush(uint8_t testChar);
#endif /* MAIN_H_ */