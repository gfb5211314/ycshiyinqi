#include "app_task.h"
#include "ether_hal.h"
 shiyinqi_TYPE  shiyinqi_st;
 
//
void app_task_run()
{
			
			if(shiyinqi_st.RX_flag==1)
		{
			    
			
//        HAL_UART_Transmit(&huart2,shiyinqi_st.RX_pData,shiyinqi_st.RX_Size, 0xffffffff);
////	
//		 	HAL_UART_Transmit_DMA(&huart2,shiyinqi_st.RX_pData,1);
//			
//					 	shiyinqi_st.RX_flag=0;
////					 
////					
////			
//				HAL_UART_Transmit_DMA(&huart1,shiyinqi_st.RX_pData,1);
//		   	HAL_UART_Receive_DMA(&shiyinqi_usart,shiyinqi_st.RX_pData,800);
//		  printf("122");
		}
//	
//  if(HAL_OK==	HAL_UART_Receive_DMA(&shiyinqi_usart,(uint8_t *)shiyinqi_st.RX_pData, 800))
//	{
//		
//		 HAL_UART_Transmit_DMA(&huart2,shiyinqi_st.RX_pData,800);
//		
//	};  //不能启动打开

}
