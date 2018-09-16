/*
 * cmdParser.cpp
 *
 * Created: 09.10.2017 20:40:21
 *  Author: Flo
 */
#include "cmdParser.h"
#include "cmdHandler.h"
#include <string.h>
#include "uart.h"
#include "debug.h"
extern volatile uint8_t  InBufferUart0[256];
extern volatile uint8_t InBufferUart0pointer;
cmdParser::cmdParser()
{
	readCursor = 0;
	parser_cnt = 0;
}

 void cmdParser::checkparser() volatile
 {
	if(parser_cnt > 0){
	/*
		debug::debug0(readCursor);
		debug::debug1(InBufferUart0pointer);
		debug::debug2(parser_cnt);	
		*/
		parseOne();
		//serial_out1('d');

		
	}
}
void cmdParser::parseOne() volatile
{
	cli();
	uint8_t cmdByte = InBufferUart0[readCursor];	//readCursor starts with cmd Byte
	sei();
	readCursor++;
		//serial_out1('1');
	if( cmdByte < setVA0 || cmdByte > cmdfreeRam){		//really cmd byte????
		serial_out1('e');
		
	}else{
		cli();
		uint8_t parsedNumber = parseUint8Number();
		sei();
		//serial_out1('2');
		readCursor++;
		if( cmdByte <= getCA15 ){							
			if(cmdByte <= getVA15){
				if(cmdByte <= setVA15){
					//set value A0..15
					//MAKES NO SENSE -> do nothing
				}else{
					//get value A0..15
					cmdHandler_get_value_adc(cmdByte-getVA0);
				}
			}else{
				if(cmdByte <= setCA15){
					//set config A0..15
					cmdHandler_set_config_adc(cmdByte-setCA0, parsedNumber);
				}else{
					//get config A0..15
					cmdHandler_get_config_adc(cmdByte-getCA0);
				}
			}
		}else{
			if(cmdByte <= getVI39){
				if(cmdByte <= setVI39){
					//set value I0..31
					cmdHandler_set_value_io(cmdByte-setVI0, parsedNumber);
				}else{
					//get value I0..31
					cmdHandler_get_value_io(cmdByte-getVI0);
				}
			}else{
				if(cmdByte <= setCI39){
					//set config I0..31
					cmdHandler_set_config_io(cmdByte-setCI0, parsedNumber);
				}else{
					if(cmdByte <=getCI39){
						//get config I0..31
						cmdHandler_get_config_io(cmdByte-getCI0);
					}else{
						if(cmdByte == cmdfreeRam){
							cmdHandler__freeMem();
						}
					}	
				}
			}
		}			
	}
	this->parser_cnt--;
}


void cmdParser::inc_parser_cnt() volatile
{
	parser_cnt++;
}
uint8_t cmdParser::get_parser_cnt() volatile
{
	return parser_cnt;
}
uint8_t cmdParser::parseUint8Number() volatile{
	uint8_t i = 0;
	uint8_t result = 0;
	uint8_t partitialResult = InBufferUart0[readCursor];
	while(partitialResult != eot){
		switch(i){
			case 0:{
				result += partitialResult;
			}break;
			case 1:{
				result += partitialResult << 4;
			}break;
			default:{
				return 0;
			}
		}
		i++;
		partitialResult = InBufferUart0[++readCursor];
	}
	return result;
}

void plotNumber(uint8_t number, unsigned char* result){
	result[0] = ( number & 0x0F );
	result[1] = ( number >> 4 ) & 0x0F;
}
void plotNumber(int16_t number, unsigned char* result){
	result[0] = (unsigned char)( number & 0x000F );
	result[1] = (unsigned char)( ( number >> 4 ) & 0x000F );
	result[2] = (unsigned char)( ( number >> 8 ) & 0x000F );
	result[3] = (unsigned char)( ( number >> 12 ) & 0x000F );
}