/*
 * arduino io.cpp
 *
 * Created: 11.10.2017 19:24:10
 * Author : Flo
 */ 

#include <avr/io.h>
#include "ADC.h"
#include "cmdParser.h"
#include "io.h"
#include "cmdHandler.h"
#include <avr/wdt.h>
#include <util/delay.h>

extern volatile uint8_t  InBufferUart0[256];
extern volatile uint8_t InBufferUart0pointer;

volatile AnalogDigitalConverter myADC;
volatile cmdParser myParser;
volatile io_pin* io[40];


#define testPin 32
int main(void)
{
	MCUSR = 0;
	wdt_disable();
	
DDRB |= 0x80;//LED
	init_io();
	
	init_pwmTimer();
	init_UART0();	//UART is on screw-terminal and usb
	init_UART1();	//only on screw-terminals
	uint8_t startcmd[2];
	startcmd[0] = cmdresetMCU;
	startcmd[1] = eot;
	serial_out0(startcmd, 2);

	test();

	sei();
	while(1){
		myParser.checkparser();
	}
}
void test(){
	/*
	for ( uint8_t command = setCI0+16; command <= setCI0+23; command++ ){
		testflush(command);
		testflush(0x03);
		testflush(0x00);
		testflush(eot);
	}
	for ( uint8_t command = setVI0+16; command <= setVI0+23; command++ ){
		testflush(command);
		testflush(0x00);
		testflush(0x00);
		testflush(eot);
	}
	*/
	
	
	
}
void testflush(uint8_t testChar){
	uint8_t tempRec = testChar;
	InBufferUart0[InBufferUart0pointer] = tempRec;
	InBufferUart0pointer++;
	if(tempRec == eot){
		myParser.inc_parser_cnt();
	}
}
void init_io(){
	//__________________________________________________________________________________
	//pins noch anzupassen

	io[0]	=new io_pin(&DDRC, &PORTC, &PINC, 1 );
	io[1]	=new io_pin(&DDRC, &PORTC, &PINC, 3 );
	io[2]	=new io_pin(&DDRC, &PORTC, &PINC, 5 );
	io[3]	=new io_pin(&DDRC, &PORTC, &PINC, 7 );
	io[4]	=new io_pin(&DDRA, &PORTA, &PINA, 6 );
	io[5]	=new io_pin(&DDRA, &PORTA, &PINA, 4 );
	io[6]	=new io_pin(&DDRA, &PORTA, &PINA, 2 );
	io[7]	=new io_pin(&DDRA, &PORTA, &PINA, 0 );
	
	io[8]	=new io_pin(&DDRC, &PORTC, &PINC, 0 );
	io[9]	=new io_pin(&DDRC, &PORTC, &PINC, 2 );
	io[10]	=new io_pin(&DDRC, &PORTC, &PINC, 4 );
	io[11]	=new io_pin(&DDRC, &PORTC, &PINC, 6 );
	io[12]	=new io_pin(&DDRA, &PORTA, &PINA, 7 );
	io[13]	=new io_pin(&DDRA, &PORTA, &PINA, 5 );
	io[14]	=new io_pin(&DDRA, &PORTA, &PINA, 3 );
	io[15]	=new io_pin(&DDRA, &PORTA, &PINA, 1 );
	//__________________________________________________________________________________
	io[16]	=new io_pin(&DDRD, &PORTD, &PIND, 7 );
	io[17]	=new io_pin(&DDRG, &PORTG, &PING, 1 );
	io[18]	=new io_pin(&DDRL, &PORTL, &PINL, 7 );
	io[19]	=new io_pin(&DDRL, &PORTL, &PINL, 5 );
	io[20]	=new io_pin(&DDRL, &PORTL, &PINL, 3 );
	io[21]	=new io_pin(&DDRL, &PORTL, &PINL, 1 );
	io[22]	=new io_pin(&DDRB, &PORTB, &PINB, 3 );
	io[23]	=new io_pin(&DDRB, &PORTB, &PINB, 1 );
	
	io[24]	=new io_pin(&DDRG, &PORTG, &PING, 2 );
	io[25]	=new io_pin(&DDRG, &PORTG, &PING, 0 );
	io[26]	=new io_pin(&DDRL, &PORTL, &PINL, 6 );
	io[27]	=new io_pin(&DDRL, &PORTL, &PINL, 4 );
	io[28]	=new io_pin(&DDRL, &PORTL, &PINL, 2 );
	io[29]	=new io_pin(&DDRL, &PORTL, &PINL, 0 );
	io[30]	=new io_pin(&DDRB, &PORTB, &PINB, 2 );
	io[31]	=new io_pin(&DDRB, &PORTB, &PINB, 0 );

	
	io[32]	=new io_pin(&DDRH, &PORTH, &PINH, 4 );
	io[33]	=new io_pin(&DDRH, &PORTH, &PINH, 3 );
	io[34]	=new io_pin(&DDRE, &PORTE, &PINE, 3 );
	io[35]	=new io_pin(&DDRE, &PORTE, &PINE, 5 );
	io[36]	=new io_pin(&DDRJ, &PORTJ, &PINJ, 1 );
	io[37]	=new io_pin(&DDRJ, &PORTJ, &PINJ, 0 );
	io[38]	=new io_pin(&DDRH, &PORTH, &PINH, 1 );
	io[39]	=new io_pin(&DDRH, &PORTH, &PINH, 0 );
	
	

	//__________________________________________________________________________________
}
void init_pwmTimer(){
	
	OCR3A	=	624;		//624 = alter wert-->50Hz
	TIMSK3	=	1<<OCIE3A;	//Timer/Countern3, Output Compare A Match Interrupt Enable
	TCCR3B	=	(1<<CS32) | (1<<WGM32);	//prescaler:256 ; CTC mode
}
ISR (TIMER3_COMPA_vect){
	for(uint8_t i = 0; i < 40; i++){
		io[i]->trigger();
	}
}

ISR (ADC_vect){
	myADC.sample();
}
int16_t freeRam () {
	extern int __heap_start, *__brkval;
	int v;
	return (int16_t) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
