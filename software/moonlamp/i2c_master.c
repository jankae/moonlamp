#include "i2c_master.h"

void i2c_init(void) {
	TWCR |= (1 << TWEN) | (1 << TWEA);
	//Bitrate = 50000
	//Bitrate = F_CPU(1000000)/(16+2(TWBR))
	TWBR = 2;
}

uint8_t i2c_get_byte(uint8_t ack) {
	uint16_t timeout = time_SetTimeout(10);
	TWCR |= (1 << TWINT) | (1 << TWEA);
	if (ack != 1)
		TWCR &= ~(1 << TWEA);
	while (!(TWCR & (1 << TWINT)) && !time_TimeoutElapsed(timeout))
		;
	return TWDR ;
}
uint8_t i2c_write_byte(uint8_t data) {
	uint16_t timeout = time_SetTimeout(10);
	TWDR = data;
	TWCR |= (1 << TWINT);
	while (!(TWCR & (1 << TWINT)) && !time_TimeoutElapsed(timeout))
		;
	if ((TWSR & 0xF8) != 0x28) {
		TWCR |= (1 << TWINT) | (1 << TWSTO);
		return 1;
	}
	return 0;
}
uint8_t i2c_start(void) {
	uint16_t timeout = time_SetTimeout(10);
	//Start senden
	TWCR |= (1 << TWINT) | (1 << TWSTA);
	while (!(TWCR & (1 << TWINT)) && !time_TimeoutElapsed(timeout))
		;
	if ((TWSR & 0xF8) != 0x08)
		return 1;
	else
		return 0;
}
uint8_t i2c_address(uint8_t adr, uint8_t mode) {
	uint16_t timeout = time_SetTimeout(10);
	//Slave-Adresse + Write senden
	TWDR = (adr << 1) | mode;
	TWCR &= ~(1 << TWSTA);
	TWCR |= (1 << TWINT);
	while (!(TWCR & (1 << TWINT)) && !time_TimeoutElapsed(timeout))
		;
	uint8_t status = TWSR & 0xF8;
	if (status != 0x18 && status != 0x40) {
		TWCR |= (1 << TWINT) | (1 << TWSTO);
		return 1;
	} else
		return 0;
}
void i2c_stop(void) {
	TWCR |= (1 << TWINT) | (1 << TWSTO);
}
