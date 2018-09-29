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
extern io_pin* io[40];
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
/*
bool cmdHandler__io();
bool cmdHandler__io_set();
bool cmdHandler__io_set_value();
bool cmdHandler__io_set_value_io0(int16_t num);
bool cmdHandler__io_set_value_io0_true(int16_t pin);
bool cmdHandler__io_set_value_io0_false(int16_t pin);
bool cmdHandler__io_set_value_io1(int16_t num);
bool cmdHandler__io_set_value_io1_true(int16_t pin);
bool cmdHandler__io_set_value_io1_false(int16_t pin);
bool cmdHandler__io_set_value_io2(int16_t num);
bool cmdHandler__io_set_value_io2_true(int16_t pin);
bool cmdHandler__io_set_value_io2_false(int16_t pin);
bool cmdHandler__io_set_value_io3(int16_t num);
bool cmdHandler__io_set_value_io3_true(int16_t pin);
bool cmdHandler__io_set_value_io3_false(int16_t pin);
bool cmdHandler__io_set_value_io3(int16_t num);
bool cmdHandler__io_set_value_io3_true(int16_t pin);
bool cmdHandler__io_set_value_io3_false(int16_t pin);
bool cmdHandler__io_set_value_io3(int16_t num);
bool cmdHandler__io_set_value_io3_true(int16_t pin);
bool cmdHandler__io_set_value_io3_false(int16_t pin);
bool cmdHandler__io_set_value_io4(int16_t num);
bool cmdHandler__io_set_value_io4_true(int16_t pin);
bool cmdHandler__io_set_value_io4_false(int16_t pin);


bool cmdHandler__io_set_config();
bool cmdHandler__io_set_config_io0(int16_t pin_config);   //wenn pin==0xFF -> alle setzen
bool cmdHandler__io_set_config_io1(int16_t pin_config);
bool cmdHandler__io_set_config_io2(int16_t pin_config);
bool cmdHandler__io_set_config_io3(int16_t pin_config);
bool cmdHandler__io_set_config_io4(int16_t pin_config);
bool cmdHandler__io_set_config_adc0(int16_t pin_config);
bool cmdHandler__io_set_config_adc1(int16_t pin_config); 



bool cmdHandler__io_get();
bool cmdHandler__io_get_config();
bool cmdHandler__io_get_config_io0();
bool cmdHandler__io_get_config_io0(int16_t pin);
bool cmdHandler__io_get_config_io1();
bool cmdHandler__io_get_config_io1(int16_t pin);
bool cmdHandler__io_get_config_io2();
bool cmdHandler__io_get_config_io2(int16_t pin);
bool cmdHandler__io_get_config_io3();
bool cmdHandler__io_get_config_io3(int16_t pin);
bool cmdHandler__io_get_config_io4();
bool cmdHandler__io_get_config_io4(int16_t pin);
bool cmdHandler__io_get_config_adc0();
bool cmdHandler__io_get_config_adc0(int16_t pin);
bool cmdHandler__io_get_config_adc1();
bool cmdHandler__io_get_config_adc1(int16_t pin);
bool cmdHandler__io_get_value();
bool cmdHandler__io_get_value_io0();
bool cmdHandler__io_get_value_io0(int16_t);
bool cmdHandler__io_get_value_io1();
bool cmdHandler__io_get_value_io1(int16_t);
bool cmdHandler__io_get_value_io2();
bool cmdHandler__io_get_value_io2(int16_t);
bool cmdHandler__io_get_value_io3();
bool cmdHandler__io_get_value_io3(int16_t);
bool cmdHandler__io_get_value_io4();
bool cmdHandler__io_get_value_io4(int16_t);
bool cmdHandler__io_get_value_adc0();
bool cmdHandler__io_get_value_adc0(int16_t);
bool cmdHandler__io_get_value_adc1();
bool cmdHandler__io_get_value_adc1(int16_t);
*/







#endif /* CMDHANDLER_H_ */