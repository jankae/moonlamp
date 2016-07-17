#ifndef SYSTIME_H_
#define SYSTIME_H_

#include <avr/io.h>
#include <avr/interrupt.h>

struct {
	uint16_t ms;
} time;

/**
 * \brief Initializes timer0 to overflow every ms
 */
void time_Init();

/**
 * \brief Waits for specific amount of time
 *
 * \param ms Time to wait in milliseconds
 */
void time_WaitMs(uint16_t ms);

/**
 * \brief Sets a timeout which can be checked later
 *
 * \param ms Time in milliseconds after which the timeout should elapse
 */
void time_SetTimeout(uint16_t ms);

/**
 * \brief Checks whether a timeout has elapsed
 *
 * \return 1 if timeout has elapsed, 0 otherwise
 */
uint8_t time_TimeoutElapsed(void);

#endif
