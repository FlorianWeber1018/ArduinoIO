/*
 * button_parallel.h
 *
 * Created: 31.07.2017 12:40:02
 *  Author: Flo
 */ 


#ifndef BUTTON_PARALLEL_H_
#define BUTTON_PARALLEL_H_

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

class button
{
	public:
		button(volatile uint8_t* _DDR, volatile uint8_t* _PORT_OUT, volatile uint8_t* _PORT_IN, uint8_t _PIN, uint16_t samplerate);
		~button();
		void sample();
	private:
		volatile uint8_t* PORT_IN;
		volatile uint8_t* PORT_OUT;
		uint8_t PIN;
		uint16_t bounce_number;
		bool last_state=true;
		bool count_enable=false;
		uint16_t count;
};




#endif /* BUTTON_PARALLEL_H_ */