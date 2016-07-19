#include "touch.h"

void touch_Init(void) {
	touch.threshold = TOUCH_DEF_THRESHOLD;
	// fastest prescaler, capture on rising edge
	TCCR1B |= (1 << CS10);
	// enable interrupts
	TIMSK1 |= (1 << TOIE1);

	// ADC initialization
	// select AVCC as reference + GND as ADC input
	ADMUX = (1 << REFS0) | 0x0F;
	// enable + prescaler = 2 -> 500kHz
	ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADIE);

	// charge capacitor from touch pin to ground
	PORTC |= (1 << PC0);
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

ISR(TIMER1_OVF_vect) {
	// disable pull-up on touch pin
	PORTC &= ~(1 << PC0);
	// select channel 0 (PC0)
	ADMUX = (1 << REFS0);
	// sample ADC
	ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect) {
	touch.CaptureValue = ADC;
	// switch ADC input to ground again (discharge sampling capacitor)
	ADMUX = (1 << REFS0) | 0x0F;
	// enable pull-up on touch pin
	PORTC |= (1 << PC0);
	// evaluate result
	if (touch.CaptureValue > touch.threshold + TOUCH_HYSTERESIS) {
		touch.touching = 1;
		touch.count++;
		if (touch.count >= 8) {
			// has been continuously touched for some time
			touch.holding = 1;
		}
	} else if (touch.touching
			&& touch.CaptureValue < touch.threshold - TOUCH_HYSTERESIS) {
		touch.touching = 0;
		touch.holding = 0;
		if (touch.count < 8) {
			// has been touched for a reasonable short time
			touch.tapped = 1;
		}
		touch.count = 0;
	}
}

