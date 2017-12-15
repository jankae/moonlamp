#ifndef ENCODER_H_
#define ENCODER_H_

#include <avr/io.h>

#define ENC_A_DDR					DDRC
#define ENC_A_PORT					PORTC
#define ENC_A_PIN					PINC
#define ENC_A_BIT					(1)

#define ENC_B_DDR					DDRC
#define ENC_B_PORT					PORTC
#define ENC_B_PIN					PINC
#define ENC_B_BIT					(2)

#define ENC_BUTTON_DDR				DDRC
#define ENC_BUTTON_PORT				PORTC
#define ENC_BUTTON_PIN				PINC
#define ENC_BUTTON_BIT				(3)

void Encoder_Init();

void Encoder_Update();
int8_t Encoder_GetMovement();
uint8_t Encoder_GetPress();

#endif
