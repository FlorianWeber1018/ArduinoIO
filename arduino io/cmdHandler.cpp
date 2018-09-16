/*
 * cmdHandler.cpp
 *
 * Created: 18.10.2017 19:25:14
 *  Author: Flo
 */
 #include "cmdHandler.h"
 #include <avr/io.h>
 #include "uart.h"
 #include "cmdParser.h"
 #include "io.h"
 void cmdHandler__freeMem()
 {
	serial_out0(cmdfreeRam);

	uint8_t numberStr[4];
	plotNumber( freeRam(), numberStr);
	serial_out0(numberStr, 4);
	serial_out0(eot);
 }
 void cmdHandler_get_value_io(uint8_t pin)
 {
	if(pin < 40){
 		serial_out0(setVI0 + pin);
 		uint8_t numberStr[2];
		plotNumber(io[pin]->get(), numberStr);
		serial_out0(numberStr, 2);
		serial_out0(eot);
	}
 }
void cmdHandler_get_value_adc(uint8_t pin)
{
	if (pin < 16){
		serial_out0(setVA0 + pin);
		uint8_t numberStr[4];
		plotNumber( myADC.getoutput(pin), numberStr);
		serial_out0(numberStr, 4);
		serial_out0(eot);
	}
}
void cmdHandler_get_config_io(uint8_t pin)
{
static uint8_t cnt = 0;
	if(pin < 40){
		cnt++;
		serial_out0(setCI0 + pin);
		uint8_t numberStr[2];
		//plotNumber(io[pin]->getconfig(), numberStr);
		plotNumber(3, numberStr);
		serial_out0(numberStr, 2);
		serial_out0(eot);
		//serial_out1('h');
	}

}
void cmdHandler_get_config_adc(uint8_t pin)
{
	if (pin < 16){
		serial_out0(setCA0 + pin);
		uint8_t numberStr[2];
		plotNumber( myADC.getconfig(pin), numberStr);
		serial_out0(numberStr, 2);
		serial_out0(eot);
	}
}
void cmdHandler_set_value_io(uint8_t pin, uint8_t value)
{
	if(pin < 40){
		io[pin]->set(value);
		cmdHandler_get_value_io(pin);
	}
}
void cmdHandler_set_config_io(uint8_t pin, uint8_t config)
{
	if(pin < 40){
		io[pin]->setconfig(config);
		cmdHandler_get_config_io(pin);
	}
}
void cmdHandler_set_config_adc(uint8_t pin, uint8_t config)
{
	if(pin < 16){
		myADC.setconfig(pin, config);
		cmdHandler_get_config_adc(pin);
	}
}
