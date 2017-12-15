#include <avr/io.h>

#include "eeprom.h"
#include "ds1307.h"
#include "systime.h"
#include "world.h"
#include "encoder.h"

int main(void) {
	Encoder_Init();
	time_Init();
	uart_init();
	i2c_init();
	sei();

	DS1307_Init();

	uart_puts("moonlamp V0.9 start\n");
	struct date date;
	struct time time;
	eeprom_Read(&date, &time);

	uart_puts("EEPROM date/time: ");
	uart_putDate(date);
	uart_putc('/');
	uart_putTime(time);
	// compare EEPROM time with compile time
	if ((date.day != COMPILE_DAY) || (date.month != COMPILE_MONTH)
			|| (date.year != (COMPILE_YEAR - 2000))
			|| (time.second != COMPILE_SECOND)
			|| (time.minute != COMPILE_MINUTE) || (time.hour != COMPILE_HOUR)) {
		// EEPROM date/time doesn't match compile date/time
		// -> device has just been flashed, write compile date/time to RTC
		date.day = COMPILE_DAY;
		date.month = COMPILE_MONTH;
		date.year = (COMPILE_YEAR - 2000);
		time.second = COMPILE_SECOND;
		time.minute = COMPILE_MINUTE;
		time.hour = COMPILE_HOUR;
		uart_puts("\nEEPROM doesn't match compile time:\n");
		uart_puts("Compile date/time: ");
		uart_putDate(date);
		uart_putc('/');
		uart_putTime(time);
		// set RTC
		uart_puts("\nSetting RTC...\n");
		DS1307_setTime(time);
		DS1307_setDate(date);
		// save in EEPROM
		uart_puts("Updating EEPROM...\n");
		eeprom_Write(date, time);
	} else {
		uart_puts("\nEEPROM matches compile time\n");
	}
	// at this point the RTC has either just been set or still contains a valid
	// time and date (device hasn't been flashed before current start-up)
	DS1307_getDate(&date);
	DS1307_getTime(&time);
	uart_puts("RTC date/time: ");
	uart_putDate(date);
	uart_putc('/');
	uart_putTime(time);
	uart_putc('\n');

	world_init();

	// light up moon once to show device is working (it might be new moon)
	// activate all elements
	world_EnableAll();
	uint8_t i;
	for (i = 0; i < 10; i++) {
		world_SetPWM(i * i);
		time_WaitMs(50);
	}
	world_SetPWM(255);
	time_WaitMs(50);
	for (i = 9; i > 0; i--) {
		world_SetPWM(i * i);
		time_WaitMs(50);
	}
	world_SetPWM(0);

	// sanity check for RTC
	if (date.year < 16) {
		// can't be right, year must be at least 2016
		uart_puts("ERROR: RTC invalid\n");
		world_Error(2);
	}

	world_Update(time);

	int8_t brightness = 5;
	uint8_t oldTime;
	uint8_t timeTrackingMode = 0;
	uint16_t timeUpdateTimeout = time_SetTimeout(10000);
	while (1) {
		time_WaitMs(50);
		/*********************************
		 * Step 1: Evaluate encoder control
		 ********************************/
		brightness += Encoder_GetMovement();
		if (brightness < 0) {
			brightness = 0;
		} else if (brightness > 16) {
			brightness = 16;
		}
		if (Encoder_GetPress()) {
			/* Switch mode, wait for encoder to be released */
			timeTrackingMode = !timeTrackingMode;
			while (Encoder_GetPress())
				;
		}
		/*********************************
		 * Step 2: get current time
		 ********************************/
		if (timeTrackingMode) {
			if (time_TimeoutElapsed(timeUpdateTimeout)) {
				oldTime = time.hour;
				DS1307_getTime(&time);
				struct time time2;
				DS1307_getTime(&time2);
				if (time.hour == time2.hour && time.minute == time2.minute
						&& time.second == time2.second) {
					// both dates are the same
					// -> probably no I2C transmission error
					if (time.hour <= 23 && time.minute < 60
							&& time.second < 60) {
						// date seems to be valid
						/*********************************
						 * Step 3: Update world state
						 ********************************/
						if (oldTime != time.hour) {
							world_Update(time);
						}
						timeUpdateTimeout = time_SetTimeout(10000);
					}
				}
			}
		} else {
			/* World is always completely on */
			world_EnableAll();
		}
		/*********************************
		 * Step 4: Set moon PWM
		 ********************************/
		uint16_t pwm = (uint8_t) brightness * (uint8_t) brightness;
		if (pwm > 255)
			pwm = 255;
		world_SetPWM(pwm);
	}
}
