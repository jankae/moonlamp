#include "moon.h"

uint8_t daysinmonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/* BEGIN OF AUTO-GENERATED CODE */
/*
 * Dates of a full moon {day, month, year-2000}
 * Auto-generated using python script and
 * http://home.hiwaay.net/~krcool/Astro/moon/fullmoon.htm
 */
struct date fullMoon[] = { { 24, 1, 16 }, { 22, 2, 16 }, { 23, 3, 16 }, { 22, 4,
		16 }, { 21, 5, 16 }, { 20, 6, 16 }, { 20, 7, 16 }, { 18, 8, 16 }, { 16,
		9, 16 }, { 16, 10, 16 }, { 14, 11, 16 }, { 14, 12, 16 }, { 12, 1, 17 },
		{ 11, 2, 17 }, { 12, 3, 17 }, { 11, 4, 17 }, { 10, 5, 17 },
		{ 9, 6, 17 }, { 9, 7, 17 }, { 7, 8, 17 }, { 6, 9, 17 }, { 5, 10, 17 }, {
				4, 11, 17 }, { 3, 12, 17 }, { 2, 1, 18 }, { 31, 1, 18 }, { 2, 3,
				18 }, { 31, 3, 18 }, { 30, 4, 18 }, { 29, 5, 18 },
		{ 28, 6, 18 }, { 27, 7, 18 }, { 26, 8, 18 }, { 25, 9, 18 },
		{ 24, 10, 18 }, { 23, 11, 18 }, { 22, 12, 18 }, { 21, 1, 19 }, { 19, 2,
				19 }, { 21, 3, 19 }, { 19, 4, 19 }, { 18, 5, 19 },
		{ 17, 6, 19 }, { 16, 7, 19 }, { 15, 8, 19 }, { 14, 9, 19 },
		{ 13, 10, 19 }, { 12, 11, 19 }, { 12, 12, 19 }, { 10, 1, 20 }, { 9, 2,
				20 }, { 9, 3, 20 }, { 8, 4, 20 }, { 7, 5, 20 }, { 5, 6, 20 }, {
				5, 7, 20 }, { 3, 8, 20 }, { 2, 9, 20 }, { 1, 10, 20 }, { 31, 10,
				20 }, { 30, 11, 20 }, { 30, 12, 20 }, { 28, 1, 21 },
		{ 27, 2, 21 }, { 28, 3, 21 }, { 27, 4, 21 }, { 26, 5, 21 },
		{ 24, 6, 21 }, { 24, 7, 21 }, { 22, 8, 21 }, { 20, 9, 21 },
		{ 20, 10, 21 }, { 19, 11, 21 }, { 19, 12, 21 }, { 17, 1, 22 }, { 16, 2,
				22 }, { 18, 3, 22 }, { 16, 4, 22 }, { 16, 5, 22 },
		{ 14, 6, 22 }, { 13, 7, 22 }, { 12, 8, 22 }, { 10, 9, 22 },
		{ 9, 10, 22 }, { 8, 11, 22 }, { 8, 12, 22 }, { 6, 1, 23 }, { 5, 2, 23 },
		{ 7, 3, 23 }, { 6, 4, 23 }, { 5, 5, 23 }, { 4, 6, 23 }, { 3, 7, 23 }, {
				1, 8, 23 }, { 31, 8, 23 }, { 29, 9, 23 }, { 28, 10, 23 }, { 27,
				11, 23 }, { 27, 12, 23 }, { 25, 1, 24 }, { 24, 2, 24 }, { 25, 3,
				24 }, { 23, 4, 24 }, { 23, 5, 24 }, { 22, 6, 24 },
		{ 21, 7, 24 }, { 19, 8, 24 }, { 18, 9, 24 }, { 17, 10, 24 }, { 15, 11,
				24 }, { 15, 12, 24 }, { 13, 1, 25 }, { 12, 2, 25 },
		{ 14, 3, 25 }, { 13, 4, 25 }, { 12, 5, 25 }, { 11, 6, 25 },
		{ 10, 7, 25 }, { 9, 8, 25 }, { 7, 9, 25 }, { 7, 10, 25 }, { 5, 11, 25 },
		{ 4, 12, 25 }, { 3, 1, 26 }, { 1, 2, 26 }, { 3, 3, 26 }, { 2, 4, 26 }, {
				1, 5, 26 }, { 31, 5, 26 }, { 29, 6, 26 }, { 29, 7, 26 }, { 28,
				8, 26 }, { 26, 9, 26 }, { 26, 10, 26 }, { 24, 11, 26 }, { 24,
				12, 26 }, { 22, 1, 27 }, { 20, 2, 27 }, { 22, 3, 27 }, { 20, 4,
				27 }, { 20, 5, 27 }, { 19, 6, 27 }, { 18, 7, 27 },
		{ 17, 8, 27 }, { 15, 9, 27 }, { 15, 10, 27 }, { 14, 11, 27 }, { 13, 12,
				27 }, { 12, 1, 28 }, { 10, 2, 28 }, { 11, 3, 28 }, { 9, 4, 28 },
		{ 8, 5, 28 }, { 7, 6, 28 }, { 6, 7, 28 }, { 5, 8, 28 }, { 3, 9, 28 }, {
				3, 10, 28 }, { 2, 11, 28 }, { 2, 12, 28 }, { 31, 12, 28 }, { 30,
				1, 29 }, { 28, 2, 29 }, { 30, 3, 29 }, { 28, 4, 29 }, { 27, 5,
				29 }, { 26, 6, 29 }, { 25, 7, 29 }, { 24, 8, 29 },
		{ 22, 9, 29 }, { 22, 10, 29 }, { 21, 11, 29 }, { 20, 12, 29 }, { 19, 1,
				30 }, { 18, 2, 30 }, { 19, 3, 30 }, { 18, 4, 30 },
		{ 17, 5, 30 }, { 15, 6, 30 }, { 15, 7, 30 }, { 13, 8, 30 },
		{ 11, 9, 30 }, { 11, 10, 30 }, { 10, 11, 30 }, { 9, 12, 30 },
		{ 8, 1, 31 }, { 7, 2, 31 }, { 9, 3, 31 }, { 7, 4, 31 }, { 7, 5, 31 }, {
				5, 6, 31 }, { 4, 7, 31 }, { 3, 8, 31 }, { 1, 9, 31 }, { 30, 9,
				31 }, { 30, 10, 31 }, { 28, 11, 31 }, { 28, 12, 31 }, { 27, 1,
				32 }, { 26, 2, 32 }, { 27, 3, 32 }, { 25, 4, 32 },
		{ 25, 5, 32 }, { 23, 6, 32 }, { 22, 7, 32 }, { 21, 8, 32 },
		{ 19, 9, 32 }, { 18, 10, 32 }, { 17, 11, 32 }, { 16, 12, 32 }, { 15, 1,
				33 }, { 14, 2, 33 }, { 16, 3, 33 }, { 14, 4, 33 },
		{ 14, 5, 33 }, { 12, 6, 33 }, { 12, 7, 33 }, { 10, 8, 33 },
		{ 9, 9, 33 }, { 8, 10, 33 }, { 6, 11, 33 }, { 6, 12, 33 }, { 4, 1, 34 },
		{ 3, 2, 34 }, { 5, 3, 34 }, { 3, 4, 34 }, { 3, 5, 34 }, { 2, 6, 34 }, {
				1, 7, 34 }, { 31, 7, 34 }, { 29, 8, 34 }, { 28, 9, 34 }, { 27,
				10, 34 }, { 25, 11, 34 }, { 25, 12, 34 }, { 23, 1, 35 }, { 22,
				2, 35 }, { 23, 3, 35 }, { 22, 4, 35 }, { 22, 5, 35 }, { 20, 6,
				35 }, { 20, 7, 35 }, { 19, 8, 35 }, { 17, 9, 35 },
		{ 17, 10, 35 }, { 15, 11, 35 }, { 15, 12, 35 }, { 13, 1, 36 }, { 11, 2,
				36 }, { 12, 3, 36 }, { 10, 4, 36 }, { 10, 5, 36 }, { 8, 6, 36 },
		{ 8, 7, 36 }, { 7, 8, 36 }, { 5, 9, 36 }, { 5, 10, 36 }, { 4, 11, 36 },
		{ 3, 12, 36 }, { 2, 1, 37 }, { 31, 1, 37 }, { 2, 3, 37 }, { 31, 3, 37 },
		{ 29, 4, 37 }, { 29, 5, 37 }, { 27, 6, 37 }, { 27, 7, 37 },
		{ 25, 8, 37 }, { 24, 9, 37 }, { 24, 10, 37 }, { 22, 11, 37 }, { 22, 12,
				37 }, { 21, 1, 38 }, { 19, 2, 38 }, { 21, 3, 38 },
		{ 19, 4, 38 }, { 18, 5, 38 }, { 17, 6, 38 }, { 16, 7, 38 },
		{ 14, 8, 38 }, { 13, 9, 38 }, { 13, 10, 38 }, { 11, 11, 38 }, { 11, 12,
				38 }, { 10, 1, 39 }, { 9, 2, 39 }, { 10, 3, 39 }, { 9, 4, 39 },
		{ 8, 5, 39 }, { 6, 6, 39 }, { 6, 7, 39 }, { 4, 8, 39 }, { 2, 9, 39 }, {
				2, 10, 39 }, { 31, 10, 39 }, { 30, 11, 39 }, { 30, 12, 39 }, };
