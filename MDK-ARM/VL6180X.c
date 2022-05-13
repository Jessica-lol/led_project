#include "VL6180.h"
//д	reg�Ĵ��� data����
i2c_t VL6180_I2C;
uint8_t VL6180X_WriteByte(uint16_t reg,uint8_t data)
{
	uint8_t Index_H = (uint8_t)(reg >> 8);
	uint8_t Index_L = (uint8_t)(reg & 0xFF);
	
	I2C_Start(VL6180_I2C);
	I2C_Send_Byte(VL6180_I2C,(VL6180X_DEFAULT_I2C_ADDR<<1)|0);
	if(I2C_Wait_Ack(VL6180_I2C))	//�ȴ�Ӧ��
	{
		I2C_Stop(VL6180_I2C);	
		return 1;		
	}
	I2C_Send_Byte(VL6180_I2C,Index_H);
	I2C_Wait_Ack(VL6180_I2C);	//�ȴ�ACK
	I2C_Send_Byte(VL6180_I2C,Index_L);
	I2C_Wait_Ack(VL6180_I2C);	//�ȴ�ACK
	I2C_Send_Byte(VL6180_I2C,data);
	if(I2C_Wait_Ack(VL6180_I2C))	//�ȴ�ACK
	{
		I2C_Stop(VL6180_I2C);	 
		return 1;		 
	}
	I2C_Stop(VL6180_I2C);
	return 0;	
}

//VL6180X��ȡ8λ����
uint8_t VL6180X_ReadByte(uint16_t reg)
{
	uint8_t res;
	uint8_t Index_H = (uint8_t)(reg >> 8);
	uint8_t Index_L = (uint8_t)(reg & 0xff);
    I2C_Start(VL6180_I2C); 
	I2C_Send_Byte(VL6180_I2C,(VL6180X_DEFAULT_I2C_ADDR<<1)|0);//����������ַ+д����	
	I2C_Wait_Ack(VL6180_I2C);		//�ȴ�Ӧ�� 
    I2C_Send_Byte(VL6180_I2C,Index_H);	//д�Ĵ�����ַ
    I2C_Wait_Ack(VL6180_I2C);		//�ȴ�Ӧ��
	I2C_Send_Byte(VL6180_I2C,Index_L);	//д�Ĵ�����ַ
	I2C_Wait_Ack(VL6180_I2C);	
	
    I2C_Start(VL6180_I2C);
	I2C_Send_Byte(VL6180_I2C,(VL6180X_DEFAULT_I2C_ADDR<<1)|1);//����������ַ+������	
    I2C_Wait_Ack(VL6180_I2C);		//�ȴ�Ӧ�� 
	res=I2C_Read_Byte(VL6180_I2C,0);//��ȡ����,����nACK 
    I2C_Stop(VL6180_I2C);			//����һ��ֹͣ���� 
	return res;
}


uint8_t VL6180X_Read_ID(void)
{
	return VL6180X_ReadByte(VL6180X_REG_IDENTIFICATION_MODEL_ID);
}

uint8_t VL6180X_Init(void)
{
	VL6180_I2C = hi2c2;
	if(VL6180X_Read_ID() == VL6180X_DEFAULT_ID)
	{	
		VL6180X_WriteByte(0x0207, 0x01);
		VL6180X_WriteByte(0x0208, 0x01);
		VL6180X_WriteByte(0x0096, 0x00);
		VL6180X_WriteByte(0x0097, 0xfd);
		VL6180X_WriteByte(0x00e3, 0x00);
		VL6180X_WriteByte(0x00e4, 0x04);
		VL6180X_WriteByte(0x00e5, 0x02);
		VL6180X_WriteByte(0x00e6, 0x01);
		VL6180X_WriteByte(0x00e7, 0x03);
		VL6180X_WriteByte(0x00f5, 0x02);
		VL6180X_WriteByte(0x00d9, 0x05);
		VL6180X_WriteByte(0x00db, 0xce);
		VL6180X_WriteByte(0x00dc, 0x03);
		VL6180X_WriteByte(0x00dd, 0xf8);
		VL6180X_WriteByte(0x009f, 0x00);
		VL6180X_WriteByte(0x00a3, 0x3c);
		VL6180X_WriteByte(0x00b7, 0x00);
		VL6180X_WriteByte(0x00bb, 0x3c);
		VL6180X_WriteByte(0x00b2, 0x09);
		VL6180X_WriteByte(0x00ca, 0x09);
		VL6180X_WriteByte(0x0198, 0x01);
		VL6180X_WriteByte(0x01b0, 0x17);
		VL6180X_WriteByte(0x01ad, 0x00);
		VL6180X_WriteByte(0x00ff, 0x05);
		VL6180X_WriteByte(0x0100, 0x05);
		VL6180X_WriteByte(0x0199, 0x05);
		VL6180X_WriteByte(0x01a6, 0x1b);
		VL6180X_WriteByte(0x01ac, 0x3e);
		VL6180X_WriteByte(0x01a7, 0x1f);
		VL6180X_WriteByte(0x0030, 0x00);
		
		// Recommended : Public registers - See data sheet for more detail
		VL6180X_WriteByte(0x0011, 0x10);       // Enables polling for 'New Sample ready'
									// when measurement completes
		VL6180X_WriteByte(0x010a, 0x30);       // Set the averaging sample period
									// (compromise between lower noise and
									// increased execution time)
		VL6180X_WriteByte(0x003f, 0x46);       // Sets the light and dark gain (upper
									// nibble). Dark gain should not be
									// changed. !�ϰ��ֽ�Ҫд��0x4	Ĭ��������1.0
		VL6180X_WriteByte(0x0031, 0xFF);       // sets the # of range measurements after
									// which auto calibration of system is
									// performed
		VL6180X_WriteByte(0x0040, 0x63);       // Set ALS integration time to 100ms
		VL6180X_WriteByte(0x002e, 0x01);       // perform a single temperature calibration
									// of the ranging sensor

		// Optional: Public registers - See data sheet for more detail
		VL6180X_WriteByte(0x001b, 0x09);    //�������	��ѯģʽ
									// period to 100ms	ÿ��10ms->0-10ms
		VL6180X_WriteByte(0x003e, 0x31);      //��������	ALSģʽ
									// to 500ms		
		VL6180X_WriteByte(0x0014, 0x24);       // Configures interrupt on 'New Sample
									// Ready threshold event'
		return 0;
	}
	else return 1;
}

