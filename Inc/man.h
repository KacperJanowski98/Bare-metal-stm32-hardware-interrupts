/*
 * man.h
 *
 *  Created on: Jun 12, 2021
 *      Author: kacpe
 */

#ifndef MAN_H_
#define MAN_H_

#include "stm32f4xx.h"

#define BUTTON_PIN		1
#define LED_PIN			12	// Green LED on STM32F407G-DISC1 (PD12)
#define ROTARY_PIN		0

volatile uint8_t led_on;

#endif /* MAN_H_ */
