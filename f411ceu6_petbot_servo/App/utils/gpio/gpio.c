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

	for(uint8_t ch = 0 ; ch < gpio_count_; ch++)
	{
		if(config[ch].port == NULL)	return false;
		gpio_info_[ch].config = config[ch];
		gpio_info_[ch].initialized = true;
	}
	return true;
}

/*active가 true 시 LED-ON*/
bool gpioWrite(uint8_t ch, bool active)
{
	GPIO_PinState output_state;

	if(!gpioIsValidChannel(ch)) 	return false;
	/*각 설정된 active_state설정에 따라 값이 바뀌므로 필요*/
	if(active)
	{
		output_state = gpioGetOnState(ch);
	}
	else
	{
		output_state = gpioGetOffState(ch);
	}

	HAL_GPIO_WritePin(
		gpio_info_[ch].config.port, 
		gpio_info_[ch].config.pin,
		output_state	
	);

	return true;
}

bool gpioRead(uint8_t ch) 
{
	GPIO_PinState pin_state;
	if(!gpioIsValidChannel(ch))	return false;

	pin_state = HAL_GPIO_ReadPin(
		gpio_info_[ch].config.port,
		gpio_info_[ch].config.pin
	);

	return pin_state == gpioGetOnState(ch);
}

bool gpioToggle(uint8_t ch) 
{
	if(!gpioIsValidChannel(ch)) return false;

	HAL_GPIO_TogglePin(gpio_info_[ch].config.port, gpio_info_[ch].config.pin);

	return true;
}



/* =========================================================
 * PRIVATE MEMBER FUNC
 * ========================================================= */


 static bool gpioIsValidChannel(uint8_t ch) 
 {
	if(ch >= gpio_count_)	return false;

	if(!gpio_info_[ch].initialized)	return false;

	return true;
 }

 static GPIO_PinState gpioGetOnState(uint8_t ch) 
 {
	return gpio_info_[ch].config.on_state;
 }
 
 /*get 끄는 값  
 	- 만약 내장된 PC13처럼 GND연결되어야 켜지는 led는 
 		on_state가 GPIO_PIN_RESET으로 저장되어 있어서, 
		아래 흐름대로 하면 GPIO_PIN_SET을 줘서 off된다.
 */
 static GPIO_PinState gpioGetOffState(uint8_t ch) 
{
	if(gpio_info_[ch].config.on_state == GPIO_PIN_SET)
	{
		return GPIO_PIN_RESET;
	}
	return GPIO_PIN_SET;
}
