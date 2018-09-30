/*
 * io.cpp
 *
 * Created: 18.10.2017 21:18:04
 *  Author: Flo
 */
 #include "io.h"
 io_pin::io_pin(volatile uint8_t* DDR, volatile uint8_t* PORT_OUT, volatile uint8_t* PORT_IN, uint8_t PIN){
	 this->DDR=DDR;
	 this->PORT_OUT=PORT_OUT;
	 this->PORT_IN=PORT_IN;
	 this->PIN=PIN;
	 init_pinConfig(invertOutput);
	 this->DutyCycle = 0;
	 this->cnt = 0;
	 
 }
void io_pin::init_pinConfig(io_config _config) volatile
{
		switch(_config){
			case ninvertInput:{
				*DDR &= ~(1<<PIN);
				*PORT_OUT |= 1<<PIN;
			}break;
			case invertInput:{
				*DDR &= ~(1<<PIN);
				*PORT_OUT |= 1<<PIN;
			}break;
			case ninvertOutput:{
				*DDR |= 1<<PIN;
				*PORT_OUT &= ~(1<<PIN);
			}break;
			case invertOutput:{
				*DDR |= 1<<PIN;
				*PORT_OUT |= 1<<PIN;
			}break;
			case ninvertPwmOutput:{
				cnt=0;
				DutyCycle=0;
				*DDR |= 1<<PIN;
				*PORT_OUT &= ~(1<<PIN);
			}break;
			case invertPwmOutput:{
				cnt=0;
				DutyCycle=0;
				*DDR |= 1<<PIN;
				*PORT_OUT |= 1<<PIN;
			}
		}
	this->config=_config;
}

 io_pin::~io_pin(){

 }
 uint8_t io_pin::get() volatile
 {
	switch(config){
		case ninvertInput:{
			if((((*PORT_IN)>>PIN) & 1)==1){
				return 1;
			}else{
				return 0;
			}
		}break;
		case invertInput:{
			if((((*PORT_IN)>>PIN) & 1)==1){
				return 0;
			}else{
				return 1;
			}
		}break;
		case ninvertOutput:{
			if((((*PORT_OUT)>>PIN) & 1)==1){
				return 1;
				}else{
				return 0;
			}
		}break;
		case invertOutput:{
			if((((*PORT_OUT)>>PIN) & 1)==1){
				return 0;
				}else{
				return 1;
			}
		}break;
		case ninvertPwmOutput:{
			return DutyCycle;
		}break;
		case invertPwmOutput:{
			return DutyCycle;
		}break;

	}
	return 0;
 }
 void io_pin::set(uint8_t value) volatile
 {
 	switch(this->config){
		case ninvertInput:{
			
		}break;
		case invertInput:{
			
		}break;
		case ninvertOutput:{
			if(value){
				*PORT_OUT |= 1<<PIN;
			}else{
				*PORT_OUT &= ~(1<<PIN);
			}
		}break;
		case invertOutput:{
			if(value){
				*PORT_OUT &= ~(1<<PIN);
			}else{
				*PORT_OUT |= 1<<PIN;
			}
		}break;
		case ninvertPwmOutput:{
			DutyCycle = value;
		}break;
		case invertPwmOutput:{
			DutyCycle = value;
		}
	}
 }
 void io_pin::setconfig(uint8_t config) volatile
 {
	if(this->config != static_cast<io_config>(config))
	{
		switch(config){
			case ninvertInput:{
				*DDR &= ~(1<<PIN);
				*PORT_OUT |= 1<<PIN;
			}break;
			case invertInput:{
				*DDR &= ~(1<<PIN);
				*PORT_OUT |= 1<<PIN;
			}break;
			case ninvertOutput:{
				*DDR |= 1<<PIN;
				*PORT_OUT &= ~(1<<PIN);
			}break;
			case invertOutput:{
				*DDR |= 1<<PIN;
				*PORT_OUT |= 1<<PIN;
			}break;
			case ninvertPwmOutput:{
				cnt=0;
				DutyCycle=0;
				*DDR |= 1<<PIN;
				*PORT_OUT &= ~(1<<PIN);
			}break;
			case invertPwmOutput:{
				cnt=0;
				DutyCycle=0;
				*DDR |= 1<<PIN;
				*PORT_OUT |= 1<<PIN;
			}
		}
		
	}
	this->config=static_cast<io_config>(config);
	
 }
 uint8_t io_pin::getconfig() volatile
 {
	 return static_cast<uint8_t>(config);
 }
 void io_pin::trigger() volatile
 {
	if(config == ninvertPwmOutput){
		if(cnt > DutyCycle){
			*PORT_OUT &= ~(1<<PIN);		//switch off
		}else if(cnt == 0 && DutyCycle != 0){
			*PORT_OUT |= 1<<PIN;		//switch on
		}
	}else if(config == invertPwmOutput){
		if(cnt > DutyCycle){
			*PORT_OUT |= 1<<PIN;		//switch off
		}else if(cnt == 0 && DutyCycle != 0){
			*PORT_OUT &= ~(1<<PIN);		//switch on
		}
	}
	cnt++;
 }