/* END OF AUTO-GENERATED CODE */

void moon_init(void) {
	MOON_ELEMENT1_DDR |= (1 << MOON_ELEMENT1_PIN);
	MOON_ELEMENT2_DDR |= (1 << MOON_ELEMENT2_PIN);
	MOON_ELEMENT3_DDR |= (1 << MOON_ELEMENT3_PIN);
	MOON_ELEMENT4_DDR |= (1 << MOON_ELEMENT4_PIN);
	MOON_ELEMENT5_DDR |= (1 << MOON_ELEMENT5_PIN);
	MOON_ELEMENT6_DDR |= (1 << MOON_ELEMENT6_PIN);
	MOON_ELEMENT7_DDR |= (1 << MOON_ELEMENT7_PIN);
	MOON_ELEMENT8_DDR |= (1 << MOON_ELEMENT8_PIN);
	MOON_ELEMENT9_DDR |= (1 << MOON_ELEMENT9_PIN);
	MOON_ELEMENT10_DDR |= (1 << MOON_ELEMENT10_PIN);
	MOON_ELEMENT11_DDR |= (1 << MOON_ELEMENT11_PIN);
	MOON_ELEMENT12_DDR |= (1 << MOON_ELEMENT12_PIN);
	MOON_ELEMENT13_DDR |= (1 << MOON_ELEMENT13_PIN);

	// build 'switch-off'-masks
	moon.MaskPORTB = 0xFF;
	moon.MaskPORTC = 0xFF;
	moon.MaskPORTD = 0xFF;
	moon.MOON_ELEMENT1_PORT &= ~(1 << MOON_ELEMENT1_PIN);
	moon.MOON_ELEMENT2_PORT &= ~(1 << MOON_ELEMENT2_PIN);
	moon.MOON_ELEMENT3_PORT &= ~(1 << MOON_ELEMENT3_PIN);
	moon.MOON_ELEMENT4_PORT &= ~(1 << MOON_ELEMENT4_PIN);
	moon.MOON_ELEMENT5_PORT &= ~(1 << MOON_ELEMENT5_PIN);
	moon.MOON_ELEMENT6_PORT &= ~(1 << MOON_ELEMENT6_PIN);
	moon.MOON_ELEMENT7_PORT &= ~(1 << MOON_ELEMENT7_PIN);
	moon.MOON_ELEMENT8_PORT &= ~(1 << MOON_ELEMENT8_PIN);
	moon.MOON_ELEMENT9_PORT &= ~(1 << MOON_ELEMENT9_PIN);
	moon.MOON_ELEMENT10_PORT &= ~(1 << MOON_ELEMENT10_PIN);
	moon.MOON_ELEMENT11_PORT &= ~(1 << MOON_ELEMENT11_PIN);
	moon.MOON_ELEMENT12_PORT &= ~(1 << MOON_ELEMENT12_PIN);
	moon.MOON_ELEMENT13_PORT &= ~(1 << MOON_ELEMENT13_PIN);
	moon.OffPORTB = moon.MaskPORTB;
	moon.OffPORTC = moon.MaskPORTC;
	moon.OffPORTD = moon.MaskPORTD;
	moon.MaskPORTB = 0;
	moon.MaskPORTC = 0;
	moon.MaskPORTD = 0;

	moon.brightness = 0;

	TCCR2B |= (1 << CS21);
	TIMSK2 |= (1 << TOIE2) | (1 << OCIE2A);
}

