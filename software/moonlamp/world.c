#include "world.h"

void world_init(void) {
	WORLD_TIMEZONE1_DDR |= (1 << WORLD_TIMEZONE1_PIN);
	WORLD_TIMEZONE2_DDR |= (1 << WORLD_TIMEZONE2_PIN);
	WORLD_TIMEZONE3_DDR |= (1 << WORLD_TIMEZONE3_PIN);
	WORLD_TIMEZONE4_DDR |= (1 << WORLD_TIMEZONE4_PIN);
	WORLD_TIMEZONE5_DDR |= (1 << WORLD_TIMEZONE5_PIN);
	WORLD_TIMEZONE6_DDR |= (1 << WORLD_TIMEZONE6_PIN);
	WORLD_TIMEZONE7_DDR |= (1 << WORLD_TIMEZONE7_PIN);
	WORLD_TIMEZONE8_DDR |= (1 << WORLD_TIMEZONE8_PIN);
	WORLD_TIMEZONE9_DDR |= (1 << WORLD_TIMEZONE9_PIN);

	// build 'switch-off'-masks
	world.MaskPORTB = 0xFF;
	world.MaskPORTC = 0xFF;
	world.MaskPORTD = 0xFF;
	world.WORLD_TIMEZONE1_PORT &= ~(1 << WORLD_TIMEZONE1_PIN);
	world.WORLD_TIMEZONE2_PORT &= ~(1 << WORLD_TIMEZONE2_PIN);
	world.WORLD_TIMEZONE3_PORT &= ~(1 << WORLD_TIMEZONE3_PIN);
	world.WORLD_TIMEZONE4_PORT &= ~(1 << WORLD_TIMEZONE4_PIN);
	world.WORLD_TIMEZONE5_PORT &= ~(1 << WORLD_TIMEZONE5_PIN);
	world.WORLD_TIMEZONE6_PORT &= ~(1 << WORLD_TIMEZONE6_PIN);
	world.WORLD_TIMEZONE7_PORT &= ~(1 << WORLD_TIMEZONE7_PIN);
	world.WORLD_TIMEZONE8_PORT &= ~(1 << WORLD_TIMEZONE8_PIN);
	world.WORLD_TIMEZONE9_PORT &= ~(1 << WORLD_TIMEZONE9_PIN);
	world.OffPORTB = world.MaskPORTB;
	world.OffPORTC = world.MaskPORTC;
	world.OffPORTD = world.MaskPORTD;
	world.MaskPORTB = 0;
	world.MaskPORTC = 0;
	world.MaskPORTD = 0;

	world.brightness = 0;

	/* Prescaler = 64, results in 250Hz PWM frequency */
	TCCR2B |= (1 << CS22) | (1 << CS20);
	TIMSK2 |= (1 << TOIE2);
}

void world_EnableAll(void){
	world.WORLD_TIMEZONE1_PORT |= (1 << WORLD_TIMEZONE1_PIN);
	world.WORLD_TIMEZONE2_PORT |= (1 << WORLD_TIMEZONE2_PIN);
	world.WORLD_TIMEZONE3_PORT |= (1 << WORLD_TIMEZONE3_PIN);
	world.WORLD_TIMEZONE4_PORT |= (1 << WORLD_TIMEZONE4_PIN);
	world.WORLD_TIMEZONE5_PORT |= (1 << WORLD_TIMEZONE5_PIN);
	world.WORLD_TIMEZONE6_PORT |= (1 << WORLD_TIMEZONE6_PIN);
	world.WORLD_TIMEZONE7_PORT |= (1 << WORLD_TIMEZONE7_PIN);
	world.WORLD_TIMEZONE8_PORT |= (1 << WORLD_TIMEZONE8_PIN);
	world.WORLD_TIMEZONE9_PORT |= (1 << WORLD_TIMEZONE9_PIN);
}
void world_DisableAll(void){
	world.MaskPORTB = 0;
	world.MaskPORTC = 0;
	world.MaskPORTD = 0;
}

