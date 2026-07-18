/*
 * ap.c
 *
 *  Created on: Feb 26, 2025
 *      Author: hwido
 */
#include "def.h"
#include "ap.h"


char api[30]="/data";
char api_key[30] = "GGGG";

uint8_t f1;
uint32_t f2;


void apInit()
{
//	uartInit();
}
void apMain()
{
	uartPrintf(_DEF_UART_CH2,"123");

	while(1)
	{
	}
}
