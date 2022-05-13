/***************************************************************************//**
 * @brief Writes data to a slave device.
 *
 * @param slaveAddress - Adress of the slave device.
 * @param dataBuffer - Pointer to a buffer storing the transmission data.
 * @param bytesNumber - Number of bytes to write.
 * @param stopBit - Stop condition control.
 *                  Example: 0 - A stop condition will not be sent;
 *                           1 - A stop condition will be sent.
*******************************************************************************/


#include "TCS34725.h"

i2c_t TCS_I2C;

void TCS34725_I2C_Write(uint8_t slaveAddress, 
						uint8_t* dataBuffer,
						uint8_t bytesNumber, 
						uint8_t stopBit)
{
	unsigned char i = 0;
	
	I2C_Start(TCS_I2C);;
	I2C_Send_Byte(TCS_I2C,(slaveAddress << 1) | 0x00);	   //发送从机地址写命令
	I2C_Wait_Ack(TCS_I2C);
	for(i = 0; i < bytesNumber; i++)
	{
		I2C_Send_Byte(TCS_I2C,*(dataBuffer + i));
		I2C_Wait_Ack(TCS_I2C);
	}
	if(stopBit == 1) I2C_Stop(TCS_I2C);
}

/***************************************************************************//**
 * @brief Reads data from a slave device.
 *
 * @param slaveAddress - Adress of the slave device.
 * @param dataBuffer - Pointer to a buffer that will store the received data.
 * @param bytesNumber - Number of bytes to read.
 * @param stopBit - Stop condition control.
 *                  Example: 0 - A stop condition will not be sent;
 *                           1 - A stop condition will be sent.
*******************************************************************************/
void TCS34725_I2C_Read(uint8_t slaveAddress, 
						uint8_t* dataBuffer, 
						uint8_t bytesNumber, 
						uint8_t stopBit)
{
	unsigned char i = 0;
	
	I2C_Start(TCS_I2C);
	I2C_Send_Byte(TCS_I2C,(slaveAddress << 1) | 0x01);	   //发送从机地址读命令
	I2C_Wait_Ack(TCS_I2C);
	for(i = 0; i < bytesNumber; i++)
	{
		if(i == bytesNumber - 1)
		{
			*(dataBuffer + i) = I2C_Read_Byte(TCS_I2C,0);//读取的最后一个字节发送NACK
		}
		else
		{
			*(dataBuffer + i) = I2C_Read_Byte(TCS_I2C,1);
		}
	}
	if(stopBit == 1)I2C_Stop(TCS_I2C);
}





/***************************************************************************//**
 * @brief Writes data into TCS34725 registers, starting from the selected
 *        register address pointer.
 *
 * @param subAddr - The selected register address pointer.
 * @param dataBuffer - Pointer to a buffer storing the transmission data.
 * @param bytesNumber - Number of bytes that will be sent.
 *
 * @return None.
*******************************************************************************/
void TCS34725_Write(unsigned char subAddr, unsigned char* dataBuffer, unsigned char bytesNumber)
{
    unsigned char sendBuffer[10] = {0, };
    unsigned char byte = 0;
    
    sendBuffer[0] = subAddr | TCS34725_COMMAND_BIT;
    for(byte = 1; byte <= bytesNumber; byte++)
    {
        sendBuffer[byte] = dataBuffer[byte - 1];
    }
	TCS34725_I2C_Write(TCS34725_ADDRESS, sendBuffer, bytesNumber + 1, 1);
}

/***************************************************************************//**
 * @brief Reads data from TCS34725 registers, starting from the selected
 *        register address pointer.
 *
 * @param subAddr - The selected register address pointer.
 * @param dataBuffer - Pointer to a buffer that will store the received data.
 * @param bytesNumber - Number of bytes that will be read.
 *
 * @return None.
*******************************************************************************/
void TCS34725_Read(unsigned char subAddr, unsigned char* dataBuffer, unsigned char bytesNumber)
{
	subAddr |= TCS34725_COMMAND_BIT;
	
	TCS34725_I2C_Write(TCS34725_ADDRESS, (unsigned char*)&subAddr, 1, 0);
	TCS34725_I2C_Read(TCS34725_ADDRESS, dataBuffer, bytesNumber, 1);
}




