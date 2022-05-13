// HAL_I2C_Mem_Write(&hi2c1, 0x88, 0, I2C_MEMADD_SIZE_8BIT, 0, 0, 0X10); //д

// HAL_I2C_Master_Receive(&hi2c1, 0x89, (uint8_t *)datatemp, 4, 0x10); //��
#include "myi2c.h"

i2c_t hi2c1;
i2c_t hi2c2;


void myi2c_init(void){
	hi2c1 = i2c1;
	hi2c2 = i2c2;
	
}

void delay_xus(__IO uint32_t nTime)
{
    __HAL_TIM_SetCounter(&htim4, 0);
    __HAL_TIM_ENABLE(&htim4);

    while (__HAL_TIM_GetCounter(&htim4) < nTime)
        ;

    __HAL_TIM_DISABLE(&htim4);
}

//--------------------------------------------
void SDA_Output(i2c_t i2c)
{
	  if(i2c==i2c1){
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = MYI2C_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MYI2C_SDA_PORT, &GPIO_InitStruct);
		}
		if(i2c==i2c2){
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = MYI2C2_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MYI2C2_SDA_PORT, &GPIO_InitStruct);
		}
}

void SDA_Input(i2c_t i2c)
{
	if(i2c==i2c1){
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = MYI2C_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MYI2C_SDA_PORT, &GPIO_InitStruct);
	}
	if(i2c==i2c2){
		GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = MYI2C2_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MYI2C2_SDA_PORT, &GPIO_InitStruct);
	}
}

void SCL_Output(i2c_t i2c)
{
	if(i2c==i2c1){
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = MYI2C_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MYI2C_SCL_PORT, &GPIO_InitStruct);
	}
	if(i2c==i2c2){
		GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = MYI2C2_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MYI2C2_SCL_PORT, &GPIO_InitStruct);
	}
}

void SCL_Input(i2c_t i2c)
{
	if(i2c==i2c1){
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = MYI2C_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MYI2C_SCL_PORT, &GPIO_InitStruct);
	}
	if(i2c==i2c2){
		GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = MYI2C_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MYI2C_SCL_PORT, &GPIO_InitStruct);
	}
}

void I2C_Init(i2c_t i2c)
{
		if(i2c==i2c1){
    SCL_Output(hi2c1);
    SDA_Output(hi2c1);
    SCL_Dout_HIGH();
    SDA_Dout_HIGH();	
		}
		if(i2c==i2c2){
    SCL_Output(hi2c2);
    SDA_Output(hi2c2);
    SCL2_Dout_HIGH();
    SDA2_Dout_HIGH();			
		}
}

//����IIC��ʼ�ź�

void I2C_Start(i2c_t i2c)
{
	if(i2c==i2c1){
    SDA_Output(hi2c1);
    SDA_Dout_HIGH();
    SCL_Dout_HIGH();
    Delay_us(4);
    SDA_Dout_LOW();
    Delay_us(4);
    SCL_Dout_LOW();
	}
		if(i2c==i2c2){
    SDA_Output(hi2c2);
    SDA2_Dout_HIGH();
    SCL2_Dout_HIGH();
    Delay_us(4);
    SDA2_Dout_LOW();
    Delay_us(4);
    SCL2_Dout_LOW();
	}
}

//����IICֹͣ�ź�

void I2C_Stop(i2c_t i2c)
{
	if(i2c==i2c1){
    SDA_Output(hi2c1);
    SCL_Dout_LOW();
    SDA_Dout_LOW();
    Delay_us(4);
    SCL_Dout_HIGH();
    SDA_Dout_HIGH();
    Delay_us(4);
	}
		if(i2c==i2c2){
    SDA_Output(hi2c2);
    SCL2_Dout_LOW();
    SDA2_Dout_LOW();
    Delay_us(4);
    SCL2_Dout_HIGH();
    SDA2_Dout_HIGH();
    Delay_us(4);
	}
}

