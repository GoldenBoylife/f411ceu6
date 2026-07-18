/*
 * servo.h
 *
 *  Created on: Jul 18, 2026
 *      Author: hwido
 */

#ifndef UTILS_SERVO_SERVO_H_
#define UTILS_SERVO_SERVO_H_

#include "def.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef _USE_SERVO



/* =========================================================
 * PUBLIC VARIABLES
 * ========================================================= */


typedef struct 
{
    TIM_HandleTypeDef *htim;
    uint32_t tim_channel;
    uint32_t tim_hz;

    uint16_t min_pulse_us;
    uint16_t center_pulse_us;
    uint16_t max_pulse_us;

    uint16_t min_angle;
    uint16_t center_angle;
    uint16_t max_angle;

    bool reverse;
} SERVO_CONFIG;

/* =========================================================
 * PUBLIC MEMBER FUNC
 * ========================================================= */

// bool servoInit(
//     SERVO_T *servo, 
//     TIM_HandleTypeDef *htim,
//     uint16_t channel,
//     uint16_t min_pulse_us,
//     uint16_t center_pulse_us,
//     uint16_t max_pulse_us
// );

bool  servoInit(
    const SERVO_CONFIG *config,
    uint8_t config_count
);

bool servoStart(uint8_t ch);
bool servoStop(uint8_t ch);

bool servoSetAngle(uint8_t ch, uint8_t angle);
bool servoSetPulseUs(uint8_t ch, uint16_t pulse_us);


bool servoMove45(uint8_t ch);
bool servoMove65(uint8_t ch);
bool servoMoveCenter(uint8_t ch);

uint8_t servoGetAngle(uint8_t ch);
bool servoIsStarted(uint8_t ch);


/* =========================================================
 * PRIVATE
 *
 * servo.c에서만 SERVO_PRIVATE을 정의하여 사용
 * ========================================================= */
#ifdef SERVO_PRIVATE
/* =========================================================
 * PRIVATE MEMBER VARIABLES
 * ========================================================= */

typedef struct
{
	SERVO_CONFIG config;
	uint16_t current_angle;

	bool initialized;
	bool started;


} SERVO_INFO;

static SERVO_INFO servo_info[_SERVO_MAX_CH];
static uint8_t servo_count = 0;

/* =========================================================
 * PRIVATE MEMBER FUNC
 * ========================================================= */
static bool servoIsValidChannel(uint8_t ch);
static uint16_t servoClampAngle(uint8_t ch, uint16_t angle);
static uint16_t servoAngleToPulseUs(uint8_t ch, uint16_t angle);
static uint32_t servoPulseUsToTick(uint8_t ch, uint16_t pulse_us);

#endif // SERVO_PRIVATE


#endif //_USE_SERVO

#endif /* UTILS_SERVO_SERVO_H_ */
