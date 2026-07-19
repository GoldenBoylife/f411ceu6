/*
 * ap.c
 *
 *  Created on: Feb 26, 2025
 *      Author: hwido
 */

#include "ap.h"
#include "def.h"
#include "app_config.h"

#include "bsp/bsp.h"

#include "utils/servo/servo.h"
#include "utils/led/led.h"


void apInit()
{
	if(!bspInit())	return;
	uartInit();

    servoStart(PETBOT_SERVO_HEAD_CH);
    servoStart(PETBOT_SERVO_NECK_CH);

    servoMoveCenter(PETBOT_SERVO_HEAD_CH);
    servoMoveCenter(PETBOT_SERVO_NECK_CH);

}

void apMain()
{
	uartPrintf(_UART_CH2,"123");

	while(1)
	{
        #if 0
		servoMove45(_SERVO_CH0);
		servoMove45(_SERVO_CH1);

		HAL_Delay(1000);
        servoSetAngle(_SERVO_CH0, 135);
        servoSetAngle(_SERVO_CH1, 115);

        HAL_Delay(1000);


        servoMoveCenter(_SERVO_CH0);
        servoMoveCenter(_SERVO_CH1);

        HAL_Delay(1000);
        #elif 0
        if (gpioRead(_GPIO_CH_BTN_USER))
        {
            // gpioWrite(_GPIO_CH4, true);
            ledOn(_LED_CH_USER);
        }
        else
        {
            ledOff(_LED_CH_USER);
        }

        HAL_Delay(10);
        #elif 1
        gpioWrite(_LED_CH_USER, true);
		#elif 0
        bool pressed = gpioRead(_GPIO_CH_BTN_USER);

        uartPrintf(
            _UART_CH2,
            "BTN_USER: %d\r\n",
            pressed
        );

        HAL_Delay(200);
        #endif 
	}
}
