#ifndef __ETHER_HAL_H__
#define __ETHER_HAL_H__


#include "main.h"

#define data_len_eth   800
#define  eth_at_port     REF_CLK_GPIO_Port
#define  eth_at_pin       REF_CLK_Pin
#define  eth_usart        huart2
#define  eth_RST_L        HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET);
#define  eth_RST_H        HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET);
typedef struct
{
    uint8_t  RX_flag;        //IDLE receive flag
    uint16_t RX_Size;          //receive length
	  uint16_t count;
    uint16_t tem_RX_Size;          //receive length
    uint8_t  RX_pData[data_len_eth];
//    uint8_t  tem_RX_pData[data_len];
    uint8_t  TX_pData[data_len_eth];
}ETH_TYPE;

void send_string_to_eth(uint8_t *p,uint16_t plen);
uint8_t eth_init(void);
void ETH_Rst ( void );
 void  ETH_DMA_START(void);
void eth_at_open(void); 
uint8_t  eth_ring_net_in(void);
#endif
