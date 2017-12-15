#ifndef WORLD_H_
#define WORLD_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "dates.h"
#include "systime.h"

#define WORLD_SUNRISE			7
#define WORLD_SUNSET			19

/*
 * Bits  7   6   5   4   3   2   1   0
 * PB    6   7   -   -   -   1   2   -
 * PC    -   -   -   -  11  12  13   -
 * PD    3   4   5   8   9  10   -   -
 */
#define WORLD_NUM_TIMEZONES		13

#define WORLD_TIMEZONE1_DDR		DDRB
#define WORLD_TIMEZONE1_PORT	MaskPORTB
#define WORLD_TIMEZONE1_PIN		(2)

#define WORLD_TIMEZONE2_DDR		DDRB
#define WORLD_TIMEZONE2_PORT	MaskPORTB
#define WORLD_TIMEZONE2_PIN		(1)

#define WORLD_TIMEZONE3_DDR		DDRD
#define WORLD_TIMEZONE3_PORT	MaskPORTD
#define WORLD_TIMEZONE3_PIN		(7)

#define WORLD_TIMEZONE4_DDR		DDRD
#define WORLD_TIMEZONE4_PORT	MaskPORTD
#define WORLD_TIMEZONE4_PIN		(6)

#define WORLD_TIMEZONE5_DDR		DDRD
#define WORLD_TIMEZONE5_PORT	MaskPORTD
#define WORLD_TIMEZONE5_PIN		(5)

#define WORLD_TIMEZONE6_DDR		DDRB
#define WORLD_TIMEZONE6_PORT	MaskPORTB
#define WORLD_TIMEZONE6_PIN		(7)

#define WORLD_TIMEZONE7_DDR		DDRB
#define WORLD_TIMEZONE7_PORT	MaskPORTB
#define WORLD_TIMEZONE7_PIN		(6)

#define WORLD_TIMEZONE8_DDR		DDRD
#define WORLD_TIMEZONE8_PORT	MaskPORTD
#define WORLD_TIMEZONE8_PIN		(4)

#define WORLD_TIMEZONE9_DDR		DDRD
#define WORLD_TIMEZONE9_PORT	MaskPORTD
#define WORLD_TIMEZONE9_PIN		(3)
//
//#define MOON_ELEMENT10_DDR		DDRD
//#define MOON_ELEMENT10_PORT		MaskPORTD
//#define MOON_ELEMENT10_PIN		(2)
//
//#define MOON_ELEMENT11_DDR		DDRC
//#define MOON_ELEMENT11_PORT		MaskPORTC
//#define MOON_ELEMENT11_PIN		(3)
//
//#define MOON_ELEMENT12_DDR		DDRC
//#define MOON_ELEMENT12_PORT		MaskPORTC
//#define MOON_ELEMENT12_PIN		(2)
//
//#define MOON_ELEMENT13_DDR		DDRC
//#define MOON_ELEMENT13_PORT		MaskPORTC
//#define MOON_ELEMENT13_PIN		(1)

struct {
	uint8_t MaskPORTB;
	uint8_t MaskPORTC;
	uint8_t MaskPORTD;
	uint8_t OffPORTB;
	uint8_t OffPORTC;
	uint8_t OffPORTD;
	uint8_t brightness;
	uint8_t pwmCycle;
} world;

/**
 * \brief Initializes ports and variables, sets brightness to zero
 */
void world_init(void);

void world_EnableAll(void);
void world_DisableAll(void);

/**
 * \brief Updates the moon state with a given date
 *
 * \param date The current date
 */
void world_Update(struct time time);

/**
 * \brief Sets the intensity of the moon LEDs
 *
 * \param pwm 8-bit PWM (0-255)
 */
void world_SetPWM(uint8_t pwm);

void world_Error(uint8_t blink);

#endif
