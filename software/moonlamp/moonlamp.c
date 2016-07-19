#include <avr/io.h>

#include "moon.h"
#include "eeprom.h"
#include "ds1307.h"
#include "systime.h"
#include "touch.h"

int main(void) {
	time_Init();
	uart_init();
	i2c_init();
	touch_Init();
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

	moon_init();

	// light up moon once to show device is working (it might be new moon)
	// activate all elements
	moon_SetElementsLeft(13);
	uint8_t i;
	for (i = 0; i < 16; i++) {
		moon_SetPWM(i * i);
		time_WaitMs(50);
	}
	moon_SetPWM(255);
	time_WaitMs(50);
	for (i = 15; i > 0; i--) {
		moon_SetPWM(i * i);
		time_WaitMs(50);
	}
	moon_SetPWM(0);

	// sanity check for RTC
	if (date.year < 16) {
		// can't be right, year must be at least 2016
		uart_puts("ERROR: RTC invalid\n");
		moon_Error(2);
	}

	moon_Update(date);

	uint8_t brightness = 1;
	uint8_t oldDay;
	uint8_t on = 1;
	uint8_t increasingBrightness = 1;
	uint8_t holding = 0;
	uint16_t changeTimeout;
	while (1) {
		time_WaitMs(50);
		/*********************************
		 * Step 1: Evaluate touch control
		 ********************************/
		if (touch_Tapped()) {
			on = !on;
			if (on) {
				uart_puts("Moonlamp on\n");
			} else {
				uart_puts("Moonlamp off\n");
			}
		} else if (touch_Holding()) {
			if (!on) {
				uart_puts("Moonlamp on\n");
				on = 1;
			}
			if (!holding || time_TimeoutElapsed(changeTimeout)) {
				// only change brightness every 200ms
				changeTimeout = time_SetTimeout(200);
				// sweep brightness
				if (increasingBrightness) {
					if (brightness < 16) {
						brightness++;
					} else {
						increasingBrightness = 0;
					}
				} else {
					if (brightness > 1) {
						brightness--;
					} else {
						increasingBrightness = 1;
					}
				}
				holding = 1;
				uart_puts("New brightness: ");
				uart_putInteger(brightness);
				uart_putc('\n');
			}
		} else {
			holding = 0;
		}
		/*********************************
		 * Step 2: get current date
		 ********************************/
		oldDay = date.day;
		DS1307_getDate(&date);
		/*********************************
		 * Step 3: Update moon state
		 ********************************/
		if (oldDay != date.day) {
			moon_Update(date);
		}
		/*********************************
		 * Step 4: Set moon PWM
		 ********************************/
		if (on) {
			uint16_t pwm = brightness * brightness;
			if (pwm > 255)
				pwm = 255;
			moon_SetPWM(pwm);
		} else {
			moon_SetPWM(0);
		}
	}
}
