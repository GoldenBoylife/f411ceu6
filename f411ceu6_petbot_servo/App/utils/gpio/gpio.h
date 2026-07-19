/*
 * gpio.h
 *
 *  Created on: Jul 18, 2026
 *      Author: hwido
 */

#ifndef UTILS_GPIO_GPIO_H_
#define UTILS_GPIO_GPIO_H_

#include "def.h"

#include <stdbool.h>
#include <stdint.h>




/* =========================================================
 * PUBLIC TYPE
 * ========================================================= */
typedef struct
{
	GPIO_TypeDef *port;
	uint16_t pin;

	GPIO_PinState on_state;
}GPIO_CONFIG;


/* =========================================================
 * PUBLIC METHOD
 * ========================================================= */

bool gpioInit(const GPIO_CONFIG *config);
bool gpioWrite(uint8_t ch, bool active);

bool gpioRead(uint8_t ch);
bool gpioToggle(uint8_t ch);
#ifdef GPIO_PRIVATE
/* =========================================================
 * PRIVATE TYPE
 * ========================================================= */
typedef struct
{
	GPIO_CONFIG config;
	bool initialized;
} GPIO_INFO;

static GPIO_INFO gpio_info_[_GPIO_MAX_CH];


/* =========================================================
 * PRIVATE METHOD
 * ========================================================= */
static bool gpioIsValidChannel(uint8_t ch);
static GPIO_PinState gpioGetOnState(uint8_t ch);
static GPIO_PinState gpioGetOffState(uint8_t ch);
  



#endif //GPIO_PRIVATE

#endif /* UTILS_GPIO_GPIO_H_ */
