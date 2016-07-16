#ifndef DS1307_H_
#define DS1307_H_

#include <avr/io.h>
#include "i2c_master.h"

#define DS1307_SLAVE 0x68

void set_time(uint8_t hour, uint8_t minute, uint8_t second);
void set_date(uint8_t date, uint8_t month, uint8_t year);
void get_time(uint8_t *hour, uint8_t *minute, uint8_t *second);
void get_date(uint8_t *date, uint8_t *month, uint8_t *year);

#endif