uint8_t moon_DaysBetweenDates(struct date date1, struct date date2) {
	if (date1.year > date2.year
			|| (date1.year == date2.year && date1.month > date2.month)
			|| (date1.month == date2.month && date1.year == date2.year
					&& date1.day > date2.day)) {
		// date2 is before date1
		return moon_DaysBetweenDates(date2, date1);
	}
	uint8_t days = 0;
	if (date1.month == date2.month && date1.year == date2.year) {
		// same month and year -> simply take the difference in days
		days = date2.day - date1.day;
	} else {
		// not the same month (or even year)
		// 1. remaining days in month1
		days = daysinmonth[date1.month] - date1.day;
		uint8_t monthBuffer = date1.month + 1;
		uint8_t yearBuffer = date1.year;
		if (monthBuffer > 12) {
			monthBuffer -= 12;
			yearBuffer++;
		}
		// add all the days from the months lying completely between the two dates
		while (monthBuffer != date2.month || yearBuffer != date2.year) {
			days += daysinmonth[monthBuffer];
			monthBuffer++;
			if (monthBuffer > 12) {
				monthBuffer -= 12;
				yearBuffer++;
			}
		}
		// add days from month2
		days += date2.day;
	}
	return days;
}

int8_t moon_calculateState(struct date date) {
	struct date lastFullMoon;
	struct date nextFullMoon;
	int8_t daysSinceFull, daysUntilFull;
	uint8_t i = 0;
	int8_t moonstate = 0;
	uart_puts("Calculating moon state for ");
	uart_putDate(date);
	uart_putc('\n');
	// step through full moon dates until we pass the current date
	while (date.year > fullMoon[i].year
			|| (date.year == fullMoon[i].year && date.month > fullMoon[i].month)
			|| (date.year == fullMoon[i].year && date.month == fullMoon[i].month
					&& date.day > fullMoon[i].day)) {
		i++;
		if (i >= sizeof(fullMoon) / sizeof(struct date)) {
			// passed the last saved full moon
			uart_puts("ERROR: Last full moon date is too old\n");
			moon_Error(1);
		}
	}
	if (date.day == fullMoon[i].day && date.month == fullMoon[i].month
			&& date.year == fullMoon[i].year) {
		// today is a full moon day
		uart_puts("Today is a full moon\n");
		moonstate = -128;
	} else {
		// save last and next full moon
		lastFullMoon = fullMoon[i - 1];
		nextFullMoon = fullMoon[i];

		uart_puts("Last full moon on: ");
		uart_putDate(lastFullMoon);
		uart_puts("\nNext full moon on: ");
		uart_putDate(nextFullMoon);

		daysSinceFull = moon_DaysBetweenDates(lastFullMoon, date);
		daysUntilFull = moon_DaysBetweenDates(date, nextFullMoon);

		uart_puts("\nDays since full moon: ");
		uart_putInteger(daysSinceFull);
		uart_puts("\nDays until next full moon: ");
		uart_putInteger(daysUntilFull);
		uart_putc('\n');

		moonstate = ((daysSinceFull - daysUntilFull) * 128)
				/ (daysSinceFull + daysUntilFull);
	}
	uart_puts("Current moonstate: ");
	uart_putInteger(moonstate);
	uart_putc('\n');

	return moonstate;
}