//��λ����
uint8_t VL6180X_Read_Range(void)
{
	uint8_t range = 0;
	//��������
	while(!(VL6180X_ReadByte(VL6180X_REG_RESULT_RANGE_STATUS) & 0x01));
	VL6180X_WriteByte(VL6180X_REG_SYSRANGE_START,0x01);	//���δ���ģʽ
	//�ȴ�������������ֵ�¼�(New Sample Ready threshold event)
	while(!(VL6180X_ReadByte(VL6180X_REG_RESULT_INTERRUPT_STATUS_GPIO) & 0x04));
	range = VL6180X_ReadByte(VL6180X_REG_RESULT_RANGE_VAL);
	//��ȡ�����ݣ�����ж�λ
	VL6180X_WriteByte(VL6180X_REG_SYSTEM_INTERRUPT_CLEAR,0x07);	//0111b ����������жϱ�־
	return range;
}


//VL6180X��ȡ16λ����
uint8_t VL6180X_Read_HalfWold(uint16_t reg)
{
	uint16_t res;
	uint8_t Index_H = (uint8_t)(reg >> 8);
	uint8_t Index_L = (uint8_t)(reg & 0xff);
    I2C_Start(VL6180_I2C); 
	I2C_Send_Byte(VL6180_I2C,(VL6180X_DEFAULT_I2C_ADDR<<1)|0);//����������ַ+д����	
	I2C_Wait_Ack(VL6180_I2C);		//�ȴ�Ӧ�� 
    I2C_Send_Byte(VL6180_I2C,Index_H);	//д�Ĵ�����ַ
    I2C_Wait_Ack(VL6180_I2C);		//�ȴ�Ӧ��
	I2C_Send_Byte(VL6180_I2C,Index_L);	//д�Ĵ�����ַ
	I2C_Wait_Ack(VL6180_I2C);	
	
    I2C_Start(VL6180_I2C);
	I2C_Send_Byte(VL6180_I2C,(VL6180X_DEFAULT_I2C_ADDR<<1)|1);//����������ַ+������	
    I2C_Wait_Ack(VL6180_I2C);		//�ȴ�Ӧ�� 
	res = I2C_Read_Byte(VL6180_I2C,1);//��ȡ����,����ACK 
	res <<= 8;
	res |= I2C_Read_Byte(VL6180_I2C,0);//��ȡ����,����nACK 
    I2C_Stop(VL6180_I2C);			//����һ��ֹͣ���� 
	return res;
}


float VL6180X_Read_Lux(uint8_t Gain)
{
	float lux;
	uint8_t reg;
	reg = VL6180X_ReadByte(VL6180X_REG_SYSTEM_INTERRUPT_CONFIG);
	reg &= ~0x38;		//[5:3]��0
	reg |= (0x4<<3);	//����ת��New sample ready	����ת��
	
	VL6180X_WriteByte(VL6180X_REG_SYSALS_INTEGRATION_PERIOD_HI,0);
	VL6180X_WriteByte(VL6180X_REG_SYSALS_INTEGRATION_PERIOD_LO,100);	//101ms
	if (Gain > VL6180X_ALS_GAIN_40)
	{
		Gain = VL6180X_ALS_GAIN_40;
	}
	VL6180X_WriteByte(VL6180X_REG_SYSALS_ANALOGUE_GAIN, 0x40 | Gain);
	VL6180X_WriteByte(VL6180X_REG_SYSALS_START, 0x1);	//����ģʽ
	// New Sample Ready threshold event ����������
	while (4 != ((VL6180X_ReadByte(VL6180X_REG_RESULT_INTERRUPT_STATUS_GPIO) >> 3) & 0x7));
	
	lux = VL6180X_Read_HalfWold(VL6180X_REG_RESULT_ALS_VAL);
	VL6180X_WriteByte(VL6180X_REG_SYSTEM_INTERRUPT_CLEAR,0x07);	//0111b ����������жϱ�־
	//���������㷨
	lux *= 0.32f; // calibrated count/lux
	switch(Gain) { 
	case VL6180X_ALS_GAIN_1: 
	break;
	case VL6180X_ALS_GAIN_1_25: 
	lux /= 1.25f;
	break;
	case VL6180X_ALS_GAIN_1_67: 
	lux /= 1.76f;
	break;
	case VL6180X_ALS_GAIN_2_5: 
	lux /= 2.5f;
	break;
	case VL6180X_ALS_GAIN_5: 
	lux /= 5;
	break;
	case VL6180X_ALS_GAIN_10: 
	lux /= 10;
	break;
	case VL6180X_ALS_GAIN_20: 
	lux /= 20;
	break;
	case VL6180X_ALS_GAIN_40: 
	lux /= 20;
	break;
	}
	lux *= 100;
	lux /= 100; // integration time in ms
	return lux;
}

