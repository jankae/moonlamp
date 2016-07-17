#include <avr/io.h>

#include "moon.h"
#include "eeprom.h"
#include "ds1307.h"

int main(void) {
	struct date date;
	struct time time;
	eeprom_Read(&date, &time);

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
		// set RTC
		DS1307_setTime(time);
		DS1307_setDate(date);
		// save in EEPROM
		eeprom_Write(date, time);
	}
	// at this point the RTC has either just been set or still contains a valid
	// time and date (device hasn't been flashed before current start-up)

	moon_init();
	while (1)
		;
}
