#ifndef __SHIYINQI_HAL_H__
#define __SHIYINQI_HAL_H__

#include "main.h"
#include "usart.h"

#define  shiyinqi_usart        huart1
#define  data_len_shiyin 800

typedef struct
{
    uint8_t  RX_flag;        //IDLE receive flag
    uint16_t RX_Size;          //receive length
	  uint16_t count;
    uint16_t tem_RX_Size;          //receive length
    uint8_t  RX_pData[data_len_shiyin];
    uint8_t  tem_RX_pData[data_len_shiyin];
    uint8_t  TX_pData[50];
}shiyinqi_TYPE;

extern shiyinqi_TYPE  shiyinqi_st;
#endif

