/*
 * led.h
 *
 *  Created on: Jul 19, 2026
 *      Author: hwido
 */

#ifndef UTILS_LED_LED_H_
#define UTILS_LED_LED_H_

#include "def.h"

/* =========================================================
 * PUBLIC MEMBER FUNC
 * ========================================================= */

bool ledOn(uint8_t ch);
bool ledOff(uint8_t ch);
bool ledToggle(uint8_t ch);

#endif /* UTILS_LED_LED_H_ */
