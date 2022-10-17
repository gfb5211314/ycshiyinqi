#include "ether_hal.h"
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "usart.h"
#include   "eth_ring_com.h"
#include "u_flash.h"
typedef enum{
	 Access_request=0U,
	 Access_request_ack,
	 State_net,
	 State_net_ack,
	 Equipment_report,
	 Equipment_report_ack
}net_in_flow;

ETH_TYPE  ether_st;

uint8_t  local_eth_ip[40]="at+LANIp=192.168.1.160\r\n";
//uint8_t   local_eth_port[30]="at+NRPort0=6962\r\n";
uint8_t  Remote_eth_ip[40]="at+NDomain0=192.168.1.203\r\n";
uint8_t  Remote_eth_port[30]="at+NRPort0=6962\r\n";
extern uint8_t   dev_buffer[4];
extern uint8_t product_key[30];
uint8_t eth_ack_flag=0;
//ģ������
void ETH_Rst ( void )
{
	eth_RST_H;
	HAL_Delay(1000);
	 eth_RST_L;
	 HAL_Delay( 2000 ); 
	 eth_RST_H;
	HAL_Delay(2000);
	HAL_Delay(2000);
  HAL_Delay(2000);
	

}
//����1�ֽڵ�WIFIģ��
void send_byte_to_eth(uint8_t p)
{

    HAL_UART_Transmit(&eth_usart, (uint8_t*)&p,1, 0xffff);

}
//����һ���ַ���wifiģ��,���ܷ�������0
void eth_send_string(uint8_t *p) {

    while(*p!= '\0') {

        send_byte_to_eth(*p);
        p++;
    }
//	length=sizeof(data)/sizeof(data[0])
}

void send_string_to_eth(uint8_t *p,uint16_t plen)
{
	 HAL_UART_Transmit(&eth_usart, p,plen, 0xffff);	
}
//ֻ��������AT����ͣ��ַ�Ϊ0��û������! �����������㶼����
uint8_t atk_eth_send_cmd(uint8_t *cmd,uint8_t *ack,uint32_t waittime)
{
	     uint8_t sucess_state=0;
	    static  uint8_t reset_count=0; 
	    static  uint8_t comumtate=0; 
	    static  uint32_t eth_wait_tim_sta=0; 
	    static  uint32_t eth_wait_tim_end=0; 
	   switch(comumtate)
		 {
			 //���뷢��״̬
			 case 0 : 
				            eth_send_string(cmd);
//		  __HAL_UART_ENABLE_IT(&eth_usart, UART_IT_IDLE);
		  HAL_UART_Receive_DMA(&eth_usart,(uint8_t *)ether_st.RX_pData, 50);//�����������
			                    comumtate=1; 
			                    eth_wait_tim_sta=HAL_GetTick();
			              printf("wait_tim_sta=%d\r\n",eth_wait_tim_sta);
//			                   HAL_Delay(1000);
			                  reset_count++;
			                    if(reset_count>10)
													{
														printf("reset");
													HAL_NVIC_SystemReset();

														
													}
			               break;
			 //����ack״̬
			 case 1 :  if(ether_st.RX_flag==1)
			         {
			                       
				           printf("ack:%s\r\n",(uint8_t*)ether_st.RX_pData);
				           if(strstr((const char*)ether_st.RX_pData,(const char*)ack))
			            {
									  	reset_count=0;
								          ether_st.RX_flag=0;
								        	ether_st.RX_Size=0;
								           sucess_state=1;
								             comumtate=0;
                      memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));					        
				           }
									    ether_st.RX_flag=0;
								     ether_st.RX_Size=0;
                      memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));	
			         }
							 else
							 {
								         eth_wait_tim_end=HAL_GetTick();
//								       printf("wait_tim_end=%d\r\n",wait_tim_end);
								         if((eth_wait_tim_end-eth_wait_tim_sta)>waittime)
												 {
													 
													    comumtate=0;
													   
												 }								 
							 }
							 break;			 
		 }
              return sucess_state;
} 
/*****************************************************************
                       *����HAL*
******************************************************************/
//����DMA���տ����ж�
void  ETH_DMA_START()
{
   HAL_UART_Receive_DMA(&eth_usart,(uint8_t *)ether_st.RX_pData, 50);  //����������
    __HAL_UART_ENABLE_IT(&eth_usart, UART_IT_IDLE);
//		HAL_UART_Receive_IT(&wifi_usart,ESP8266_temp.RX_pData,1);		// ����ʹ�ܴ���2�����ж�
}
//�������տ����ж�
void  ETH_UsartReceive_IDLE()
{
    uint32_t temp=0;
    if((__HAL_UART_GET_FLAG(&eth_usart,UART_FLAG_IDLE) != RESET))
    {
			  
        __HAL_UART_CLEAR_IDLEFLAG(&eth_usart);
        HAL_UART_DMAStop(&eth_usart);
        temp = eth_usart.hdmarx->Instance->CNDTR;//	
          ether_st.RX_Size = data_len_eth - temp;
        ether_st.RX_flag=1;
				HAL_UART_Receive_DMA(&eth_usart,(uint8_t *)ether_st.RX_pData, data_len_eth);
    }
}