void moon_SetElementsLeft(uint8_t elements) {
	moon.MaskPORTB = 0;
	moon.MaskPORTC = 0;
	moon.MaskPORTD = 0;
	if (elements >= 1)
		moon.MOON_ELEMENT1_PORT |= (1 << MOON_ELEMENT1_PIN);
	if (elements >= 2)
		moon.MOON_ELEMENT2_PORT |= (1 << MOON_ELEMENT2_PIN);
	if (elements >= 3)
		moon.MOON_ELEMENT3_PORT |= (1 << MOON_ELEMENT3_PIN);
	if (elements >= 4)
		moon.MOON_ELEMENT4_PORT |= (1 << MOON_ELEMENT4_PIN);
	if (elements >= 5)
		moon.MOON_ELEMENT5_PORT |= (1 << MOON_ELEMENT5_PIN);
	if (elements >= 6)
		moon.MOON_ELEMENT6_PORT |= (1 << MOON_ELEMENT6_PIN);
	if (elements >= 7)
		moon.MOON_ELEMENT7_PORT |= (1 << MOON_ELEMENT7_PIN);
	if (elements >= 8)
		moon.MOON_ELEMENT8_PORT |= (1 << MOON_ELEMENT8_PIN);
	if (elements >= 9)
		moon.MOON_ELEMENT9_PORT |= (1 << MOON_ELEMENT9_PIN);
	if (elements >= 10)
		moon.MOON_ELEMENT10_PORT |= (1 << MOON_ELEMENT10_PIN);
	if (elements >= 11)
		moon.MOON_ELEMENT11_PORT |= (1 << MOON_ELEMENT11_PIN);
	if (elements >= 12)
		moon.MOON_ELEMENT12_PORT |= (1 << MOON_ELEMENT12_PIN);
	if (elements >= 13)
		moon.MOON_ELEMENT13_PORT |= (1 << MOON_ELEMENT13_PIN);
	uart_puts("Illuminating ");
	uart_putInteger(elements);
	uart_puts(" elements from the left\n");
}
void moon_SetElementsRight(uint8_t elements) {
	moon.MaskPORTB = 0;
	moon.MaskPORTC = 0;
	moon.MaskPORTD = 0;
	if (elements >= 1)
		moon.MOON_ELEMENT13_PORT |= (1 << MOON_ELEMENT13_PIN);
	if (elements >= 2)
		moon.MOON_ELEMENT12_PORT |= (1 << MOON_ELEMENT12_PIN);
	if (elements >= 3)
		moon.MOON_ELEMENT11_PORT |= (1 << MOON_ELEMENT11_PIN);
	if (elements >= 4)
		moon.MOON_ELEMENT10_PORT |= (1 << MOON_ELEMENT10_PIN);
	if (elements >= 5)
		moon.MOON_ELEMENT9_PORT |= (1 << MOON_ELEMENT9_PIN);
	if (elements >= 6)
		moon.MOON_ELEMENT8_PORT |= (1 << MOON_ELEMENT8_PIN);
	if (elements >= 7)
		moon.MOON_ELEMENT7_PORT |= (1 << MOON_ELEMENT7_PIN);
	if (elements >= 8)
		moon.MOON_ELEMENT6_PORT |= (1 << MOON_ELEMENT6_PIN);
	if (elements >= 9)
		moon.MOON_ELEMENT5_PORT |= (1 << MOON_ELEMENT5_PIN);
	if (elements >= 10)
		moon.MOON_ELEMENT4_PORT |= (1 << MOON_ELEMENT4_PIN);
	if (elements >= 11)
		moon.MOON_ELEMENT3_PORT |= (1 << MOON_ELEMENT3_PIN);
	if (elements >= 12)
		moon.MOON_ELEMENT2_PORT |= (1 << MOON_ELEMENT2_PIN);
	if (elements >= 13)
		moon.MOON_ELEMENT1_PORT |= (1 << MOON_ELEMENT1_PIN);
	uart_puts("Illuminating ");
	uart_putInteger(elements);
	uart_puts(" elements from the right\n");
}
void moon_Update(struct date date) {
	int8_t moonstate = moon_calculateState(date);
	uint8_t elements;
	if (moonstate < 0) {
		elements = -(int16_t) moonstate * MOON_NUM_ELEMENTS / 128;
		moon_SetElementsLeft(elements);
	} else {
		elements = (int16_t) moonstate * MOON_NUM_ELEMENTS / 128;
		moon_SetElementsRight(elements);
	}
}

