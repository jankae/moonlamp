/*
 * uart.h
 *
 *  Created on: 16.05.2012
 *      Author: jan
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

#define UBRR_VAL 12 //9600baud@1MHz(U2X = 1)

void uart_init(void);
void uart_putc(unsigned char c);
uint8_t uart_getc(void);
void uart_puts(char *s);

#endif /* UART_H_ */
