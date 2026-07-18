/*
 * gpio.c
 *
 *  Created on: Jul 18, 2026
 *      Author: hwido
 */



#define GPIO_PRIVATE
#include "gpio.h"


/* =========================================================
 * PUBLIC MEMBER FUNC
 * ========================================================= */

bool gpioInit(const GPIO_CONFIG *config, uint8_t config_count)
{
	if(config == NULL) 	return false;

	if(config_count == 0 || config_count > _GPIO_MAX_CH)	return false;

	gpio_count_ = config_count;

	for(uint8_t ch = 0 ; ch < gpio_count; ch++)
	{
		if(config[ch].port = NULL)	return false;
		gpio_info_[ch].config = config[ch];
		gpio_info_[ch].initialized = true;
	}
	return true;
}



/* =========================================================
 * PRIVATE MEMBER FUNC
 * ========================================================= */
