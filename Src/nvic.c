/*
 * nvic.c
 *
 *  Created on: Jun 12, 2021
 *      Author: Kacper Janowski
 */

#include "nvic.h"

void EXTI0_1_IRQ_handler(void) {
	// Check that EXTI1 is the line that triggered
	if (EXTI->PR & (1 << BUTTON_PIN)) {
		// Clear interrupt flag
		EXTI->PR |= (1 << BUTTON_PIN);

		// toggle the LED state
		led_on = !led_on;
	}
}
