/*
 * uart.h
 *
 *  Created on: Mar 2, 2025
 *      Author: hwido
 */

#ifndef UTILS_UART_UART_H_
#define UTILS_UART_UART_H_

#include "def.h"

#ifdef _USE_HW_UART

bool uartInit(void);
uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length);
uint32_t uartAvailable(uint8_t ch);
uint32_t uartRead(uint8_t ch); //한바이트를 읽어옴.
uint32_t uartPrintf(uint8_t ch, const char *fmt, ...);
// ...는 가변인자 뜻함. 인자 갯수 랜덤
uint32_t uartVPrintf(uint8_t ch, const char *fmt, va_list arg);


#endif /* _USR_HW_UART */

#endif /* UTILS_UART_UART_H_ */
