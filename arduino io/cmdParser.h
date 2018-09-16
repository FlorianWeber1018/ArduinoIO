/*
 * cmdParser.h
 *
 * Created: 09.10.2017 20:40:35
 *  Author: Flo
 */ 


#ifndef CMDPARSER_H_
#define CMDPARSER_H_
#include <stdbool.h>
#include <inttypes.h>
#include "uart.h"
#include "COMprotocol.h"
#include "list__array_uint8_t.h"
#include "avr/pgmspace.h"
#include "avr/portpins.h"




#ifndef nullptr
#define nullptr NULL
#endif

void toggleLed();

//int16_t CharArrayToInt(list_array_uint8_t_element* array);
//list_array_uint8_t_element* intToCharArray(int16_t value);
//list_array_uint8_t_element* intToCharArray(list_array_uint8_t_element* pre, int16_t value);
class cmdParser{
	public:
		cmdParser();
		void checkparser() volatile;
		void inc_parser_cnt() volatile;
		uint8_t get_parser_cnt() volatile;
		
	private:
		volatile uint8_t readCursor;
		volatile uint8_t parser_cnt;
		void parseOne() volatile;
		uint8_t parseUint8Number() volatile;
};
void plotNumber(uint8_t number, unsigned char* result);
void plotNumber(int16_t number, unsigned char* result);
//list_array_uint8_t_element* build_listElementFromProgmem(list_array_uint8_t_element* preElement, const uint8_t* inp, uint8_t inpSize);



#endif /* CMDPARSER_H_ */