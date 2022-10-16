#include "bsp_usart1.h"

#include "stdio.h"
//打印函数
 BSP_UASRT1_TYPE   BSP_UASRT1_ST;

int fputc(int ch, FILE *f)
{
   u1_tx(ch);
  return ch;
}

//DMA开启
void  usart1_DMA_START()
{
   HAL_UART_Receive_DMA(&bsp_usart1,(uint8_t *)BSP_UASRT1_ST.RX_pData,50);  //??????
    __HAL_UART_ENABLE_IT(&bsp_usart1, UART_IT_IDLE); //打开串口空闲中断
//	  __HAL_DMA_DISABLE_IT(hdma, DMA_IT_HT);   //打开dma 半传输中断
//		HAL_UART_Receive_IT(&wifi_usart,ESP8266_temp.RX_pData,1);		// ??????2????
}
//空闲中断接收函数
void  usa1_UsartReceive_IDLE()
{
    uint32_t temp=0;
    if(__HAL_UART_GET_FLAG(&bsp_usart1,UART_FLAG_IDLE) != RESET)
    {
			  
        __HAL_UART_CLEAR_IDLEFLAG(&bsp_usart1);
        HAL_UART_DMAStop(&bsp_usart1);
        temp = bsp_usart1.hdmarx->Instance->CNDTR;//	
          BSP_UASRT1_ST.RX_Size = data_len - temp;
        BSP_UASRT1_ST.RX_flag=1;
       HAL_UART_Receive_DMA(&bsp_usart1,(uint8_t *)BSP_UASRT1_ST.RX_pData, data_len);
    }
}
extern DMA_HandleTypeDef hdma_usart1_rx;
//半传输中断接收函数
void  dma_half_interrupt()
{
//	 if(__HAL_DMA_GET_FLAG(&hdma_usart1_rx, DMA_FLAG_HT1) != RESET)
//	 {
//		  printf("123");
//		 
//	 }
//    uint32_t temp=0;
//    if((__HAL_UART_GET_FLAG(&bsp_usart1,UART_FLAG_IDLE) != RESET))
//    {
//			  
//        __HAL_UART_CLEAR_IDLEFLAG(&bsp_usart1);
//        HAL_UART_DMAStop(&bsp_usart1);
//        temp = bsp_usart1.hdmarx->Instance->CNDTR;//	
//          BSP_UASRT1_ST.RX_Size = data_len - temp;
//        BSP_UASRT1_ST.RX_flag=1;
//       HAL_UART_Receive_DMA(&bsp_usart1,(uint8_t *)BSP_UASRT1_ST.RX_pData, data_len);
//    }
}
 uint8_t count=0;
uint8_t count_flaf1=0;
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	
//	if(&bsp_usart1==huart)
//	{
////		 printf("123");
//		   count_flaf1=1;
////		count++;
////		printf("count=%d\r\n",count);
//	}
//	

//}
 uint8_t count1=0;

uint8_t count_flaf2=0;
uint8_t er8[1000]={'a','b'};
void enen1()
{
	
    
		count1++;
	   if(count1==1)
		 {
//			 HAL_UART_Transmit_DMA(&bsp_usart1,(uint8_t *)BSP_UASRT1_ST.RX_pData, 5);
				  for(uint16_t i=0;i<350;i++)
			 {
				er8[i]= BSP_UASRT1_ST.RX_pData[i];
			 }
//			 	 printf("1");
//			 count_flaf1=1;
	    
		 }
		  if(count1==2)
		 {
//			  HAL_UART_Transmit_DMA(&bsp_usart1,(uint8_t *)BSP_UASRT1_ST.RX_pData+5, 5);
//			  count_flaf2=1;
//			 printf("2");
			  for(uint16_t i=0;i<350;i++)
			 {
				er8[i+256]= BSP_UASRT1_ST.RX_pData[i+350];
			 }
//	   HAL_UART_Transmit_DMA(&bsp_usart1,(uint8_t *)er8, 5);    
			 count1=0;
		 }
//		printf("count1=%d\r\n",count1);

	

}
void data_send()
{
//	 if(count_flaf1==1)
//	 {
////		  for(uint8_t i=0;i<10;i++)
////		 {
////			 
////			 printf("%c",BSP_UASRT1_ST.RX_pData[i]);
////		 }
//	  HAL_UART_Transmit_DMA(&huart1,(uint8_t *)er8, 700);
////		 HAL_UART_Transmit(&huart1, (uint8_t *)er8, 640, 0xffffff);
//		   count_flaf1=0;
//	 }
	 if(BSP_UASRT1_ST.RX_flag==1)
	 {
//      BSP_UASRT1_ST.tem_RX_pData[0]=0xfe;
//		  BSP_UASRT1_ST.tem_RX_pData[1]=0xef;
//		 for(uint16_t i=0;i<BSP_UASRT1_ST.RX_Size;i++)
//		 {
//			 BSP_UASRT1_ST.tem_RX_pData[i+2]=BSP_UASRT1_ST.RX_pData[i];
//			 
//		 }
//	
//		 BSP_UASRT1_ST.tem_RX_pData[BSP_UASRT1_ST.RX_Size+2]=0xef;
//		 BSP_UASRT1_STa.tem_RX_pData[BSP_UASRT1_ST.RX_Size+3]=0xfe;
//	  HAL_UART_Transmit_DMA(&huart2,(uint8_t *)BSP_UASRT1_ST.tem_RX_pData,BSP_UASRT1_ST.RX_Size+2+2);	
		 HAL_UART_Transmit_DMA(&huart2,(uint8_t *)BSP_UASRT1_ST.RX_pData,BSP_UASRT1_ST.RX_Size);

		 BSP_UASRT1_ST.RX_flag=0;
		 
	 }
//	 if(count_flaf2==1)
//	 {
//		  HAL_UART_Transmit_DMA(&bsp_usart1,(uint8_t *)er8, 5);
//		 count_flaf2=0;
//	 }
	
}
