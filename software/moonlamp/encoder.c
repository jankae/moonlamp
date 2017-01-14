#include "encoder.h"

void encoder_Init() {
	/* Initialize pins as inputs with pull-ups */
	ENCODER_DDR_A &= ~(1 << ENCODER_PIN_A);
	ENCODER_DDR_B &= ~(1 << ENCODER_PIN_B);
	ENCODER_PORT_A |= (1 << ENCODER_PIN_A);
	ENCODER_PORT_B |= (1 << ENCODER_PIN_B);

	encoder.state = 0;
}

int8_t encoder_Update() {
	uint8_t newState = 0;
	if (ENCODER_IN_A & (1 << ENCODER_PIN_A)) {
		newState |= 0x01;
	}
	if (ENCODER_IN_B & (1 << ENCODER_PIN_B)) {
		newState |= 0x02;
	}
	uint8_t diffState = newState ^ encoder.state;
	encoder.state = newState;
	if (diffState & 0x02) {
		/* got some movement */
		if ((newState & 0x02) ^ ((newState & 0x01) << 1)) {
			return -1;
		} else {
			return 1;
		}
	} else {
		/* no encoder movement */
		return 0;
	}
}
