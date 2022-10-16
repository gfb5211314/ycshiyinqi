#ifndef    __ETH_RING_COM_H__
#define    __ETH_RING_COM_H__

#include "main.h"

#define  eth_ring_len  50

typedef struct
{
    uint8_t  RX_flag;        //IDLE receive flag
    uint16_t RX_Size;          //receive length
	  uint16_t count;
    uint16_t dev_pData_len;          //receive length
    uint8_t  RX_pData[eth_ring_len];
    uint8_t  dev_pData[eth_ring_len];
    uint8_t  TX_pData[eth_ring_len];
}ETH_ring_TYPE;
extern ETH_ring_TYPE eth_ring;
#define   Manufacturer_ID_1        0xfe 
#define   Manufacturer_ID_2        0xef

#define   Manufacturer_ID_3        0xef 
#define   Manufacturer_ID_4        0xfe


#define   device_type              0x06 //拾音器

#define  Access_request_function    0x01      //请求入网
	
#define	 State_net_function         0x02    //入网状态上报
	
#define	 Equipment_report_function  0x05  //设备号上报

#define  Equipment_run_state_function        0x08  //设备状态上报
 
#define  alarm_report_function       0x12     //报警上报

#define  Distance_away_p_function      0x13    //远程消警
 
#define  Manual_away_p_function      0x14   //手动消警


uint8_t eth_ring_com_pack(uint8_t *rxpbuf,uint8_t *dev_buf,uint8_t function,uint8_t *eth_data,uint16_t pbuf_len,uint8_t *proctukey);
#endif