//
void USART2_IRQHandler(void)
{
    /* USER CODE BEGIN USART3_IRQn 0 */
      ETH_UsartReceive_IDLE();

    /* USER CODE END USART3_IRQn 0 */
      HAL_UART_IRQHandler(&eth_usart);
    /* USER CODE BEGIN USART3_IRQn 1 */
	
    /* USER CODE END USART3_IRQn 1 */
}
//
void eth_at_open()
{
		HAL_GPIO_WritePin(eth_at_port, eth_at_pin, GPIO_PIN_SET);
  	 HAL_Delay(1000);
	  HAL_GPIO_WritePin(eth_at_port, eth_at_pin, GPIO_PIN_RESET);
	   HAL_Delay(1000);
     HAL_Delay(1000);
	  HAL_GPIO_WritePin(eth_at_port, eth_at_pin, GPIO_PIN_SET);
	   HAL_Delay(1000);
	   HAL_Delay(1000);
	   HAL_Delay(1000);
	
}
//�ָ���������
void reset_ethdevinit()
{
    	HAL_GPIO_WritePin(eth_at_port, eth_at_pin, GPIO_PIN_SET);
  	 HAL_Delay(1000);
	  HAL_GPIO_WritePin(eth_at_port, eth_at_pin, GPIO_PIN_RESET);
	  HAL_Delay(1000);
		 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
		 HAL_Delay(1000);
	  HAL_GPIO_WritePin(eth_at_port, eth_at_pin, GPIO_PIN_SET);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	
	
	
}
//��ʼ��ģ��
uint8_t eth_init()
{

	   uint8_t sucess_stetc=0;
	   static uint8_t wifi_state_num=0;
	   switch(wifi_state_num)
		 {
	
			                  
			 case 0 : 
				                if(atk_eth_send_cmd((uint8_t *)"at+Netmode=0\r\n",(uint8_t *)"at+RNetmode=0",5000)==1)
											  {
												  wifi_state_num=1;											 
											  }
			   break;
			 case 1 :  
				                    printf("����ģʽ\r\n");
				 if(atk_eth_send_cmd((uint8_t *)"at+NProType0=2\r\n",(uint8_t *)"at+RNProType0",5000)==1)
											 {
												  wifi_state_num=2;											 
											 }  
			   break; 
											 
			 	 case 2 :       printf("DHCP�������ر�\r\n");
					 if(atk_eth_send_cmd((uint8_t *)"at+Dhcpd=0\r\n",(uint8_t *)"at+RDhcpd",5000)==1)
											 {
							  wifi_state_num=11;											 
											 }
			   break; 
											 ///////////////
		   case 11:       printf("����WAN��IP��ַ��ȡ��ʽ\r\n");
					 if(atk_eth_send_cmd((uint8_t *)"at+Dhcpc=1\r\n",(uint8_t *)"at+RDhcpc",5000)==1)
											 {
							  wifi_state_num=12;											 
											 }
			   break; 			
	   case 12:       printf("���ñ���IP��ַ\r\n");
					 if(atk_eth_send_cmd((uint8_t *)local_eth_ip,(uint8_t *)"at+RLANIp",5000)==1)
											 {
							  wifi_state_num=13;											 
											 }
			   break; 		
      case 13:       printf("���ñ������ص�ַ��ַ\r\n");
					 if(atk_eth_send_cmd((uint8_t *)"at+LANIpMask=255.255.255.0\r\n",(uint8_t *)"at+RLANIpMask",5000)==1)
											 {
							  wifi_state_num=3;											 
											 }
			   break; 												 
			  	 case 3 :        printf("123\r\n");
						 if(atk_eth_send_cmd((uint8_t *)Remote_eth_ip,(uint8_t *)"at+RNDomain0",5000)==1)
											 {
							  wifi_state_num=4;											 
											 }
    		   break; 
			  	 case 4 :    
						    printf("����IP��ַ\r\n");
						 if(atk_eth_send_cmd((uint8_t *)Remote_eth_port,(uint8_t *)"at+RNRPort0",5000)==1)
											 {
							     wifi_state_num=5;											 
											 }
			   break; 
			  	   case 5 :         if(atk_eth_send_cmd((uint8_t *)"at+NLPort0=8888\r\n",(uint8_t *)"at+RNLPort0",5000)==1)
											    {
							               wifi_state_num=6;											 
											    }
			   break; 
           case 6 :         if(atk_eth_send_cmd((uint8_t *)"at+Save=1\r\n",(uint8_t *)"at+RSave=1",5000)==1)
											    {
							               wifi_state_num=7;											 
											    }
			      break; 
						 case 7 :         if(atk_eth_send_cmd((uint8_t *)"at+Apply=1\r\n",(uint8_t *)"at+RApply=1",5000)==1)
											    {
							               wifi_state_num=8;											 
											    }
			      break; 
		       case 8 :         atk_eth_send_cmd((uint8_t *)"at+Reboot=1\r\n",(uint8_t *)"at+Reboot",1000);
											    
							               wifi_state_num=9;		
                               												
											       HAL_Delay(1000);
			      break; 									 
				
					 
			 	  	 case 9 :        
                           HAL_Delay(1000);
                           HAL_Delay(1000);
                           HAL_Delay(1000);
                           HAL_Delay(1000);	
                           HAL_Delay(1000);
                           HAL_Delay(1000);
                           HAL_Delay(1000);
                           HAL_Delay(1000);	
                           HAL_Delay(1000);
                           HAL_Delay(1000);
                           HAL_Delay(1000);
  HAL_Delay(1000);							 
sucess_stetc=1;								 
//							 printf("����͸���ɹ�\r\n");
//							 if(atk_eth_send_cmd((uint8_t *)"at+SAtMode=0\r\n",(uint8_t *)"at+RSAtMode",5000)==1)
//											    {
//													
//							               wifi_state_num=8;											 
//											    }
													
			   break; 		 
		 }
	     return  sucess_stetc;
}

