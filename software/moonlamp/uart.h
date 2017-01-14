/*
 * uart.h
 *
 *  Created on: 16.05.2012
 *      Author: jan
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include "dates.h"

#define UBRR_VAL 103 //9600baud@8MHz(U2X = 1)

void uart_init(void);
void uart_putc(unsigned char c);
void uart_puts(char *s);

void uart_putDate(struct date date);
void uart_putTime(struct time time);

void uart_putInteger(int16_t i);

#endif /* UART_H_ */
