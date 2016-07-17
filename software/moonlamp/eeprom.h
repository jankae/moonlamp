#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/eeprom.h>
#include "dates.h"

/**
 * \brief Writes the date and time into EEPROM
 */
void eeprom_Write(struct date date, struct time time);

/**
 * \brief Reads the date and time from EEPROM
 */
void eeprom_Read(struct date *date, struct time *time);

#endif
