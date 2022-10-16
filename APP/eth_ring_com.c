#include   "eth_ring_com.h"
#include   "ether_hal.h"

ETH_ring_TYPE eth_ring;
uint8_t   dev_buffer[4]={0}; //�豸��
uint8_t product_key[30]={0,0,0,0,0,0,0,1};//һ��Ҫ��ʼ����Ҫ��д���ᷢ������
//
uint8_t eth_ring_com_pack(uint8_t *rxpbuf,uint8_t *dev_buf,uint8_t function,uint8_t *eth_data,uint16_t pbuf_len,uint8_t *proctukey)
{
	  uint16_t index=0;
	 	     for(uint16_t i=0;i<8;i++)
	{
	 rxpbuf[index++]=proctukey[i]; //productkey
	}
	 rxpbuf[index++]=Manufacturer_ID_1; //����ʶ����
	 rxpbuf[index++]=Manufacturer_ID_2;
	 rxpbuf[index++]=dev_buf[0];    //�豸��
   rxpbuf[index++]=dev_buf[1];
	 rxpbuf[index++]=device_type;  //�豸����
	 rxpbuf[index++]=function;  //������
	 for(uint16_t i=0;i<pbuf_len;i++)
	{		
		 rxpbuf[index++]=eth_data[i];  //������		
	}	
	 rxpbuf[index++]=Manufacturer_ID_3; //����ʶ����
	 rxpbuf[index++]=Manufacturer_ID_4;
	   return index;
}
