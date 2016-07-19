#include "systime.h"

void time_Init() {
	// CTC-Mode
	TCCR0A |= (1 << WGM01);
	// Overflow at 124
	OCR0A = 124;
	// prescaler = 8
	// -> overflows every ms
	TCCR0B |= (1 << CS01);
	TIMSK0 |= (1 << OCIE0A);
}
void time_WaitMs(uint16_t ms) {
	uint16_t timeout = time_SetTimeout(ms);
	while (!time_TimeoutElapsed(timeout))
		;
}
uint16_t time_SetTimeout(uint16_t ms) {
	uint16_t timeout;
	cli();
	timeout = time.ms;
	sei();
	timeout += ms;
	return timeout;
}
uint8_t time_TimeoutElapsed(uint16_t timeout) {
	uint8_t ret = 1;
	cli();
	uint16_t timebuf = time.ms;
	sei();
	if ((timebuf - timeout) & 0x8000)
		ret = 0;
	return ret;
}

ISR(TIMER0_COMPA_vect) {
	time.ms++;
}
