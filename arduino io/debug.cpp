/*
 * debug.cpp
 *
 * Created: 03.09.2018 16:09:53
 *  Author: flo
 */ 
 #include "COMprotocol.h"
 #include "uart.h"
 #include "cmdParser.h"
 namespace debug{
	 void debug0(int16_t value){
		serial_out0(cmdDebug0);
		uint8_t numberStr[4];
		plotNumber( value, numberStr);
		serial_out0( numberStr, 4 );
		serial_out0(eot);
	 }
	 void debug0(uint8_t value){
		serial_out0(cmdDebug0);
		uint8_t numberStr[2];
		plotNumber( value, numberStr );
		serial_out0( numberStr, 2 );
		serial_out0(eot);
	 }
	 void debug1(int16_t value){
		 serial_out0(cmdDebug1);
		 uint8_t numberStr[4];
		 plotNumber( value, numberStr);
		 serial_out0( numberStr, 4 );
		 serial_out0(eot);
	 }
	 void debug1(uint8_t value){
		 serial_out0(cmdDebug1);
		 uint8_t numberStr[2];
		 plotNumber( value, numberStr );
		 serial_out0( numberStr, 2 );
		 serial_out0(eot);
	 }
	 void debug2(uint8_t value){
		 serial_out0(cmdDebug2);
		 uint8_t numberStr[2];
		 plotNumber( value, numberStr );
		 serial_out0( numberStr, 2 );
		 serial_out0(eot);
	 }
 }