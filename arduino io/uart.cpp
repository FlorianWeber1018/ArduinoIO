/*
 * UART.cpp
 *
 * Created: 08.10.2017 19:06:26
 *  Author: Flo
 */ 
 #include "uart.h"
 #include "lock.h"
 #include <stdbool.h>

volatile uint8_t InBufferUart0[256];
volatile uint8_t InBufferUart0pointer = 0;
volatile lock lockUart0;
#include "debug.h"

extern volatile cmdParser myParser;

 void init_UART0(){

InBufferUart0pointer=0;
	 uint16_t baud = F_CPU / (BAUD * 16L) -1;
	 UBRR0H = (uint8_t) (baud >> 8);
	 UBRR0L = (uint8_t) baud;
	 UCSR0B = UCSR0B_std;
	 UCSR0C = UCSR0C_std;

 }
 //initiate serial communication on pins
 void init_UART1(){
	 
	 uint16_t baud = F_CPU / (BAUDdebug * 16L) -1;
	 UBRR1H = (uint8_t) (baud >> 8);
	 UBRR1L = (uint8_t) baud;
	 UCSR1B = UCSR1B_std;
	 UCSR1C = UCSR1C_std;
}
ISR(USART0_RX_vect){
	uint8_t tempRec = UDR0;
	InBufferUart0[InBufferUart0pointer] = tempRec;
	InBufferUart0pointer++;
	if(tempRec == eot){
		myParser.inc_parser_cnt();
	}
}
ISR(USART1_RX_vect){
	 uint8_t temp= UDR1;

}
void serial_out0(uint8_t data){
	lockUart0.tryLock();
	while (!(UCSR0A & (1<<UDRE0)))  // warten bis Senden moeglich
	{
		asm volatile("nop");
	}
	 
	UDR0 = data;                    //sende Zeichen
	lockUart0.unlock();
	return;
}
void serial_out0(uint8_t* data, uint8_t count){
	lockUart0.tryLock();
	for(uint8_t i=0; i < count;i++){
		while (!(UCSR0A & (1<<UDRE0)))  // warten bis Senden moeglich
		{
			asm volatile("nop");
		}
		UDR0 = data[i];                    //sende Zeichen
	}
	lockUart0.unlock();
}
void serial_out1(uint8_t data){
	 while (!(UCSR0A & (1<<UDRE0)))  // warten bis Senden moeglich
	 {
		 asm("nop");
	 }
	 UDR1 = data;                    //sende Zeichen
}
