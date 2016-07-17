#include "moon.h"

uint8_t daysinmonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
struct date fullMoon[] = { { 21, 5, 16 }, { 20, 6, 16 }, { 19, 7, 16 }, { 18, 8,
		16 }, { 16, 9, 16 }, { 16, 10, 16 }, { 14, 11, 16 }, { 14, 12, 16 } };

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
	moon.error = 0;

	TCCR2A |= (1 << CS21);
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
	// step through full moon dates until we pass the current date
	while (date.year > fullMoon[i].year
			|| (date.year == fullMoon[i].year && date.month > fullMoon[i].month)
			|| (date.year == fullMoon[i].year && date.month == fullMoon[i].month
					&& date.day > fullMoon[i].day)) {
		i++;
		if (i >= sizeof(fullMoon) / sizeof(struct date)) {
			// passed the last saved full moon
			moon.error = 1;
			return 128;
		}
	}
	if (date.day == fullMoon[i].day && date.month == fullMoon[i].month
			&& date.year == fullMoon[i].year) {
		// today is a full moon day
		return 128;
	}
	// save last and next full moon
	lastFullMoon = fullMoon[i - 1];
	nextFullMoon = fullMoon[i];

	daysSinceFull = moon_DaysBetweenDates(lastFullMoon, date);
	daysUntilFull = moon_DaysBetweenDates(date, nextFullMoon);

	return ((daysSinceFull - daysUntilFull) * 128)
			/ (daysSinceFull + daysUntilFull);
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
}
void moon_Update(struct date date) {
	int8_t moonstate = moon_calculateState(date);
	uint8_t elements;
	if (moonstate < 0) {
		elements = -moonstate / 9;
		moon_SetElementsLeft(elements);
	} else {
		elements = moonstate / 9;
		moon_SetElementsRight(elements);
	}
}

void moon_SetPWM(uint8_t pwm) {
	moon.brightness = pwm;
}

ISR(TIMER2_OVF_vect) {
	if (moon.brightness > 0) {
		PORTB |= moon.MaskPORTB;
		PORTC |= moon.MaskPORTC;
		PORTD |= moon.MaskPORTD;
	}
	OCR2A = moon.brightness;
}
ISR(TIMER2_COMPA_vect) {
	PORTB &= moon.OffPORTB;
	PORTC &= moon.OffPORTB;
	PORTD &= moon.OffPORTB;
}
