#include "ds1307.h"

void set_time(uint8_t hour, uint8_t minute, uint8_t second) {
	uint8_t bcdhour = ((hour / 10) << 4) + (hour % 10);
	uint8_t bcdminute = ((minute / 10) << 4) + (minute % 10);
	uint8_t bcdsecond = ((second / 10) << 4) + (second % 10);

	i2c_start();
	i2c_address(DS1307_SLAVE, I2C_WRITE);
	i2c_write_byte(0x00);					//set register pointer to seconds
	i2c_write_byte(bcdsecond);
	i2c_write_byte(bcdminute);
	i2c_write_byte(bcdhour);
	i2c_stop();
}

void set_date(uint8_t date, uint8_t month, uint8_t year) {
	uint8_t bcddate = ((date / 10) << 4) + (date % 10);
	uint8_t bcdmonth = ((month / 10) << 4) + (month % 10);
	uint8_t bcdyear = ((year / 10) << 4) + (year % 10);

	i2c_start();
	i2c_address(DS1307_SLAVE, I2C_WRITE);
	i2c_write_byte(0x04);						//set register pointer to date
	i2c_write_byte(bcddate);
	i2c_write_byte(bcdmonth);
	i2c_write_byte(bcdyear);
	i2c_stop();
}

void get_time(uint8_t *hour, uint8_t *minute, uint8_t *second) {
	//set register pointer
	i2c_start();
	i2c_address(DS1307_SLAVE, I2C_WRITE);
	i2c_write_byte(0x00);
	i2c_stop();

	//receive data
	i2c_start();
	i2c_address(DS1307_SLAVE, I2C_READ);
	*second = i2c_get_byte(1);
	*minute = i2c_get_byte(1);
	*hour = i2c_get_byte(0);

	//convertion from BCD
	*second = (*second & 0x0F) + 10 * (*second >> 4);
	*minute = (*minute & 0x0F) + 10 * (*minute >> 4);
	*hour = (*hour & 0x0F) + 10 * (*hour >> 4);
}

void get_date(uint8_t *date, uint8_t *month, uint8_t *year) {
	//set register pointer
	i2c_start();
	i2c_address(DS1307_SLAVE, I2C_WRITE);
	i2c_write_byte(0x04);
	i2c_stop();

	//receive data
	i2c_start();
	i2c_address(DS1307_SLAVE, I2C_READ);
	*date = i2c_get_byte(1);
	*month = i2c_get_byte(1);
	*year = i2c_get_byte(0);

	//convertion from BCD
	*date = (*date & 0x0F) + 10 * (*date >> 4);
	*month = (*month & 0x0F) + 10 * (*month >> 4);
	*year = (*year & 0x0F) + 10 * (*year >> 4);
}

