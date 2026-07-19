/*
 * led.c
 *
 *  Created on: Jul 19, 2026
 *      Author: hwido
 */

#include "led.h"
#include "utils/gpio/gpio.h"

bool ledOn(uint8_t ch)
{
    return gpioWrite(ch,true);
}


bool ledOff(uint8_t ch)
{
    return gpioWrite(ch,false);
}

bool ledToggle(uint8_t ch)
{
    return gpioToggle(ch);
}