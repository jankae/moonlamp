#include "ds1307.h"

void set_time(struct time time) {
	uint8_t bcdhour = ((time.hour / 10) << 4) + (time.hour % 10);
	uint8_t bcdminute = ((time.minute / 10) << 4) + (time.minute % 10);
	uint8_t bcdsecond = ((time.second / 10) << 4) + (time.second % 10);

	i2c_start();
	i2c_address(DS1307_SLAVE, I2C_WRITE);
	i2c_write_byte(0x00);					//set register pointer to seconds
	i2c_write_byte(bcdsecond);
	i2c_write_byte(bcdminute);
	i2c_write_byte(bcdhour);
	i2c_stop();
}

void set_date(struct date date) {
	uint8_t bcddate = ((date.day / 10) << 4) + (date.day % 10);
	uint8_t bcdmonth = ((date.month / 10) << 4) + (date.month % 10);
	uint8_t bcdyear = ((date.year / 10) << 4) + (date.year % 10);

	i2c_start();
	i2c_address(DS1307_SLAVE, I2C_WRITE);
	i2c_write_byte(0x04);						//set register pointer to date
	i2c_write_byte(bcddate);
	i2c_write_byte(bcdmonth);
	i2c_write_byte(bcdyear);
	i2c_stop();
}

void get_time(struct time *time) {
	//set register pointer
	i2c_start();
	i2c_address(DS1307_SLAVE, I2C_WRITE);
	i2c_write_byte(0x00);
	i2c_stop();

	//receive data
	i2c_start();
	i2c_address(DS1307_SLAVE, I2C_READ);
	uint8_t second = i2c_get_byte(1);
	uint8_t minute = i2c_get_byte(1);
	uint8_t hour = i2c_get_byte(0);

	//conversion from BCD
	time->second = (second & 0x0F) + 10 * (second >> 4);
	time->minute = (minute & 0x0F) + 10 * (minute >> 4);
	time->hour = (hour & 0x0F) + 10 * (hour >> 4);
}

void get_date(struct date *date) {
	//set register pointer
	i2c_start();
	i2c_address(DS1307_SLAVE, I2C_WRITE);
	i2c_write_byte(0x04);
	i2c_stop();

	//receive data
	i2c_start();
	i2c_address(DS1307_SLAVE, I2C_READ);
	uint8_t day = i2c_get_byte(1);
	uint8_t month = i2c_get_byte(1);
	uint8_t year = i2c_get_byte(0);

	//conversion from BCD
	date->day = (day & 0x0F) + 10 * (day >> 4);
	date->month = (month & 0x0F) + 10 * (month >> 4);
	date->year = (year & 0x0F) + 10 * (year >> 4);
}

