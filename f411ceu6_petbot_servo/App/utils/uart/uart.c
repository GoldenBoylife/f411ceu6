/*
 * uart.c
 *
 *  Created on: Mar 2, 2025
 *      Author: hwido
 */


#include "uart.h"

#ifdef _USE_HW_UART

#define UART_Q_BUF_MAX 256

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
//extern UART_HandleTypeDef huart5;

static bool is_open[_UART_MAX_CH];


//q_in,q_out은 중급플젝의 qbufferFlush 와 같음
static uint16_t q_in[_UART_MAX_CH] = {0,};
static uint16_t q_out[_UART_MAX_CH] = {0,};
static uint8_t q_buf[_UART_MAX_CH][UART_Q_BUF_MAX];


bool uartInit(void)
{

    is_open[_UART_MAX_CH] = false;
    HAL_UART_Receive_DMA(&huart1, &q_buf[0][0],UART_Q_BUF_MAX);
    HAL_UART_Receive_DMA(&huart2, &q_buf[1][0],UART_Q_BUF_MAX);
//    HAL_UART_Receive_DMA(&huart5, &q_buf[2][0],UART_Q_BUF_MAX);

  return true;

}

/*uartOpen은 이미 main.c에 있어서 안해도 될듯*/
uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length)
{
  uint32_t ret =0;
  HAL_StatusTypeDef hal_ret;

  switch(ch)
  {
    case _UART_CH1:
        hal_ret = HAL_UART_Transmit(&huart1,p_data,length,100); //100
        //맨마지막 Timeout 인자는 100ms정도로 한다.
        if(hal_ret ==HAL_OK)
        {
          ret = length;
        }
        break;
    /*ultra sensor여서 write는 필요 없다.*/
     case _UART_CH2:
         hal_ret = HAL_UART_Transmit(&huart2,p_data,length,100); //100
         //맨마지막 Timeout 인자는 100ms정도로 한다.
         if(hal_ret ==HAL_OK)
         {
           ret = length;
         }
         break;

  }

  return ret;
}

/*return value is rest of Q_size*/
uint32_t uartAvailable(uint8_t ch)
{
  uint32_t ret =0;

  switch(ch)
  {
    case _UART_CH1:
      q_in[0] = (UART_Q_BUF_MAX - huart1.hdmarx->Instance->NDTR) % UART_Q_BUF_MAX;
      //Calculate the current input pointer based on the DMA register NDTR
      // q_in = (254-0)/254
      //하나도 안썼으면, 1
      ret = (UART_Q_BUF_MAX + q_in[0] - q_out[0]) % UART_Q_BUF_MAX;
      //?rest of Q size : 0~253
      // cliPrintf("UART_CH3 Available\r\n");
      break;
    case _UART_CH2:
      q_in[1] = (UART_Q_BUF_MAX - huart2.hdmarx->Instance->NDTR) % UART_Q_BUF_MAX;
      //Calculate the current input pointer based on the DMA register NDTR
      // q_in = (254-0)/254
      //하나도 안썼으면, 1
      ret = (UART_Q_BUF_MAX + q_in[1] - q_out[1]) % UART_Q_BUF_MAX;
      //?rest of Q size : 0~253
      // cliPrintf("UART_CH3 Available\r\n");
      break;
//    case _DEF_UART_CH5:
//      q_in[2] = (UART_Q_BUF_MAX - huart5.hdmarx->Instance->NDTR) % UART_Q_BUF_MAX;
//      //Calculate the current input pointer based on the DMA register NDTR
//      // q_in = (254-0)/254
//      //하나도 안썼으면, 1
//      ret = (UART_Q_BUF_MAX + q_in[2] - q_out[2]) % UART_Q_BUF_MAX;
//      //?rest of Q size : 0~253
//      // cliPrintf("UART_CH3 Available\r\n");
//      break;

  }
  return ret;
}
uint32_t uartRead(uint8_t ch) //한바이트를 읽어옴.
{
  uint8_t ret = 0;
  // cliPrintf("uartRead\r\n");

  switch(ch)
  {
    case _UART_CH1:
      //cliPrintf("uartRead_CH1\r\n");
      if(q_out[0] !=q_in[0])
      {
        ret = q_buf[0][q_out[0]];
        q_out[0] = (q_out[0] +1) %UART_Q_BUF_MAX;
        //q_out+1이 next_index이고,
        //q_out은 ptr_out이다.
      }
        break;
    case _UART_CH2:
      //cliPrintf("uartRead_CH2\r\n");
      if(q_out[1] !=q_in[1])
      {
        ret = q_buf[1][q_out[1]];
        q_out[1] = (q_out[1] +1) %UART_Q_BUF_MAX;
        //q_out+1이 next_index이고,
        //q_out은 ptr_out이다.
      }
      break;
//    case _DEF_UART_CH5:
//      cliPrintf("uartRead_CH5\r\n");
//      if(q_out[2] !=q_in[2])
//      {
//        ret = q_buf[2][q_out[2]];
//        q_out[2] = (q_out[2] +1) %UART_Q_BUF_MAX;
//        //q_out+1이 next_index이고,
//        //q_out은 ptr_out이다.
//      }
//      break;

  }
  return ret;
}



uint32_t uartPrintf(uint8_t ch, const char *fmt, ...)
{
  uint32_t ret =0;
  va_list arg;
  char print_buf[256];

  /*va_start와 va_end사이에 가변인자 쓰는 함수 넣어야 함*/
  va_start(arg,fmt);
  int len;
  len = vsnprintf(print_buf, 256, fmt,arg);
  va_end(arg);

  if(len >0)
  {
    ret = uartWrite(ch,(uint8_t *)print_buf,len);
  }

  return ret;
}


/*바로 위 함수와 약간 다르다. */
uint32_t uartVPrintf(uint8_t ch, const char *fmt, va_list arg)
{
  uint32_t ret =0;
  char print_buf[256];



  int len;
  len = vsnprintf(print_buf, 256, fmt,arg);
  va_end(arg);

  if(len >0)
  {
    ret = uartWrite(ch,(uint8_t *)print_buf,len);
  }

  return ret;
}


#endif /*_USE_HW_UART */
