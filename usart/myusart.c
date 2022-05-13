#include "myusart.h"
#include "usart.h"
extern DMA_HandleTypeDef hdma_usart1_rx;
extern int rx_flag;
extern uint16_t rx_length;
uint8_t rx_buf[buf_length];//����Ĵ��ڽ��ջ�����
uint8_t tx_buf[buf_length];//����Ĵ��ڷ��ͻ�����

void USART1_IRQHandler(void)//���ڿ���idle�ж�
{
	if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE) != RESET)
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);	//����жϱ�־λ	
		HAL_UART_DMAStop(&huart1);//ֹͣDMA����
		
		rx_length = buf_length - hdma_usart1_rx.Instance->NDTR;//���㳤��
		rx_flag = 1;//��ʾ���ܵ���
	}
	
}

void usart_init(void)
{
__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);//IDLE�ж�ʹ��
HAL_UART_Receive_DMA(&huart1, rx_buf, buf_length);//ʹ��DMA����
}