uint8_t I2C_Wait_Ack(i2c_t i2c)
{
	if(i2c==i2c1){
    uint8_t ucErrTime = 0;
    SDA_Input(hi2c1);
    SDA_Dout_HIGH();
    Delay_us(1);
    SCL_Dout_HIGH();
    Delay_us(1);
    while (SDA_Data_IN())
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            I2C_Stop(hi2c1);
            return 1;
        }
    }
    SCL_Dout_LOW(); //ʱ�����0
    return 0;
	}
		if(i2c==i2c2){
    uint8_t ucErrTime = 0;
    SDA_Input(hi2c2);
    SDA2_Dout_HIGH();
    Delay_us(1);
    SCL2_Dout_HIGH();
    Delay_us(1);
    while (SDA2_Data_IN())
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            I2C_Stop(i2c2);
            return 1;
        }
    }
    SCL2_Dout_LOW(); //ʱ�����0
    return 0;
	}
		return 0;
}

//����ACKӦ��

void I2C_Ack(i2c_t i2c)
{
	if(i2c==i2c1){
    SCL_Dout_LOW();
    SDA_Output(hi2c1);
    SDA_Dout_LOW();
    Delay_us(2);
    SCL_Dout_HIGH();
    Delay_us(2);
    SCL_Dout_LOW();
	}
	if(i2c==i2c2){
    SCL2_Dout_LOW();
    SDA_Output(hi2c2);
    SDA2_Dout_LOW();
    Delay_us(2);
    SCL2_Dout_HIGH();
    Delay_us(2);
    SCL2_Dout_LOW();
	}
}

//������ACKӦ��

void I2C_NAck(i2c_t i2c)
{
	if(i2c==i2c1){
    SCL_Dout_LOW();
    SDA_Output(hi2c1);
    SDA_Dout_HIGH();
    Delay_us(2);
    SCL_Dout_HIGH();
    Delay_us(2);
    SCL_Dout_LOW();
	}
		if(i2c==i2c2){
    SCL2_Dout_LOW();
    SDA_Output(hi2c2);
    SDA2_Dout_HIGH();
    Delay_us(2);
    SCL2_Dout_HIGH();
    Delay_us(2);
    SCL2_Dout_LOW();
	}
}
// IIC����һ���ֽ�
//���شӻ�����Ӧ��
// 1����Ӧ��
// 0����Ӧ��
void I2C_Send_Byte(i2c_t i2c,uint8_t txd)
{
	if(i2c==i2c1){
    uint8_t t;
    //����ʱ�ӿ�ʼ���ݴ���
    SDA_Output(hi2c1);
    SCL_Dout_LOW();
    for (t = 0; t < 8; t++)
    {
        SDA_Write((txd & 0x80) >> 7);
        txd <<= 1;
        Delay_us(5); //��TEA5767��������ʱ���Ǳ����
        SCL_Dout_HIGH();
        Delay_us(5);
        SCL_Dout_LOW();
        // Delay_us(2);
    }
	}
		if(i2c==i2c2){
    uint8_t t;
    //����ʱ�ӿ�ʼ���ݴ���
    SDA_Output(hi2c2);
    SCL2_Dout_LOW();
    for (t = 0; t < 8; t++)
    {
        SDA2_Write((txd & 0x80) >> 7);
        txd <<= 1;
        Delay_us(5); //��TEA5767��������ʱ���Ǳ����
        SCL2_Dout_HIGH();
        Delay_us(5);
        SCL2_Dout_LOW();
        // Delay_us(2);
    }
	}
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t I2C_Read_Byte(i2c_t i2c,uint8_t ack)
{
	unsigned char i, receive = 0;
	if(i2c==i2c1){
    //unsigned char i, receive = 0;
    // SDA����Ϊ����
    SDA_Input(hi2c1);
    for (i = 0; i < 8; i++)
    {
        SCL_Dout_LOW();
        Delay_us(5);
        SCL_Dout_HIGH();
        receive <<= 1;
        if (SDA_Data_IN())
            receive++;
        Delay_us(5);
    }
    if (!ack)
        I2C_NAck(hi2c1); //����nACK
    else
        I2C_Ack(hi2c1); //����ACK

    return receive;
	}
	if(i2c==i2c2){
    //unsigned char i, receive = 0;
    // SDA����Ϊ����
    SDA_Input(hi2c2);
    for (i = 0; i < 8; i++)
    {
        SCL2_Dout_LOW();
        Delay_us(5);
        SCL2_Dout_HIGH();
        receive <<= 1;
        if (SDA2_Data_IN())
            receive++;
        Delay_us(5);
    }
    if (!ack)
        I2C_NAck(hi2c2); //����nACK
    else
        I2C_Ack(hi2c2); //����ACK

    return receive;
	}
	return receive;
}