//��������	
uint8_t  eth_ring_net_in()
{
	    uint8_t  net_ta=0;
   static net_in_flow  net_in=Access_request;
	 switch(net_in)
	 {		 
		   case Access_request : 
				              eth_ring.dev_pData_len=1;
			                eth_ring.dev_pData[0]=0x00;
					 eth_ring_com_pack(eth_ring.RX_pData,dev_buffer,Access_request_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key);
	  			 send_string_to_eth(eth_ring.RX_pData,eth_ring_com_pack(eth_ring.RX_pData,dev_buffer,Access_request_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key));
			                         eth_ack_flag=1;
			                         ether_st.RX_flag=0;
			                        net_in=Access_request_ack;
				 break;		 
		 	 case Access_request_ack : 
				 //�ط�
				              if(eth_ack_flag==2)
						 {
							  net_in=Access_request;
							 
						 }  
               if(ether_st.RX_flag==1)
							 {
								 printf("rev: fenpeidizhi");
								 
								 	 	for(uint16_t i=0;i<ether_st.RX_Size-8;i++)
									{
										
										ether_st.RX_pData[i]=ether_st.RX_pData[i+8];
											 printf("ether_st.RX_pData[%d]=%02x",i,	ether_st.RX_pData[i]);
									}
									
								 //��
								     if(ether_st.RX_pData[4]==device_type)
									   {
										     switch(ether_st.RX_pData[5])
												 {												
													  case 0x01 :                                         				       																
														   dev_buffer[0]=ether_st.RX_pData[6]; 
													     dev_buffer[1]=ether_st.RX_pData[7];
														 	 printf("get dev id %02x-%02x\r\n", dev_buffer[0],dev_buffer[1]);
								                    eth_ack_flag=0;
																		net_in =State_net; break;
												}
											}
										 			 ether_st.RX_flag=0;
												
											  memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));	
							  }
			 break;
		 	 case State_net :  
		                   eth_ring.dev_pData_len=1;
			                eth_ring.dev_pData[0]=0x01;
				 eth_ring_com_pack(eth_ring.RX_pData,dev_buffer,State_net_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key);
	 send_string_to_eth(eth_ring.RX_pData,eth_ring_com_pack(eth_ring.RX_pData,dev_buffer,State_net_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key));
			                         eth_ack_flag=1;
			                        net_in=State_net_ack;

			 break;
		 	 case State_net_ack :  
                       if(eth_ack_flag==2)
						 {
							  net_in=State_net;
							 
						 }  
               if(ether_st.RX_flag==1)
							 {
								  
								 	 	for(uint8_t i=0;i<ether_st.RX_Size-8;i++)
									{
										
										ether_st.RX_pData[i]=ether_st.RX_pData[i+8];
									}
								 //���߱���������Ϣ
								     if(ether_st.RX_pData[4]==device_type)
									   {
										     switch(ether_st.RX_pData[5])
												 {												
													  case State_net_function :  
                                     
																	 printf("get dev id\r\n");
														     
								                    eth_ack_flag=0;
																		net_in =Equipment_report;
														       break;
												}
											}
										 ether_st.RX_flag=0;
												
											  memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));	
								
							   }

			 break;
		 	 case Equipment_report :
				               eth_ring.dev_pData_len=2;
			                 eth_ring.dev_pData[0]=dev_buffer[0];
			                 eth_ring.dev_pData[1]=dev_buffer[1];
				 eth_ring_com_pack(eth_ring.RX_pData,dev_buffer,Equipment_report_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key);
	 send_string_to_eth(eth_ring.RX_pData,eth_ring_com_pack(eth_ring.RX_pData,dev_buffer,Equipment_report_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key));
			                         eth_ack_flag=1;
			                        net_in=Equipment_report_ack;
				         
				 break;
		 	 case Equipment_report_ack : 
                      if(eth_ack_flag==2)
						 {
							  net_in=Equipment_report;
							 
						 }  
               if(ether_st.RX_flag==1)
							 {
								  
								 	 	for(uint8_t i=0;i<ether_st.RX_Size-8;i++)
									{
										
										ether_st.RX_pData[i]=ether_st.RX_pData[i+8];
									}
								 //���߱���������Ϣ
								     if(ether_st.RX_pData[4]==device_type)
									   {
										     switch(ether_st.RX_pData[5])
												 {												
													  case Equipment_report_function :  
                                     
																	 printf("get dev id\r\n");
														        
				                      HAL_Delay(500);  //�ӳٲ�������
								                    eth_ack_flag=0;
//																		net_in =Equipment_report;
														        net_ta=1;
														       break;
												} 
											}
										 ether_st.RX_flag=0;
												
											  memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));									
							   }
			 break;
		 
		 
		 default :    break;		  
	 }
	  return net_ta;
}
extern uint8_t sn_code[16];
uint32_t factory=0;

