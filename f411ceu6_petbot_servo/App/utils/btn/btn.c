/*
 * btn.c
 *
 *  Created on: Jul 19, 2026
 *      Author: hwido
 */



#include "btn.h"
#include "utils/gpio/gpio.h"


bool btnRead(uint8_t ch)
{
	return gpioRead(ch);

}
