/*
 * servo.c
 *
 *  Created on: Jul 18, 2026
 *      Author: hwido
 */

#define SERVO_PRIVATE
#include "servo.h"

#ifdef _USE_SERVO


bool servoInit(const SERVO_CONFIG *config, uint8_t config_count)
{
	if(config == NULL)	return false;

	if(config_count ==0 || config_count > _SERVO_MAX_CH)	return false;

	servo_count = config_count;

	for(uint8_t ch = 0; ch < servo_count ; ch++)
	{
		servo_info[ch].config = config[ch];

		servo_info[ch].current_angle = config[ch].center_angle;

		servo_info[ch].initialized = true;
		servo_info[ch].started = false;
	}
	return true;

}

static bool servoIsValidChannel(uint8_t ch)
{
	return ch < servo_count;
}

static uint16_t servoClampAngle(uint8_t ch, uint16_t angle)
{
	if(angle < servo_info[ch].config.min_angle)
	{
		angle = servo_info[ch].config.min_angle;
	}

	if(angle > servo_info[ch].config.max_angle)
	{
		angle = servo_info[ch].config.max_angle;
	}
	return angle;
}

bool servoStart(uint8_t ch)
{
	if(!servoIsValidChannel(ch))	return false;
	if(!servo_info[ch].initialized)	return false;
	if(servo_info[ch].started)	return false;

	if(HAL_TIM_PWM_Start(
			servo_info[ch].config.htim,
			servo_info[ch].config.tim_channel) != HAL_OK)
	{
		return false;
	}
	servo_info[ch].started = true;
	return servoMoveCenter(ch);

}


bool servoStop(uint8_t ch)
{
    if (!servoIsValidChannel(ch))
    {
        return false;
    }

    if (!servo_info[ch].initialized)
    {
        return false;
    }

    if (!servo_info[ch].started)
    {
        return true;
    }

    if (HAL_TIM_PWM_Stop(
            servo_info[ch].config.htim,
            servo_info[ch].config.tim_channel) != HAL_OK)
    {
        return false;
    }

    servo_info[ch].started = false;

    return true;
}


bool servoSetAngle(uint8_t ch, uint8_t angle)
{
    uint16_t target_angle;
    uint16_t pulse_us;

    if (!servoIsValidChannel(ch))
    {
        return false;
    }

    if (!servo_info[ch].initialized)
    {
        return false;
    }

    if (!servo_info[ch].started)
    {
        return false;
    }

    target_angle = servoClampAngle(ch, angle);

    pulse_us = servoAngleToPulseUs(
        ch,
        target_angle
    );

    if (!servoSetPulseUs(ch, pulse_us))
    {
        return false;
    }

    servo_info[ch].current_angle = target_angle;

    return true;
}


bool servoSetPulseUs(
    uint8_t ch,
    uint16_t pulse_us)
{
    uint32_t compare_tick;

    if (!servoIsValidChannel(ch))
    {
        return false;
    }

    if (!servo_info[ch].initialized)
    {
        return false;
    }

    if (!servo_info[ch].started)
    {
        return false;
    }

    if (pulse_us < servo_info[ch].config.min_pulse_us)
    {
        pulse_us = servo_info[ch].config.min_pulse_us;
    }

    if (pulse_us > servo_info[ch].config.max_pulse_us)
    {
        pulse_us = servo_info[ch].config.max_pulse_us;
    }

    compare_tick = servoPulseUsToTick(
        ch,
        pulse_us
    );

    __HAL_TIM_SET_COMPARE(
        servo_info[ch].config.htim,
        servo_info[ch].config.tim_channel,
        compare_tick
    );

    return true;
}


bool servoMove45(uint8_t ch)
{
    return servoSetAngle(ch, 45);
}


bool servoMove65(uint8_t ch)
{
    return servoSetAngle(ch, 65);
}


bool servoMoveCenter(uint8_t ch)
{
    if (!servoIsValidChannel(ch))
    {
        return false;
    }

    return servoSetAngle(
        ch,
        servo_info[ch].config.center_angle
    );
}


uint8_t servoGetAngle(uint8_t ch)
{
    if (!servoIsValidChannel(ch))
    {
        return 0;
    }

    return (uint8_t)servo_info[ch].current_angle;
}


bool servoIsStarted(uint8_t ch)
{
    if (!servoIsValidChannel(ch))
    {
        return false;
    }

    return servo_info[ch].started;
}



/* =========================================================
 * PRIVATE MEMBER FUNC
 * ========================================================= */


static uint16_t servoAngleToPulseUs(
    uint8_t ch,
    uint16_t angle)
{
    const SERVO_CONFIG *config;
    uint32_t angle_range;
    uint32_t pulse_range;
    uint32_t pulse_us;

    config = &servo_info[ch].config;

    angle = servoClampAngle(ch, angle);

    if (config->reverse)
    {
        angle =
            config->max_angle -
            (angle - config->min_angle);
    }

    angle_range =
        config->max_angle -
        config->min_angle;

    pulse_range =
        config->max_pulse_us -
        config->min_pulse_us;

    pulse_us =
        config->min_pulse_us +
        (
            ((uint32_t)(angle - config->min_angle) *
            pulse_range)
            /
            angle_range
        );

    return (uint16_t)pulse_us;
}


static uint32_t servoPulseUsToTick(
    uint8_t ch,
    uint16_t pulse_us)
{
    uint64_t tick;

    tick =
        (uint64_t)pulse_us *
        servo_info[ch].config.tim_hz;

    tick /= 1000000;

    return (uint32_t)tick;
}

#endif //USE_SERVO
