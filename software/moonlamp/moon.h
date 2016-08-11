#ifndef MOON_H_
#define MOON_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "dates.h"
#include "systime.h"

/*
 * Bits  7   6   5   4   3   2   1   0
 * PB    6   7   -   -   -   1   2   -
 * PC    -   -   -   -  11  12  13   -
 * PD    3   4   5   8   9  10   -   -
 */
#define MOON_NUM_ELEMENTS		13

#define MOON_ELEMENT1_DDR		DDRB
#define MOON_ELEMENT1_PORT		MaskPORTB
#define MOON_ELEMENT1_PIN		(2)

#define MOON_ELEMENT2_DDR		DDRB
#define MOON_ELEMENT2_PORT		MaskPORTB
#define MOON_ELEMENT2_PIN		(1)

#define MOON_ELEMENT3_DDR		DDRD
#define MOON_ELEMENT3_PORT		MaskPORTD
#define MOON_ELEMENT3_PIN		(7)

#define MOON_ELEMENT4_DDR		DDRD
#define MOON_ELEMENT4_PORT		MaskPORTD
#define MOON_ELEMENT4_PIN		(6)

#define MOON_ELEMENT5_DDR		DDRD
#define MOON_ELEMENT5_PORT		MaskPORTD
#define MOON_ELEMENT5_PIN		(5)

#define MOON_ELEMENT6_DDR		DDRB
#define MOON_ELEMENT6_PORT		MaskPORTB
#define MOON_ELEMENT6_PIN		(7)

#define MOON_ELEMENT7_DDR		DDRB
#define MOON_ELEMENT7_PORT		MaskPORTB
#define MOON_ELEMENT7_PIN		(6)

#define MOON_ELEMENT8_DDR		DDRD
#define MOON_ELEMENT8_PORT		MaskPORTD
#define MOON_ELEMENT8_PIN		(4)

#define MOON_ELEMENT9_DDR		DDRD
#define MOON_ELEMENT9_PORT		MaskPORTD
#define MOON_ELEMENT9_PIN		(3)

#define MOON_ELEMENT10_DDR		DDRD
#define MOON_ELEMENT10_PORT		MaskPORTD
#define MOON_ELEMENT10_PIN		(2)

#define MOON_ELEMENT11_DDR		DDRC
#define MOON_ELEMENT11_PORT		MaskPORTC
#define MOON_ELEMENT11_PIN		(3)

#define MOON_ELEMENT12_DDR		DDRC
#define MOON_ELEMENT12_PORT		MaskPORTC
#define MOON_ELEMENT12_PIN		(2)

#define MOON_ELEMENT13_DDR		DDRC
#define MOON_ELEMENT13_PORT		MaskPORTC
#define MOON_ELEMENT13_PIN		(1)

struct {
	uint8_t MaskPORTB;
	uint8_t MaskPORTC;
	uint8_t MaskPORTD;
	uint8_t OffPORTB;
	uint8_t OffPORTC;
	uint8_t OffPORTD;
	uint8_t brightness;
	uint8_t pwmCycle;
} moon;

/**
 * \brief Initializes ports and variables, sets brightness to zero
 */
void moon_init(void);

/**
 * \brief Calculates the number of days between two given dates
 *
 * \param date1 First date
 * \param date2 Second date
 * \return Number of days between date1 and date2
 */
uint8_t moon_DaysBetweenDates(struct date date1, struct date date2);

/**
 * \brief Calculates the moon state to a given date
 *
 * \param date The date at which the moon state should be calculated
 * \return Moonstate:
 * 			128: full moon
 * 			1 to 127: waxing moon
 * 			0: new moon
 * 			-1 to -128: waning moon
 */
int8_t moon_calculateState(struct date date);

/**
 * \brief Lights up a number of elements, starting from the left side (waning moon)
 *
 * \param elements Number of elements to light up (0-13)
 */
void moon_SetElementsLeft(uint8_t elements);

/**
 * \brief Lights up a number of elements, starting from the right side (waxing moon)
 *
 * \param elements Number of elements to light up (0-13)
 */
void moon_SetElementsRight(uint8_t elements);

/**
 * \brief Updates the moon state with a given date
 *
 * \param date The current date
 */
void moon_Update(struct date date);

/**
 * \brief Sets the intensity of the moon LEDs
 *
 * \param pwm 8-bit PWM (0-255)
 */
void moon_SetPWM(uint8_t pwm);

void moon_Error(uint8_t blink);

#endif