/***************************************************************************//**
 * @brief TCS34725初始化
 *
 * @return ID - ID寄存器中的值
*******************************************************************************/
unsigned char TCS34725_Init(void)
{
	TCS_I2C = hi2c1;
    unsigned char status[1] = {0};
	
	I2C_Init(TCS_I2C); 
	TCS34725_Read(TCS34725_ID, status, 1);
  return status[0];
}


/***************************************************************************//**
 * @brief TCS34725设置积分时间
 *
 * @return None
*******************************************************************************/
void TCS34725_SetIntegrationTime(uint8_t time)
{
	unsigned char cmd = time;
	
	TCS34725_Write(TCS34725_ATIME, &cmd, 1);
}
/***************************************************************************//**
 * @brief TCS34725设置增益
 *
 * @return None
*******************************************************************************/
void TCS34725_SetGain(uint8_t gain)
{
	unsigned char cmd = gain;
	
	TCS34725_Write(TCS34725_CONTROL, &cmd, 1);
}
/***************************************************************************//**
 * @brief TCS34725设置寄存器
 *
 * @return None
*******************************************************************************/
void TCS34725_Setup(void)
{
	TCS34725_SetIntegrationTime(TCS34725_INTEGRATIONTIME_240MS);
	TCS34725_SetGain(TCS34725_GAIN_4X);
}

/***************************************************************************//**
 * @brief TCS34725使能
 *
 * @return None
*******************************************************************************/
void TCS34725_Enable(void)
{
	unsigned char cmd = TCS34725_ENABLE_PON;
	
	TCS34725_Write(TCS34725_ENABLE, &cmd, 1);
	//delay_ms(3);//延时应该放在设置AEN之后
	cmd = TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN;
	TCS34725_Write(TCS34725_ENABLE, &cmd, 1);
	delay_ms(3);
}
/***************************************************************************//**
 * @brief TCS34725失能
 *
 * @return None
*******************************************************************************/
void TCS34725_Disable(void)
{
	unsigned char cmd = 0x00;
	
	TCS34725_Read(TCS34725_ENABLE, &cmd, 1);
	cmd = cmd & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
	TCS34725_Write(TCS34725_ENABLE, &cmd, 1);
}

/***************************************************************************//**
 * @brief TCS34725获取单个通道数据
 *
 * @return data - 该通道的转换值
*******************************************************************************/
uint16_t TCS34725_GetChannelData(unsigned char reg)
{
	unsigned char tmp[2] = {0,0};
	uint16_t data = 0;
	
	TCS34725_Read(reg, tmp, 2);
	data = ((uint16_t)tmp[1] << 8) | tmp[0];
	
	return data;
}
/***************************************************************************//**
 * @brief TCS34725获取各个通道数据
 *
 * @return 1 - 转换完成，数据可用
 *   	   0 - 转换未完成，数据不可用
*******************************************************************************/
uint8_t TCS34725_GetRawData(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
{
	unsigned char status[1] = {0};

	status[0] = TCS34725_STATUS_AVALID;
	
	TCS34725_Read(TCS34725_STATUS, status, 1);
	
	if(status[0] & TCS34725_STATUS_AVALID)
	{
		*c = TCS34725_GetChannelData(TCS34725_CDATAL);	
		*r = TCS34725_GetChannelData(TCS34725_RDATAL);	
		*g = TCS34725_GetChannelData(TCS34725_GDATAL);	
		*b = TCS34725_GetChannelData(TCS34725_BDATAL);
		return 1;
	}
	return 0;
}
