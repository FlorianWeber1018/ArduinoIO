/*
 * button_parallel.cpp
 *
 * Created: 31.07.2017 12:37:31
 *  Author: Flo
 */ 
 #include "main.h"
 #include "button_parallel.h"
 #include <avr/io.h>

 button::button(volatile uint8_t* _DDR, volatile uint8_t* _PORT_OUT,volatile uint8_t* _PORT_IN, uint8_t _PIN, uint16_t samplerate){
	count=0;
	*_DDR &= ~(1<<_PIN);			//data direction
	*_PORT_OUT |= (1<<_PIN);		//pull-up
	PORT_OUT=_PORT_OUT;
	PORT_IN=_PORT_IN;				//input port
	PIN=_PIN;						//input pin
	bounce_number=samplerate/20;	//bouncetime= bounce number/samplerate(hier:boucetime=50ms)
	if(bounce_number==0){bounce_number=1;}
 }
 button::~button(){
	*(this->PORT_OUT) &= ~(1<<PIN);			//pull-up
 }
 void button::sample(){

	bool input_state;
	//////////////////////////////////////////////////////////////////////////
	if(((*(this->PORT_IN))&(1<<(this->PIN)))==0){
		input_state=false;
	}else{
		input_state=true;
	}
	//////////////////////////////////////////////////////////////////////////
	if(input_state!=this->last_state){
		if(input_state){	//0->1 übergang (losgelassen)
			this->count_enable=false;
			if(this->count >= this->bounce_number){
				//action
			}
			this->count=0;
		}else{				//1->0 übergang (gedrückt)
			this->count_enable=true;
		}
	}

	if(input_state==last_state){
		if(count_enable){
			this->count++;
		}
	}
	last_state=input_state;
 }

 