#include "uart.h"

void uart_init(void) {
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
	UCSR0C |= (3 << UCSZ00);

	UBRR0H = UBRR_VAL >> 8;
	UBRR0L = UBRR_VAL & 0xFF;
}
void uart_putc(unsigned char c) {
	while (!(UCSR0A & (1 << UDRE0)))
		;

	UDR0 = c;
}
uint8_t uart_getc(void) {
	while (!(UCSR0A & (1 << RXC0)))
		;
	return UDR0;
}
void uart_puts(char *s) {
	while (*s) {
		uart_putc(*s);
		s++;
	}
}
