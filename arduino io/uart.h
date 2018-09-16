/*
 * uart.h
 *
 * Created: 08.10.2017 19:06:55
 *  Author: Flo
 */ 


#ifndef UART_H_
#define UART_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "COMprotocol.h"
#include "main.h"
#include "cmdParser.h"
#include "list__array_uint8_t.h"
#define BAUD 57600L
#define BAUDdebug 19200L
#define UCSR0B_std ((1<<TXEN0)	| (1<<RXEN0) | (1<<RXCIE0))	//enable TX, enable RX on UART0, enable rx interrupt
#define UCSR1B_std ((1<<TXEN1)	| (1<<RXEN1) | (1<<RXCIE1))	//enable TX, enable RX on UART1, enable rx interrupt
#define UCSR0C_std (1<<UCSZ00)|(1<<UCSZ01)					//Asynchronous USART0; 1 stop bit; 8 data bit
#define UCSR1C_std (1<<UCSZ10)|(1<<UCSZ11)					//Asynchronous USART1; 1 stop bit; 8 data bit




void serial_out0(uint8_t data);
void serial_out0(uint8_t* data, uint8_t count);
void serial_out1(uint8_t data);
void init_UART1();
void init_UART0();
void toggleLed();


#endif /* UART_H_ */