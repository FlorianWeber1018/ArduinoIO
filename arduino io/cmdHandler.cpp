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
 void cmdHandler_freeMem()
 {
	 uint8_t returnStr[6];
	 returnStr[0] = cmdfreeRam;
	 plotNumber( freeRam(), returnStr+1);
	 returnStr[5] = eot;
	 serial_out0(returnStr, 6);
 }
 void cmdHandler_get_value_io(uint8_t pin)
 {
	if(pin < 40){
		uint8_t returnStr[4];
		returnStr[0] = setVI0 + pin;
		plotNumber(io[pin]->get(), returnStr+1);
		returnStr[3] = eot;
		serial_out0(returnStr, 4);
	}
 }
void cmdHandler_get_value_adc(uint8_t pin)
{
	if (pin < 16){
		uint8_t returnStr[6];
		returnStr[0] = setVA0 + pin;
		plotNumber( myADC.getoutput(pin), returnStr+1);
		returnStr[5] = eot;
		serial_out0(returnStr, 6);
	}
}
void cmdHandler_get_config_io(uint8_t pin)
{
	if(pin < 40){
		uint8_t returnStr[4];
		returnStr[0] = setCI0 + pin;
		plotNumber(io[pin]->getconfig(), returnStr+1);
		returnStr[3] = eot;
		serial_out0(returnStr, 4);
	}
}
void cmdHandler_get_config_adc(uint8_t pin)
{
	if (pin < 16){
		uint8_t returnStr[4];
		returnStr[0] = setCA0 + pin;
		plotNumber( myADC.getconfig(pin), returnStr+1);
		returnStr[3] = eot;
		serial_out0(returnStr, 4);
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
