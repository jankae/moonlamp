#include "touch.h"

void touch_Init(void) {
	touch.threshold = TOUCH_DEF_THRESHOLD;
	// fastest prescaler, capture on rising edge
	TCCR1B |= (1 << CS10) | (1 << ICES1);
	OCR1A = 30000;
	// enable interrupts
	TIMSK1 |= (1 << OCIE1A) | (1 << TOIE1);
}

uint8_t touch_Tapped(void) {
	uint8_t ret = 0;
	uint8_t sreg = SREG;
	cli();
	if (touch.tapped) {
		touch.tapped = 0;
		ret = 1;
	}
	SREG = sreg;
	return ret;
}

uint8_t touch_Holding(void) {
	return touch.holding;
}

ISR(TIMER1_COMPA_vect) {
	// Set PORTB0 low
	DDRB |= (1 << PB0);
	// store captured time
	touch.CaptureValue -= touch.CaptureValue / 16;
	touch.CaptureValue += ICR1;
	// evaluate result
	if (touch.CaptureValue > touch.threshold + TOUCH_HYSTERESIS) {
		touch.touching = 1;
		touch.count++;
		if (touch.count >= 8) {
			// has been continuously touched for some time
			touch.holding = 1;
		}
	} else if (touch.CaptureValue < touch.threshold - TOUCH_HYSTERESIS) {
		touch.touching = 0;
		touch.holding = 0;
		if (touch.count < 8) {
			// has been touched for a reasonable short time
			touch.tapped = 1;
		}
		touch.count = 0;
	}
}

ISR(TIMER1_OVF_vect) {
	// configure PORTB0 as input
	DDRB &= ~(1 << PB0);
}
