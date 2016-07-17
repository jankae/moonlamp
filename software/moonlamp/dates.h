#ifndef DATES_H_
#define DATES_H_

#include <stdint.h>

struct time {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
};

struct date {
	uint8_t day;
	uint8_t month;
	uint8_t year;
};

#endif
