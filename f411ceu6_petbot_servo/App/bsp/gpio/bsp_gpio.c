/*
 * bsp_gpio.c
 *
 *  Created on: Jul 18, 2026
 *      Author: hwido
 */


#include "bsp_gpio.h"
#include "utils/gpio/gpio.h"

static const GPIO_CONFIG gpio_config[_GPIO_MAX_CH] =
{
    /* _DEF_GPIO_CH_LED0
     * PB3
     * 외부 LED, Active High로 우선 설정
     */
    {
        .port       = LED0_GPIO_Port,
        .pin        = LED0_Pin,
        .on_state   = GPIO_PIN_SET
    },

    /* _DEF_GPIO_CH_LED1
     * PB4
     * 외부 LED, Active High로 우선 설정
     */
    {
        .port       = LED1_GPIO_Port,
        .pin        = LED1_Pin,
        .on_state   = GPIO_PIN_SET
    },

    /* _DEF_GPIO_CH_LCD_RST
     * PB5
     * LCD Reset은 보통 Active Low
     */
    {
        .port       = LCD_RST_GPIO_Port,
        .pin        = LCD_RST_Pin,
        .on_state   = GPIO_PIN_RESET
    },

    /* _DEF_GPIO_CH_LCD_DC
     * PB6
     * true를 Data Mode로 사용
     * SET = Data, RESET = Command
     */
    {
        .port       = LCD_DC_GPIO_Port,
        .pin        = LCD_DC_Pin,
        .on_state   = GPIO_PIN_SET
    },

    /* _DEF_GPIO_CH_LED_USER
     * PC13 실장 LED
     * GND 방향으로 전류가 흘러야 켜지는 Active Low
     */
    {
        .port       = LED_USER_GPIO_Port,
        .pin        = LED_USER_Pin,
        .on_state   = GPIO_PIN_RESET
    },

    /* _DEF_GPIO_CH_BTN_USER
     * PA0, Pull-down
     * 평소 Low, 누르면 High라고 가정
     */
    {
        .port       = BTN_USER_GPIO_Port,
        .pin        = BTN_USER_Pin,
        .on_state   = GPIO_PIN_RESET
    },

    /* _DEF_GPIO_CH_BTN0
     * PB7, Pull-down
     * 평소 Low, 누르면 High
     */
    {
        .port       = BTN0_GPIO_Port,
        .pin        = BTN0_Pin,
        .on_state   = GPIO_PIN_SET
    }
};


bool bspGpioInit(void)
{
	return gpioInit(gpio_config, _GPIO_MAX_CH);
}
