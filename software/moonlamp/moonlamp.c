#include <avr/io.h>

#include "moon.h"
#include "eeprom.h"
#include "ds1307.h"
#include "systime.h"
#include "encoder.h"

int main(void) {
	time_Init();
	uart_init();
	encoder_Init();
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

	moon_init();

	// light up moon once to show device is working (it might be new moon)
	// activate all elements
	moon_SetElementsLeft(13);
	uint8_t i;
	for (i = 0; i < 10; i++) {
		moon_SetPWM(i * i);
		time_WaitMs(50);
	}
	moon_SetPWM(255);
	time_WaitMs(50);
	for (i = 9; i > 0; i--) {
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

	uint8_t brightness = 5;
	uint8_t oldDay;
	uint8_t on = 1;
	uint16_t timeUpdateTimeout = time_SetTimeout(10000);
	while (1) {
		time_WaitMs(5);
		/*********************************
		 * Step 1: Evaluate encoder control
		 ********************************/
		int8_t enc = encoder_Update();
		if (enc == 1 && brightness < 15) {
			brightness++;
			uart_puts("New brightness: ");
			uart_putInteger(brightness);
			uart_putc('\n');
		} else if (enc == -1 && brightness > 0) {
			brightness--;
			uart_puts("New brightness: ");
			uart_putInteger(brightness);
			uart_putc('\n');
		}
		/*********************************
		 * Step 2: get current date
		 ********************************/
		if (time_TimeoutElapsed(timeUpdateTimeout)) {
			oldDay = date.day;
			DS1307_getDate(&date);
			struct date date2;
			DS1307_getDate(&date2);
			if (date.day == date2.day && date.month == date2.month
					&& date.year == date2.year) {
				// both dates are the same
				// -> probably no I2C transmission error
				if (date.day >= 1 && date.day <= 31 && date.month >= 1
						&& date.month <= 12 && date.year >= 16
						&& date.year <= 99) {
					// date seems to be valid
					/*********************************
					 * Step 3: Update moon state
					 ********************************/
					if (oldDay != date.day) {
						moon_Update(date);
					}
					timeUpdateTimeout = time_SetTimeout(10000);
				}
			}
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
