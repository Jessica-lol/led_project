#ifndef TCS34745_H 
#define TCS34745_H
#include "stm32f4xx_hal.h"
#include "myi2c.h"
#include "TCS_Code.h"
#include "delay.h"

void TCS34725_Write(unsigned char subAddr, unsigned char* dataBuffer, unsigned char bytesNumber);
void TCS34725_Read(unsigned char subAddr, unsigned char* dataBuffer, unsigned char bytesNumber);

unsigned char TCS34725_Init(void);
void TCS34725_SetIntegrationTime(uint8_t time);
void TCS34725_SetGain(uint8_t gain);
void TCS34725_Setup(void);
void TCS34725_Enable(void);
void TCS34725_Disable(void);
uint16_t TCS34725_GetChannelData(unsigned char reg);
uint8_t TCS34725_GetRawData(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c);
#endif