void process_usart_data()
{
	
	if(ether_st.RX_flag==1)
	{
		 if(ether_st.RX_Size>100)
		 {
			 ether_st.RX_flag=0;
			 ether_st.RX_Size=0;
		 }
	//	send_string_to_eth(ether_st.RX_pData,ether_st.RX_Size);
		if(strncmp((char *)ether_st.RX_pData,"sn:",3)==0)
		{
			
			
			for(uint16_t i=0;i<12;i++)
			{
			  //printf("sn=%c",ether_st.RX_pData[i+3]) ; 
				sn_code[i]=ether_st.RX_pData[i+3];
			}		
        
    	 STMFLASH_Write(SN_ADDR_FLASH,   (uint32_t *)sn_code,3 );
	     Flash_Read_Word( SN_ADDR_FLASH, (uint32_t *)sn_code,3 ) ;
			
//			for(uint16_t i=0;i<12;i++)
//			{
//			  printf("sn=%c",sn_code[i]) ; 
//			
//			}	
			send_string_to_eth(sn_code,12);
		}
			else	if(strncmp((char *)ether_st.RX_pData, "exit factory",4)==0)
		{
			
           factory=1;			
			STMFLASH_Write(FACTORY_ADDR_FLASH,(uint32_t *) &factory, 1 );
  
		
			send_string_to_eth(ether_st.RX_pData,ether_st.RX_Size);
	
		}
		ether_st.RX_flag=0;
	  ether_st.RX_Size=0;
	}
}
