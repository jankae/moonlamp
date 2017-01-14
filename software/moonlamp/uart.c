#include "uart.h"

void uart_init(void) {
	UCSRA |= (1 << U2X);
	UCSRB |= (1 << TXEN) | (1 << RXEN);
	UCSRC |= (3 << UCSZ0);

	UBRRH = UBRR_VAL >> 8;
	UBRRL = UBRR_VAL & 0xFF;
}
void uart_putc(unsigned char c) {
	while (!(UCSRA & (1 << UDRE)))
		;

	UDR = c;
}
uint8_t uart_getc(void) {
	while (!(UCSRA & (1 << RXC)))
		;
	return UDR ;
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
