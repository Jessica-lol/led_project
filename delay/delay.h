#ifndef DELAY_H
#define DELAY_H
#include "stm32f4xx_hal.h"
void delay_init(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
void delayus(uint32_t us);
#endif