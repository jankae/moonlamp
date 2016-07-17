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
	time_SetTimeout(ms);
	while (!time_TimeoutElapsed())
		;
}
void time_SetTimeout(uint16_t ms) {
	cli();
	time.ms = ms;
	sei();
}
uint8_t time_TimeoutElapsed(void) {
	uint8_t ret = 0;
	cli();
	if (!time.ms) {
		ret = 1;
	}
	sei();
	return ret;
}

ISR(TIMER0_COMPA_vect) {
	if (time.ms) {
		time.ms--;
	}
}
