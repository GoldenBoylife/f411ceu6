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


//char api[30]="/data";
//char api_key[30] = "GGGG";
//
//uint8_t f1;
//uint32_t f2;


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
		servoMove45(_SERVO_CH0);
		servoMove45(_SERVO_CH1);

		HAL_Delay(1000);
        servoSetAngle(_SERVO_CH0, 135);
        servoSetAngle(_SERVO_CH1, 115);

        HAL_Delay(1000);


        servoMoveCenter(_SERVO_CH0);
        servoMoveCenter(_SERVO_CH1);

        HAL_Delay(1000);
	}
}
