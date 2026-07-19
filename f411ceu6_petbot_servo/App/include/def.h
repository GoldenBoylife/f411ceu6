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
 * GPIO
 * ├─ LED
 * ├─ BUTTON
 * └─ LCD
 * ========================================================= */
#define _USE_GPIO
#define _GPIO_MAX_CH 7

#define _GPIO_CH_LED0          	0   // LED0
#define _GPIO_CH_LED1           1 	// LED1-> 미사용
#define _GPIO_CH_LCD_RST        2	// LCD_RST
#define _GPIO_CH_LCD_DC    		3   // LCD_DC
#define _GPIO_CH_LED_USER       4   // LED_USER
#define _GPIO_CH_BTN_USER       5   // BTN_USER
#define _GPIO_CH_BTN0          	6   // BTN0

/* ===========================
* GPIO ├─ LED
* ============================*/
#define _USE_LED

#define _LED_CH0			_GPIO_CH_LED0
#define _LED_CH1			_GPIO_CH_LED1
#define _LED_CH_USER		_GPIO_CH_LED_USER



/* ===========================
* GPIO ├─ BTN
* ============================ */

#define _USE_BTN

#define _BTN_CH_USER		_GPIO_CH_BTN_USER
#define _BTN_CH0 			_GPIO_CH_BTN0

/* ===========================
* GPIO ├─ LCD
* ============================= */
#define _LCD_RST			_GPIO_CH_LCD_RST
#define	_LCD_DC				_GPIO_CH_LCD_DC





/* =========================================================
 * SERVO
 * ========================================================= */
#define _USE_SERVO
#define _SERVO_MAX_CH 2
    #define _SERVO_CH0 0
    #define _SERVO_CH1 1






/* =========================================================
 * UART
 * ========================================================= */
#define _USE_HW_UART
#define 	_UART_MAX_CH 2
#define _UART_CH1 1      //debugger
#define _UART_CH2 2      //terinal serial uart

//#define LOG(fmt, ...) uartPrintf(UART_CH2, fmt, ##__VA_ARGS__)

#endif /* INCLUDE_DEF_H_ */
