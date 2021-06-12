/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Kacper Janowski
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "man.h"

int main(void)
{
	// Enable the GPIOB peripheral
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	// Enable the GPIOD peripheral
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	// Enable the SYSCFG peripheral
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	// Initialize the GPIO pins.
	// PB1 -> input mode with pull_up
	GPIOB->MODER &= ~(0x3 << (BUTTON_PIN*2));	// input mode
	GPIOB->PUPDR &= ~(0x3 << (BUTTON_PIN*2));
	GPIOB->PUPDR |= (0x1 << (BUTTON_PIN*2));	// Pull-up
	GPIOB->MODER &= ~(0x3 << (ROTARY_PIN*2));	// input mode
	GPIOB->PUPDR &= ~(0x3 << (ROTARY_PIN*2));
	GPIOB->PUPDR |= (0x1 << (ROTARY_PIN*2));	// Pull-up
	// PD12 is connected to LED
	// Set to push-pull low-speed output
	GPIOD->MODER &= ~(0x3 << (LED_PIN*2));		// Clear bits
	GPIOD->MODER |= (0x1 << (LED_PIN*2));		// output mode
	GPIOD->OTYPER &= ~(0x1 << LED_PIN);			// push-pull
	GPIOD->PUPDR &= ~(0x3 << (LED_PIN*2));		// no pull-up, pull-down

	// Set SYSCFG to connect the button EXIT line to GPIOB
	SYSCFG->EXTICR[BUTTON_PIN/4] &= ~(0xF << (BUTTON_PIN % 4) * 4);		// Clear
	SYSCFG->EXTICR[BUTTON_PIN/4] |= (0x1 << (BUTTON_PIN % 4) * 4);		// Set

	// Setup EXTI interrupts for falling input on the button pin
	EXTI->IMR |= (1 << BUTTON_PIN);
	// Disable the 'rising edge' trigger (button release)
	EXTI->RTSR &= ~(1 << BUTTON_PIN);
	// Enable the 'falling edge' trigger (button press)
	EXTI->FTSR |= (1 << BUTTON_PIN);
	// Enable the NVIC interrupt at  minimum priority
	NVIC_SetPriority(EXTI0_IRQn, 0x03);
	NVIC_EnableIRQ(EXTI0_IRQn);

	while (1) {
		if(led_on) {
			GPIOD->ODR |= (1 << LED_PIN);
		} else {
			GPIOD->ODR &= ~(1 << LED_PIN);
		}

	}
}



















