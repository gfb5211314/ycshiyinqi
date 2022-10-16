#include   "eth_ring_com.h"
#include   "ether_hal.h"

ETH_ring_TYPE eth_ring;
uint8_t   dev_buffer[4]={0}; //设备号
uint8_t product_key[30]={0,0,0,0,0,0,0,1};//一定要初始化，要不写读会发生问题
//
uint8_t eth_ring_com_pack(uint8_t *rxpbuf,uint8_t *dev_buf,uint8_t function,uint8_t *eth_data,uint16_t pbuf_len,uint8_t *proctukey)
{
	  uint16_t index=0;
	 	     for(uint16_t i=0;i<8;i++)
	{
	 rxpbuf[index++]=proctukey[i]; //productkey
	}
	 rxpbuf[index++]=Manufacturer_ID_1; //厂家识别码
	 rxpbuf[index++]=Manufacturer_ID_2;
	 rxpbuf[index++]=dev_buf[0];    //设备号
   rxpbuf[index++]=dev_buf[1];
	 rxpbuf[index++]=device_type;  //设备类型
	 rxpbuf[index++]=function;  //功能码
	 for(uint16_t i=0;i<pbuf_len;i++)
	{		
		 rxpbuf[index++]=eth_data[i];  //功能码		
	}	
	 rxpbuf[index++]=Manufacturer_ID_3; //厂家识别码
	 rxpbuf[index++]=Manufacturer_ID_4;
	   return index;
}
