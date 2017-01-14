
#ifndef ENCODER_H_
#define ENCODER_H_

#include <avr/io.h>

#define ENCODER_DDR_A		DDRA
#define ENCODER_PORT_A		PORTA
#define ENCODER_IN_A		PINA
#define ENCODER_PIN_A		(3)

#define ENCODER_DDR_B		DDRA
#define ENCODER_PORT_B		PORTA
#define ENCODER_IN_B		PINA
#define ENCODER_PIN_B		(4)

struct {
	uint8_t state;
} encoder;

/**
 * \brief Initializes encoder pins and status
 */
void encoder_Init();

/**
 * \brief Updates encoder state and retrieces movement
 *
 * \return encoder movement in ticks (-1, 0 or 1)
 */
int8_t encoder_Update();



#endif
