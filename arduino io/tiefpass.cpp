/*
 * tiefpass.cpp
 *
 * Created: 22.10.2017 18:28:58
 *  Author: Flo
 */ 
 #include "tiefpass.h"
 #include <stdlib.h>
int16_t iirlowpass::sample(int16_t NewSample) volatile
{
	 //shift the old samples
	 int32_t y=0;
	 for(uint8_t n=Ntap-1; n>0; n--){
		x[n] = x[n-1];
	 }

	  x[0] = NewSample;
	  for(uint8_t n=0; n<Ntap; n++){
			y += (int32_t)FIRCoef[n] * (int32_t)x[n];
	  }
	 
	  
	  return y>>18;

}
iirlowpass::iirlowpass(){

	FIRCoef[0] = 22780;
	FIRCoef[1] = 23402;
	FIRCoef[2] = 23896;
	FIRCoef[3] = 24252;
	FIRCoef[4] = 24469;
	FIRCoef[5] = 24541;
	FIRCoef[6] = 24469;
	FIRCoef[7] = 24252;;
	FIRCoef[8] = 23896;
	FIRCoef[9] = 23402;
	FIRCoef[10] = 22780;
	x=(int16_t*)malloc(2*(Ntap));
	
};
iirlowpass::~iirlowpass(){
	free(x);
}