void moon_SetPWM(uint8_t pwm) {
	moon.brightness = pwm;
	if (moon.brightness < 128) {
		OCR2A = 255 - moon.brightness;
	} else {
		OCR2A = moon.brightness;
	}
}

void moon_Error(uint8_t blink) {
	if (blink > 0) {
		// illuminate the whole moon
		moon_SetElementsLeft(MOON_NUM_ELEMENTS);
		// set blink code
		while (1) {
			uint8_t i;
			for (i = 0; i < blink; i++) {
				moon_SetPWM(255);
				time_WaitMs(200);
				moon_SetPWM(0);
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
	if (moon.brightness > 0 && moon.brightness >= 128) {
		PORTB |= moon.MaskPORTB;
		PORTC |= moon.MaskPORTC;
		PORTD |= moon.MaskPORTD;
	} else {
		PORTB &= moon.OffPORTB;
		PORTC &= moon.OffPORTC;
		PORTD &= moon.OffPORTD;
	}
}
ISR(TIMER2_COMPA_vect) {
	if (moon.brightness > 0 && moon.brightness < 128) {
		PORTB |= moon.MaskPORTB;
		PORTC |= moon.MaskPORTC;
		PORTD |= moon.MaskPORTD;
	} else {
		PORTB &= moon.OffPORTB;
		PORTC &= moon.OffPORTC;
		PORTD &= moon.OffPORTD;
	}
}
