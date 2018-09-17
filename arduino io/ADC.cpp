/*
 * ADC.cpp
 *
 * Created: 30.09.2017 12:04:14
 *  Author: Flo
 */
 #include "ADC.h"
 #include <avr/io.h>



AnalogDigitalConverter::AnalogDigitalConverter(){
	for (uint8_t i = 0; i < 16; i++)
	{
		sensor_en[i] = true;
		tp_en[i] = true;
		m_sensortype[i] = pt2000;
	}
	

	ADMUX=ADMUX_std|ADMUX_ch0;
	ADCSRA=ADCSRA_std;
	ADCSRB=ADCSRB_std;
	this->actual_measure_channel=0;
	TCCR1B=(1<<CS10)|(1<<WGM12);		//Timer 1 On, Prescaler: 1
	TIMSK1=(1<<OCIE1B);					//Timer/Counter1 Compare match B interupt enable
	OCR1A=F_CPU/(samplerate*16L);		//Zeitpunkt der Messungen F_CPU / (OCR1A*16) = F_SAMPLE = 500Hz
	DIDR0=255;
	DIDR2=255;
}
void AnalogDigitalConverter::sample() volatile
{
	int16_t temp=0;
	switch(this->actual_measure_channel){
		case 0:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch1;
		}break;
		case 1:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch2;
		}break;
		case 2:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch3;
		}break;
		case 3:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch4;
		}break;
		case 4:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch5;
		}break;
		case 5:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch6;
		}break;
		case 6:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch7;
		}break;
		case 7:{
			temp=ADC;
			ADCSRB=ADCSRB_std | ADCSRB_ch8_15;
			ADMUX=ADMUX_std|ADMUX_ch8;
		}break;
		case 8:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch9;
		}break;
		case 9:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch10;
		}break;
		case 10:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch11;
		}break;
		case 11:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch12;
		}break;
		case 12:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch13;
		}break;
		case 13:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch14;
		}break;
		case 14:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch15;
		}break;
		case 15:{
			temp=ADC;
			ADMUX=ADMUX_std|ADMUX_ch0;
			ADCSRB=ADCSRB_std;
		}break;
	}

	if(tp_en[actual_measure_channel]){
		if(sensor_en[actual_measure_channel]){
			if(m_sensortype[actual_measure_channel] == pt1000){
				outputvalue[actual_measure_channel]=ConvertPT1000ADCvalToTemperature(tp[actual_measure_channel].sample(temp));
			}
			if(m_sensortype[actual_measure_channel] == pt2000){
				outputvalue[actual_measure_channel]=ConvertPT2000ADCvalToTemperature(tp[actual_measure_channel].sample(temp));
			}
		}else{
			outputvalue[actual_measure_channel]=tp[actual_measure_channel].sample(temp);
		}
		
	}else{
		if(sensor_en[actual_measure_channel]){
			if(m_sensortype[actual_measure_channel] == pt1000){
				outputvalue[actual_measure_channel]=ConvertPT1000ADCvalToTemperature(temp);
			}
			if(m_sensortype[actual_measure_channel] == pt2000){
				outputvalue[actual_measure_channel]=ConvertPT2000ADCvalToTemperature(temp);
			}
		}else{
			outputvalue[actual_measure_channel]=temp;
		}
	}

	if(actual_measure_channel<15){
		actual_measure_channel++;
	}else{
		actual_measure_channel=0;
	}
}
int16_t AnalogDigitalConverter::getoutput(uint8_t channel) volatile
{
	if (channel>15){
		return 0xFFFF;
	}else{
		return this->outputvalue[channel];
	}

}
int16_t AnalogDigitalConverter::ConvertPT1000ADCvalToTemperature(int16_t ADCval) volatile
{
	if(ADCval < _pt1000Start){
		ADCval=_pt1000Start;
	}
	if(ADCval > (_pt1000Start + _pt1000size-1)){
		ADCval = _pt1000Start + _pt1000size-1;
	}
	int16_t offset=ADCval-_pt1000Start;
	
	return (int16_t)pgm_read_word(&_pt1000[offset]);
}
int16_t AnalogDigitalConverter::ConvertPT2000ADCvalToTemperature(int16_t ADCval) volatile
{
	if(ADCval < _pt2000Start){
		ADCval=_pt2000Start;
	}
	if(ADCval > (_pt2000Start + _pt2000size-1)){
		ADCval = _pt2000Start + _pt2000size-1;
	}
	int16_t offset=ADCval-_pt2000Start;
	
	return (int16_t)pgm_read_word(&_pt2000[offset]);
}
uint8_t AnalogDigitalConverter::getconfig(uint8_t channel) volatile
{
	if(channel > 15 || channel < 0){
		return 0;
	}
	uint8_t config = 0;
	if(tp_en[channel]){
		config|=1;
	}
	if(sensor_en[channel]){
		config|=2;
	}
	config|=((uint8_t)(m_sensortype[channel]) << 2);
	return config;
}
bool AnalogDigitalConverter::setconfig(uint8_t channel, uint8_t config) volatile
{
	if(channel > 15 || channel < 0){
		return true;
	}

	if((config & 1) == 1){
		tp_en[channel]=true;
	}else{
		tp_en[channel]=false;
	}

	if((config & 2) == 2){
		sensor_en[channel] = true;
	}else{
		sensor_en[channel] = false;
	}

	m_sensortype[channel] = (sensortype)((config & 12) >> 2);
	return false;
}
ISR(TIMER1_COMPB_vect){///zum löschen des interupt bits
	asm("nop");
}
