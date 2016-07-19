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
	return UDR0 ;
}
void uart_puts(char *s) {
	while (*s) {
		uart_putc(*s);
		s++;
	}
}

void uart_putDate(struct date date) {
	char buf[11];
	buf[0] = date.day / 10 + '0';
	buf[1] = date.day % 10 + '0';
	buf[2] = '.';
	buf[3] = date.month / 10 + '0';
	buf[4] = date.month % 10 + '0';
	buf[5] = '.';
	buf[6] = '2';
	buf[7] = '0';
	buf[8] = date.year / 10 + '0';
	buf[9] = date.year % 10 + '0';
	buf[10] = 0;
	uart_puts(buf);
}

void uart_putTime(struct time time) {
	char buf[9];
	buf[0] = time.hour / 10 + '0';
	buf[1] = time.hour % 10 + '0';
	buf[2] = ':';
	buf[3] = time.minute / 10 + '0';
	buf[4] = time.minute % 10 + '0';
	buf[5] = ':';
	buf[6] = time.second / 10 + '0';
	buf[7] = time.second % 10 + '0';
	buf[8] = 0;
	uart_puts(buf);
}

void uart_putInteger(int16_t i) {
	char buf[7];
	char *p = buf;
	if (i < 0) {
		*p++ = '-';
		i = -i;
	}
	if (i > 9999) {
		*p++ = (i / 10000) % 10 + '0';
	}
	if (i > 999) {
		*p++ = (i / 1000) % 10 + '0';
	}
	if (i > 99) {
		*p++ = (i / 100) % 10 + '0';
	}
	if (i > 9) {
		*p++ = (i / 10) % 10 + '0';
	}
	*p++ = i % 10 + '0';
	*p = 0;
	uart_puts(buf);
}
