#ifndef DS1307_H_
#define DS1307_H_

#include <avr/io.h>
#include "i2c_master.h"
#include "dates.h"

#define DS1307_SLAVE 0x68

void set_time(struct time time);
void set_date(struct date date);
void get_time(struct time *time);
void get_date(struct date *date);

#endif
