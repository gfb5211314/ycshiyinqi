#include  "shiyinqi_hal.h"
#include  "usart.h"
#include  "stdio.h"

uint8_t aRxBuffer[3];
uint32_t data_len_arx=0;
uint8_t flag_arx=0;
/*****************************************************************
                       *����HAL*
******************************************************************/
//����DMA���տ����ж�
void  shiqinqi_DMA_START()
{
     HAL_UART_Receive_DMA(&shiyinqi_usart,(uint8_t *)shiyinqi_st.RX_pData, 1);  //����������
//    __HAL_UART_ENABLE_IT(&shiyinqi_usart, UART_IT_IDLE);
}

void  send_data_usart1(uint8_t ch);
//

//�������տ����ж�
void  shiyinqi_UsartReceive_IDLE()
{
    uint32_t temp=0;
    if((__HAL_UART_GET_FLAG(&shiyinqi_usart,UART_FLAG_IDLE) != RESET))
    {
			  
        __HAL_UART_CLEAR_IDLEFLAG(&shiyinqi_usart);
        HAL_UART_DMAStop(&shiyinqi_usart);
        temp = shiyinqi_usart.hdmarx->Instance->CNDTR;//	
          shiyinqi_st.RX_Size = data_len_shiyin - temp;
        shiyinqi_st.RX_flag=1;
        HAL_UART_Receive_DMA(&shiyinqi_usart,(uint8_t *)shiyinqi_st.RX_pData, data_len_shiyin);
     
    }
}

void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
// shiyinqi_UsartReceive_IDLE();
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
// HAL_UART_Receive_DMA(&shiyinqi_usart,(uint8_t *)shiyinqi_st.RX_pData, 800);
  /* USER CODE END USART1_IRQn 1 */
}
//���ͺ���
void  send_data_usart1(uint8_t ch)
{
	while((USART2->ISR&0x40)==0);
	USART2->TDR=(uint8_t)ch;	
}
 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart==&shiyinqi_usart)
  {
//		    printf("122");
//	HAL_UART_Transmit(&shiyinqi_usart,shiyinqi_st.RX_pData,1,0);
//	      	HAL_UART_Transmit(&huart2,shiyinqi_st.RX_pData,1,0);
////   HAL_UART_Transmit(&huart2,shiyinqi_st.RX_pData,1,0);
//		 HAL_UART_Receive_DMA(&shiyinqi_usart,(uint8_t *)shiyinqi_st.RX_pData, 1);
	
//		   HAL_UART_Receive_DMA(&shiyinqi_usart,(uint8_t *)shiyinqi_st.RX_pData, 700);
//		 shiyinqi_st.RX_flag=1;
		
		 HAL_UART_Receive_DMA(&shiyinqi_usart,(uint8_t *)shiyinqi_st.RX_pData, 1);
		   memcpy ( shiyinqi_st.tem_RX_pData, shiyinqi_st.RX_pData,1 );
			HAL_UART_Transmit_DMA(&huart1,shiyinqi_st.tem_RX_pData,1);
  }
 
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	 
	if(huart==&huart1)
		{
			 
//	  printf("nihao");
//	  HAL_UART_Receive_DMA(&shiyinqi_usart,(uint8_t *)shiyinqi_st.RX_pData, data_len_shiyin);
		}
	
}
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
//{
//   
//}
void usart_it_on()
{
 HAL_UART_Receive_DMA(&shiyinqi_usart,(uint8_t *)shiyinqi_st.RX_pData, 1);
}