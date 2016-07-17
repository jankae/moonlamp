#include "eeprom.h"

struct date edate EEMEM;
struct time etime EEMEM;

void eeprom_Write(struct date date, struct time time){
	eeprom_write_block(&date, &edate, sizeof(struct date));
	eeprom_write_block(&time, &etime, sizeof(struct time));
}
void eeprom_Read(struct date *date, struct time *time){
	eeprom_read_block(date, &edate, sizeof(struct date));
	eeprom_read_block(time, &etime, sizeof(struct time));
}
