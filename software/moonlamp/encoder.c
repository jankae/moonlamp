#include "encoder.h"

#include <avr/interrupt.h>

static int8_t enc_delta;

const int8_t table[16] = {0,0,1,0,0,0,0,-1,-1,0,0,0,0,1,0,0};

void Encoder_Init() {
	/* Set as inputs */
	ENC_A_DDR &= ~(1<<ENC_A_BIT);
	ENC_B_DDR &= ~(1<<ENC_B_BIT);
	ENC_BUTTON_DDR &= ~(1<<ENC_BUTTON_BIT);
	/* Enable pullups */
	ENC_A_PORT |= (1<<ENC_A_BIT);
	ENC_B_PORT |= (1<<ENC_B_BIT);
	ENC_BUTTON_PORT |= (1<<ENC_BUTTON_BIT);
}

void Encoder_Update() {
    static int8_t last=0;

    last = (last << 2)  & 0x0F;
    if (ENC_A_PIN & (1<<ENC_A_BIT)) last |=2;
    if (ENC_B_PIN & (1<<ENC_B_BIT)) last |=1;
    enc_delta += table[last];
}
int8_t Encoder_GetMovement() {
	int8_t ret;
	cli();
	ret = enc_delta;
	enc_delta = 0;
	sei();
	return ret;
}
uint8_t Encoder_GetPress() {
	if(ENC_BUTTON_PIN & (1<<ENC_BUTTON_BIT)) {
		/* not pressed */
		return 0;
	} else {
		/* pressed */
		return 1;
	}
}
