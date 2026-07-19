/*
 * def.h
 *
 *  Created on: Feb 26, 2025
 *      Author: hwido
 */

#ifndef INCLUDE_DEF_H_
#define INCLUDE_DEF_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> //uint8_t 종류

#include <stdarg.h> //uartPrintf

#include "string.h"
#include <stdlib.h>

#include <main.h>  // 꼭 필요.


/* =========================================================
 * Servo
 * ========================================================= */
#define _USE_GPIO
#define _GPIO_MAX_CH 7

#define _GPIO_CH0 0  //LED_USER
#define _GPIO_CH1 1  //BTN_USER
#define _GPIO_CH2 2  //BTN0
#define _GPIO_CH3 3  //LED0
#define _GPIO_CH4 4  //LED1
#define _GPIO_CH5 5  //LED2
#define _GPIO_CH5 6  //LED3


/* =========================================================
 * UART
 * ========================================================= */

#define _USE_HW_UART
#define 	_UART_MAX_CH 2
#define _UART_CH1 1
#define _UART_CH2 2


/* =========================================================
 * Servo
 * ========================================================= */
#define _USE_SERVO
#define _SERVO_MAX_CH 2
    #define _SERVO_CH0 0
    #define _SERVO_CH1 1

#endif /* INCLUDE_DEF_H_ */
