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
#include <util/delay.h>

extern volatile uint8_t  InBufferUart0[256];
extern volatile uint8_t InBufferUart0pointer;

volatile AnalogDigitalConverter myADC;
volatile cmdParser myParser;
io_pin* io[40];



int main(void)
{
DDRB |= 0x80;//LED
	init_io();
	init_pwmTimer();
	init_UART0();
	init_UART1();
	

	test();

	sei();
	while(1){
		myParser.checkparser();
	}
	
}
void test(){
	/*testflush(163);
	testflush(0);
	testflush(0);
	testflush(eot);
	
	for ( uint8_t command = setCA0; command <= setCA15; command++ ){
		testflush(command);
		testflush(0x04);
		testflush(0x00);
		testflush(eot);

	}
	for ( uint8_t command = setCI0; command <= setCI39; command++ ){
	testflush(command);
	testflush(0x04);
	testflush(0x00);
	testflush(eot);

	}
	
	testflush(setVI0+16);
	testflush(0x0F);
	testflush(0x07);
	testflush(eot);
	
	testflush(setCI0+16);
	testflush(0x04);
	testflush(0x00);
	testflush(eot);
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
	io_config init_config=invertOutput;
	//__________________________________________________________________________________
	//pins noch anzupassen

	io[0]	=new io_pin(&DDRC, &PORTC, &PINC, 1, init_config);
	io[1]	=new io_pin(&DDRC, &PORTC, &PINC, 3, init_config);
	io[2]	=new io_pin(&DDRC, &PORTC, &PINC, 5, init_config);
	io[3]	=new io_pin(&DDRC, &PORTC, &PINC, 7, init_config);
	io[4]	=new io_pin(&DDRA, &PORTA, &PINA, 6, init_config);
	io[5]	=new io_pin(&DDRA, &PORTA, &PINA, 4, init_config);
	io[6]	=new io_pin(&DDRA, &PORTA, &PINA, 2, init_config);
	io[7]	=new io_pin(&DDRA, &PORTA, &PINA, 0, init_config);
	
	io[8]	=new io_pin(&DDRC, &PORTC, &PINC, 0, init_config);
	io[9]	=new io_pin(&DDRC, &PORTC, &PINC, 2, init_config);
	io[10]	=new io_pin(&DDRC, &PORTC, &PINC, 4, init_config);
	io[11]	=new io_pin(&DDRC, &PORTC, &PINC, 6, init_config);
	io[12]	=new io_pin(&DDRA, &PORTA, &PINA, 7, init_config);
	io[13]	=new io_pin(&DDRA, &PORTA, &PINA, 5, init_config);
	io[14]	=new io_pin(&DDRA, &PORTA, &PINA, 3, init_config);
	io[15]	=new io_pin(&DDRA, &PORTA, &PINA, 1, init_config);
	//__________________________________________________________________________________
	io[16]	=new io_pin(&DDRD, &PORTD, &PIND, 7, init_config);
	io[17]	=new io_pin(&DDRG, &PORTG, &PING, 1, init_config);
	io[18]	=new io_pin(&DDRL, &PORTL, &PINL, 7, init_config);
	io[19]	=new io_pin(&DDRL, &PORTL, &PINL, 5, init_config);
	io[20]	=new io_pin(&DDRL, &PORTL, &PINL, 3, init_config);
	io[21]	=new io_pin(&DDRL, &PORTL, &PINL, 1, init_config);
	io[22]	=new io_pin(&DDRB, &PORTB, &PINB, 3, init_config);
	io[23]	=new io_pin(&DDRB, &PORTB, &PINB, 1, init_config);
	
	io[24]	=new io_pin(&DDRG, &PORTG, &PING, 2, init_config);
	io[25]	=new io_pin(&DDRG, &PORTG, &PING, 0, init_config);
	io[26]	=new io_pin(&DDRL, &PORTL, &PINL, 6, init_config);
	io[27]	=new io_pin(&DDRL, &PORTL, &PINL, 4, init_config);
	io[28]	=new io_pin(&DDRL, &PORTL, &PINL, 2, init_config);
	io[29]	=new io_pin(&DDRL, &PORTL, &PINL, 0, init_config);
	io[30]	=new io_pin(&DDRB, &PORTB, &PINB, 2, init_config);
	io[31]	=new io_pin(&DDRB, &PORTB, &PINB, 0, init_config);
	//pins noch anzupassen
	
	io[32]	=new io_pin(&DDRH, &PORTH, &PINH, 5, init_config);
	io[33]	=new io_pin(&DDRH, &PORTH, &PINH, 6, init_config);
	io[34]	=new io_pin(&DDRE, &PORTE, &PINE, 4, init_config);
	io[35]	=new io_pin(&DDRE, &PORTE, &PINE, 5, init_config);
	io[36]	=new io_pin(&DDRG, &PORTG, &PING, 5, init_config);
	io[37]	=new io_pin(&DDRE, &PORTE, &PINE, 3, init_config);
	io[38]	=new io_pin(&DDRH, &PORTH, &PINH, 3, init_config);
	io[39]	=new io_pin(&DDRH, &PORTH, &PINH, 4, init_config);
	//__________________________________________________________________________________
}
void init_pwmTimer(){
	
	OCR3A	=	624;		//-->50Hz
	TIMSK3	=	1<<OCIE3A;	//Timer/Countern3, Output Compare A Match Interrupt Enable
	TCCR3B	=	(1<<CS32) | (1<<WGM32);	//prescaler:256 ; CTC mode
}
ISR (TIMER3_COMPA_vect){
	for(uint8_t i = 0; i < 39; i++){
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
