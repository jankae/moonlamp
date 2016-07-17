#ifndef DS1307_H_
#define DS1307_H_

#include <avr/io.h>
#include "i2c_master.h"
#include "dates.h"

#define DS1307_SLAVE 0x68

void DS1307_setTime(struct time time);
void DS1307_setDate(struct date date);
void DS1307_getTime(struct time *time);
void DS1307_getDate(struct date *date);

#endif
