/*
 * bsp_servo.c
 *
 *  Created on: Jul 18, 2026
 *      Author: hwido
 */


#include "bsp_servo.h"
#include "utils/servo/servo.h"




extern TIM_HandleTypeDef htim3;

static const SERVO_CONFIG servo_config[_SERVO_MAX_CH] =
{
		/*SERVO_CH0*/
		{
				.htim 			= &htim3,
				.tim_channel 	= TIM_CHANNEL_1,
				.tim_hz		= 1000000,

				.min_pulse_us 	= 500,
				.center_pulse_us= 1500,
				.max_pulse_us 	= 2500,

				.min_angle 		= 0,
				.center_angle 	= 90,
				.max_angle		= 180,

				.reverse		= true
		},
		/*SERVO_CH1*/
		{
			.htim            = &htim3,
			.tim_channel     = TIM_CHANNEL_2,
			.tim_hz        = 1000000,

			.min_pulse_us    = 500,
			.center_pulse_us = 1500,
			.max_pulse_us    = 2500,

			.min_angle       = 0,
			.center_angle    = 90,
			.max_angle       = 180,

			.reverse         = true
		}
};

bool bspServoInit(void)
{
	return servoInit(
			servo_config,
			_SERVO_MAX_CH
	);
}
