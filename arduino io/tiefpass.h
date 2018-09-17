/*
 * tiefpass.h
 *
 * Created: 22.10.2017 18:29:10
 *  Author: Flo
 */ 
#ifndef TIEFPASS_H_
#define TIEFPASS_H_


#include <inttypes.h>

#define Ntap 11
#define DCgain 262144

class iirlowpass{
	public:
		int16_t sample(int16_t input)  volatile;
		iirlowpass();
		~iirlowpass();
	private:
		 volatile int16_t FIRCoef[Ntap];
		 int16_t* x;

};




#endif /* TIEFPASS_H_ */