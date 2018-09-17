/*
 * io.h
 *
 * Created: 11.10.2017 19:30:35
 *  Author: Flo
 */ 
 

#ifndef IO_H_
#define IO_H_


#include <stdbool.h>
#include <inttypes.h>

enum io_config{ 
	ninvertInput		=	0, 
	invertInput			=	1, 
	ninvertOutput		=	2, 
	invertOutput		=	3, 
	ninvertPwmOutput	=	4, 
	invertPwmOutput		=	5
};

class io_pin{

public:
	io_pin(volatile uint8_t* DDR, volatile uint8_t* PORT_OUT, volatile uint8_t* PORT_IN, uint8_t PIN, io_config config);
	~io_pin();
	uint8_t get() volatile;
	void set(uint8_t value) volatile;
	void setconfig(uint8_t) volatile;
	uint8_t getconfig() volatile;
	void trigger() volatile;
private:
	volatile io_config config;
	volatile uint8_t* PORT_IN;
	volatile uint8_t* PORT_OUT;
	volatile uint8_t* DDR;
	volatile uint8_t PIN;
	volatile uint8_t DutyCycle;
	volatile uint8_t cnt;
};





#endif /* IO_H_ */