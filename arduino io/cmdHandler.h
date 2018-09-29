/*
 * cmdHandler.h
 *
 * Created: 18.10.2017 19:25:32
 *  Author: Flo
 */ 


#ifndef CMDHANDLER_H_
#define CMDHANDLER_H_
#include <inttypes.h>
#include <stdbool.h>
#include "io.h"
#include "ADC.h"
#include "COMprotocol.h"
extern volatile io_pin* io[40];
extern volatile AnalogDigitalConverter myADC;


void cmdHandler_get_value_io(uint8_t pin);
void cmdHandler_get_value_adc(uint8_t pin);
void cmdHandler_get_config_io(uint8_t pin);
void cmdHandler_get_config_adc(uint8_t pin);
void cmdHandler_set_value_io(uint8_t pin, uint8_t value);
void cmdHandler_set_config_io(uint8_t pin, uint8_t config);
void cmdHandler_set_config_adc(uint8_t pin, uint8_t config);

void cmdHandler_resetMCU();
void cmdHandler_freeMem();






#endif /* CMDHANDLER_H_ */