#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_

#include <avr/io.h>

#define I2C_READ 1
#define I2C_WRITE 0

void i2c_init(void);
uint8_t i2c_get_byte(uint8_t ack);
uint8_t i2c_write_byte(uint8_t data);
uint8_t i2c_start(void);
uint8_t i2c_address(uint8_t adr, uint8_t mode);
void i2c_stop(void);

#endif
