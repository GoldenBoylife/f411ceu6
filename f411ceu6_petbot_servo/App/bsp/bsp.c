/*
 * bsp.c
 *
 *  Created on: Jul 18, 2026
 *      Author: hwido
 */


#include "bsp.h"
//#include "def.h"

#ifdef _USE_SERVO
	#include "bsp/servo/bsp_servo.h"
#endif




 /*각 하드웨어 초기화*/
bool bspInit(void)
{
    if(!bspServoInit())	return false;
//    bspLedInit();
//    bspUartInit();

    return true;
}