void world_Update(struct time time) {
	for(uint8_t i=0;i<WORLD_NUM_TIMEZONES;i++) {
		int8_t hour = time.hour;
		hour -= 12;
		hour += 3 * i;
		while(hour < 0) {
			hour += 24;
		}
		while(hour > 23) {
			hour -= 24;
		}
		/* hour now contains the timezone local time */
		if(hour>=WORLD_SUNRISE && hour < WORLD_SUNSET) {
			/* This element has to be illuminated */
			switch(i) {
			case 0: world.WORLD_TIMEZONE1_PORT |= (1 << WORLD_TIMEZONE1_PIN); break;
			case 1: world.WORLD_TIMEZONE2_PORT |= (1 << WORLD_TIMEZONE2_PIN); break;
			case 2: world.WORLD_TIMEZONE3_PORT |= (1 << WORLD_TIMEZONE3_PIN); break;
			case 3: world.WORLD_TIMEZONE4_PORT |= (1 << WORLD_TIMEZONE4_PIN); break;
			case 4: world.WORLD_TIMEZONE5_PORT |= (1 << WORLD_TIMEZONE5_PIN); break;
			case 5: world.WORLD_TIMEZONE6_PORT |= (1 << WORLD_TIMEZONE6_PIN); break;
			case 6: world.WORLD_TIMEZONE7_PORT |= (1 << WORLD_TIMEZONE7_PIN); break;
			case 7: world.WORLD_TIMEZONE8_PORT |= (1 << WORLD_TIMEZONE8_PIN); break;
			case 8: world.WORLD_TIMEZONE9_PORT |= (1 << WORLD_TIMEZONE9_PIN); break;
			}
		} else {
			/* This element has to be dark */
			switch(i) {
			case 0: world.WORLD_TIMEZONE1_PORT &= ~(1 << WORLD_TIMEZONE1_PIN); break;
			case 1: world.WORLD_TIMEZONE2_PORT &= ~(1 << WORLD_TIMEZONE2_PIN); break;
			case 2: world.WORLD_TIMEZONE3_PORT &= ~(1 << WORLD_TIMEZONE3_PIN); break;
			case 3: world.WORLD_TIMEZONE4_PORT &= ~(1 << WORLD_TIMEZONE4_PIN); break;
			case 4: world.WORLD_TIMEZONE5_PORT &= ~(1 << WORLD_TIMEZONE5_PIN); break;
			case 5: world.WORLD_TIMEZONE6_PORT &= ~(1 << WORLD_TIMEZONE6_PIN); break;
			case 6: world.WORLD_TIMEZONE7_PORT &= ~(1 << WORLD_TIMEZONE7_PIN); break;
			case 7: world.WORLD_TIMEZONE8_PORT &= ~(1 << WORLD_TIMEZONE8_PIN); break;
			case 8: world.WORLD_TIMEZONE9_PORT &= ~(1 << WORLD_TIMEZONE9_PIN); break;
			}
		}
	}
}

void world_SetPWM(uint8_t pwm) {
	world.brightness = pwm;
}

void world_Error(uint8_t blink) {
	if (blink > 0) {
		// illuminate the whole world
		world_EnableAll();
		// set blink code
		while (1) {
			uint8_t i;
			for (i = 0; i < blink; i++) {
				world_SetPWM(255);
				time_WaitMs(200);
				world_SetPWM(0);
				time_WaitMs(200);
			}
			uart_puts("Error: ");
			uart_putInteger(blink);
			uart_putc('\n');
			time_WaitMs(1000);
		}
	}
}

ISR(TIMER2_OVF_vect) {
	if (world.brightness > 0) {
		PORTB |= world.MaskPORTB;
		PORTC |= world.MaskPORTC;
		PORTD |= world.MaskPORTD;
		if (world.brightness < 20) {
			// wait for PWM cycle
			while (TCNT2 < world.brightness)
//				asm volatile("NOP");
				;
			// switch world off
			PORTB &= world.OffPORTB;
			PORTC &= world.OffPORTC;
			PORTD &= world.OffPORTD;
		} else {
			// PWM duty cycle is high, waiting in interrupt takes too much time
			// -> setup compare match interrupt
			OCR2A = world.brightness;
			// clear compare match flag
			TIFR2 = (1 << OCF2A);
			// enable interrupt
			TIMSK2 |= (1 << OCIE2A);
		}
	}
}
ISR(TIMER2_COMPA_vect) {
	// disable compare interrupt
	TIMSK2 &= ~(1 << OCIE2A);
	PORTB &= world.OffPORTB;
	PORTC &= world.OffPORTC;
	PORTD &= world.OffPORTD;
}
