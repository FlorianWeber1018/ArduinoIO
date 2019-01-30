/*
 * ADC.h
 *
 * Created: 30.09.2017 12:04:28
 *  Author: Flo
 */ 
 
 ///////////////////////////////////nur gültig für arduino mega2560
#ifndef ADC_H_
#define ADC_H_

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "main.h"
#include "tiefpass.h"
#define samplerate		111L									//max 150Hz
#define ADCSRB_std		(1<<ADTS2)|(1<<ADTS0)					//Auto trigger source: Timer/Counter1 Compare Match B
#define ADCSRA_std		(1<<ADATE)|(1<<ADIE)|(1<<ADEN)|5		//ADC enable, Auto trigger mode, interupt by completed conversation, prescaler 128
#define ADMUX_std		(1<<REFS0)|(1<<REFS1)					//internal reference voltage:AVCC,2.56V
#define ADMUX_ch0		0
#define ADMUX_ch1		1
#define ADMUX_ch2		2
#define ADMUX_ch3		3
#define ADMUX_ch4		4
#define ADMUX_ch5		5
#define ADMUX_ch6		6
#define ADMUX_ch7		7
#define ADMUX_ch3		3
#define ADCSRB_ch8_15	(1<<MUX5)
#define ADMUX_ch8		0
#define ADMUX_ch9		1
#define ADMUX_ch10		2
#define ADMUX_ch11		3
#define ADMUX_ch12		4
#define ADMUX_ch13		5
#define ADMUX_ch14		6
#define ADMUX_ch15		7




enum sensortype{pt1000=0, pt2000=1};	


const int16_t _pt2000[] PROGMEM = {
#include "pt2000.csv"
};
const int16_t _pt2000Start  = 600;
const int16_t _pt2000size = 507;


const int16_t _pt1000[] PROGMEM = {
#include "pt1000.csv"
};
const int16_t _pt1000Start = 400;
const int16_t _pt1000size = 431;


class AnalogDigitalConverter{
	public:
		AnalogDigitalConverter();
		void sample() volatile;
		int16_t getoutput(uint8_t channel) volatile;
		uint8_t getconfig(uint8_t channel) volatile;
		bool setconfig(uint8_t channel, uint8_t config) volatile;
		int16_t ConvertPT1000ADCvalToTemperature(int16_t ADCval) volatile;
		int16_t ConvertPT2000ADCvalToTemperature(int16_t ADCval) volatile;
	private:
		volatile iirlowpass tp[16];
		

		volatile sensortype m_sensortype[16];// = {pt2000,pt2000,pt2000,pt2000,pt2000,pt2000,pt2000,pt2000,pt2000,pt2000,pt2000,pt2000,pt2000,pt2000,pt2000,pt2000};
		volatile bool sensor_en[16];// = {true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true};
		volatile bool tp_en[16];// = {true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true};
		volatile uint8_t actual_measure_channel;
		volatile int16_t outputvalue[16];

};




#endif /* ADC_H_ */