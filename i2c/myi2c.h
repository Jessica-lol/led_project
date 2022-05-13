#ifndef __MYI2C_H__
#define __MYI2C_H__

#include "stm32f4xx_hal.h"
#include "main.h"
#include "stdint.h"
#include "tim.h"

typedef enum{
	i2c1=1,
	i2c2
}i2c_t;


#define CPU_FREQUENCY_MHZ 100
#define MYI2C_SCL_PIN I2C_SCL_Pin
#define MYI2C_SCL_PORT I2C_SCL_GPIO_Port
#define MYI2C_SDA_PIN I2C_SDL_Pin
#define MYI2C_SDA_PORT I2C_SDL_GPIO_Port

#define SDA_Dout_LOW() HAL_GPIO_WritePin(MYI2C_SDA_PORT, MYI2C_SDA_PIN, GPIO_PIN_RESET)
#define SDA_Dout_HIGH() HAL_GPIO_WritePin(MYI2C_SDA_PORT, MYI2C_SDA_PIN, GPIO_PIN_SET)
#define SDA_Data_IN() HAL_GPIO_ReadPin(MYI2C_SDA_PORT, MYI2C_SDA_PIN)
#define SCL_Dout_LOW() HAL_GPIO_WritePin(MYI2C_SCL_PORT, MYI2C_SCL_PIN, GPIO_PIN_RESET)
#define SCL_Dout_HIGH() HAL_GPIO_WritePin(MYI2C_SCL_PORT, MYI2C_SCL_PIN, GPIO_PIN_SET)
#define SCL_Data_IN() HAL_GPIO_ReadPin(MYI2C_SCL_PORT, MYI2C_SCL_PIN)
#define SDA_Write(XX) HAL_GPIO_WritePin(MYI2C_SDA_PORT, MYI2C_SDA_PIN, (XX ? GPIO_PIN_SET : GPIO_PIN_RESET))

#define MYI2C2_SCL_PIN I2C2_SCL_Pin
#define MYI2C2_SCL_PORT I2C2_SCL_GPIO_Port
#define MYI2C2_SDA_PIN I2C2_SDL_Pin
#define MYI2C2_SDA_PORT I2C2_SDL_GPIO_Port

#define SDA2_Dout_LOW() HAL_GPIO_WritePin(MYI2C2_SDA_PORT, MYI2C2_SDA_PIN, GPIO_PIN_RESET)
#define SDA2_Dout_HIGH() HAL_GPIO_WritePin(MYI2C2_SDA_PORT, MYI2C2_SDA_PIN, GPIO_PIN_SET)
#define SDA2_Data_IN() HAL_GPIO_ReadPin(MYI2C2_SDA_PORT, MYI2C2_SDA_PIN)
#define SCL2_Dout_LOW() HAL_GPIO_WritePin(MYI2C2_SCL_PORT, MYI2C2_SCL_PIN, GPIO_PIN_RESET)
#define SCL2_Dout_HIGH() HAL_GPIO_WritePin(MYI2C2_SCL_PORT, MYI2C2_SCL_PIN, GPIO_PIN_SET)
#define SCL2_Data_IN() HAL_GPIO_ReadPin(MYI2C2_SCL_PORT, MYI2C2_SCL_PIN)
#define SDA2_Write(XX) HAL_GPIO_WritePin(MYI2C2_SDA_PORT, MYI2C2_SDA_PIN, (XX ? GPIO_PIN_SET : GPIO_PIN_RESET))



extern i2c_t hi2c1;
extern i2c_t hi2c2;


void myi2c_init(void);
void I2C_Init(i2c_t i2c);
void I2C_Start(i2c_t i2c);
void I2C_Stop(i2c_t i2c);
void I2C_Send_Byte(i2c_t i2c,uint8_t txd);
uint8_t I2C_Read_Byte(i2c_t i2c,uint8_t ack);
void I2C_NAck(i2c_t i2c);
void I2C_Ack(i2c_t i2c);
uint8_t I2C_Wait_Ack(i2c_t i2c);

void delay_xus(__IO uint32_t nTime);

#define Delay_us(xx) delay_xus(xx)

#endif
