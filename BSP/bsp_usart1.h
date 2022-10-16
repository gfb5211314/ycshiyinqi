#ifndef    BSP_USART1_H
#define    BSP_USART1_H

#include "usart.h"
#include "stdio.h"
#define   u1_tx(a)     HAL_UART_Transmit(&huart1, (uint8_t *)&a, 1, 0xffff)
#define   bsp_usart1      huart1

#define  data_len  1000

typedef struct
{
    uint8_t  RX_flag;        //IDLE receive flag
    uint16_t RX_Size;          //receive length
	  uint16_t count;
    uint16_t tem_RX_Size;          //receive length
    uint8_t  RX_pData[data_len];
    uint8_t  tem_RX_pData[data_len];
//    uint8_t  TX_pData[data_len];
}BSP_UASRT1_TYPE;

extern BSP_UASRT1_TYPE   BSP_UASRT1_ST;
void  usart1_DMA_START(void);
void data_send(void);
void  usa1_UsartReceive_IDLE(void);
#endif
