#include "u_flash.h"
#include "stm32g0xx.h"
#include "stdio.h"
#include "string.h"

//stm32g030��16������  һ������2K         P6F6  32k/2 ����



void STMFLASH_Write(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite)	;
uint8_t dev_sn_code[16];
uint8_t STM32G0_GetFlashSector(uint32_t addr){
	if (addr >= FLASH_SECTOR14_START && addr <= FLASH_SECTOR14_END){
		return 14;
	}else if (addr >= FLASH_SECTOR15_START && addr <= FLASH_SECTOR15_END){
		return 15;
	}
	return 16;
}
//void Flash_Write_Num_Word(uint32_t WriteAddr, uint32_t * pBuffer, uint32_t NumToWrite )
//{
//	uint32_t PAGEError = 0;
//	FLASH_EraseInitTypeDef EraseInitStruct;
//	if(WriteAddr<FLASH_BASE||(WriteAddr>=(FLASH_BASE+U_PAGE_NUM*U_FLASH_PAGE_SIZE)))
//	{	
//		printf("�Ƿ���ַ\r\n");
//	  return;//�Ƿ���ַ
//	}
//		HAL_FLASH_Unlock(); 
//	 //  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
//	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP  | FLASH_FLAG_WRPERR);   //����֮ǰ�����־����һ��Ҫ�������
//	
//	   EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;	// ˢ����ʽ
//	  EraseInitStruct.Page = STM32G0_GetFlashSector(WriteAddr);	// ��ʼ��ַ
//     EraseInitStruct.NbPages = 1;
//	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
//      {
//        // ���ˢ������
//        printf("\r\n FLASH Erase Fail\r\n");
//        printf("Fail Code:%d\r\n",HAL_FLASH_GetError());
//        printf("Fail Page:%d\r\n",PAGEError);
//      }
//				FLASH_WaitForLastOperation(FLASH_WAITETIME);            //�ȴ��ϴβ������
//			for(uint32_t i=0;i<NumToWrite;i++)
//			{
//				//8���ֽ�
//			if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, WriteAddr+i*8, *(uint64_t *)(pBuffer+i*2)) == HAL_OK){
//          printf("write data 0x%x OK\n", *(pBuffer+i));
//				
//				
//      }
//      else{
//        printf("failed!!!\n");
//      }
//		  }
//      HAL_FLASH_Lock();
//}
/**
  * ��������: ��ȡָ����ַ�İ���(16λ����)
  * �������: faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
  * �� �� ֵ: ����ֵ:��Ӧ����.
  * ˵    ������
  */
uint32_t STMFLASH_ReadWord ( uint32_t faddr )
{
	return *(__IO uint32_t*)faddr; 
}
/**
  * ��������: ��ָ����ַ��ʼ����ָ�����ȵ�����
  * �������: ReadAddr:��ʼ��ַ
  *           pBuffer:����ָ��
  *           NumToRead:����(16λ)��
  * �� �� ֵ: ��
  * ˵    ������
  */
void Flash_Read_Word( uint32_t ReadAddr, uint32_t *pBuffer, uint32_t NumToRead )   	
{
	uint16_t i;
	
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//��ȡ4���ֽ�.
		ReadAddr+=4;//ƫ��4���ֽ�.	
		  //  printf("read data 0x%x OK\n", *(pBuffer+i));
	}
}
uint32_t ab[2]={0x12345678,0x66778899};
uint32_t ac[2];
void test_flash()
{
	 memcpy(dev_sn_code, SN_CODE, 16);
	STMFLASH_Write(SN_ADDR_FLASH, (uint32_t *)dev_sn_code, 2);
	
	Flash_Read_Word( SN_ADDR_FLASH, ac,2 ) ;
	  printf("read data 0x%x OK\n", *ac);
	 printf("read data 0x%x OK\n", *(ac+1));
}
#include "bsp_usart1.h"
extern uint32_t factory;
extern BSP_UASRT1_TYPE   BSP_UASRT1_ST;
void Init_Dev_Param()
{
	
	Flash_Read_Word( SN_ADDR_FLASH,(uint32_t *)dev_sn_code,3) ;

	Flash_Read_Word( FACTORY_ADDR_FLASH, (uint32_t *)&factory,1 ) ;	
	   while(factory!=1)
		 {
			   process_usart_data();			 
		 }

	
//			send_string_to_eth(sn_code,12);
//		 	HAL_Delay(1000);
//		 send_string_to_eth(sn_code,12);
//		  HAL_Delay(1000);
		
		  send_string_to_eth(dev_sn_code,12);
		 	HAL_Delay(1000);
		  send_string_to_eth((uint8_t*)SQQ_VERSION,sizeof(SQQ_VERSION));
		 		 for(uint16_t j=0;j<12;j++)
		 {
			 BSP_UASRT1_ST.tem_RX_pData[j]=dev_sn_code[j];
			//  BSP_UASRT1_ST.tem_RX_pData[i]=0x55;
		 }
		 
		  
	
}


//#define FLASH_SECTOR14_START                      0x08007000
//#define FLASH_SECTOR14_END                        0x080077FF
//#define FLASH_SECTOR15_START                      0x08007800
//#define FLASH_SECTOR15_END                        0x08007FFF
 

 

 
 
 
 
///*************************************************************
//** Function name:       STM32G0_GetFlashSector
//** Descriptions:        ��ȡG030оƬ��addr���ڵ�����
//** Input parameters:    None
//** Output parameters:   None
//** Returned value:      None
//** Remarks:             None
//*************************************************************/
//uint8_t STM32G0_GetFlashSector(uint32_t addr){
//	if (addr >= FLASH_SECTOR14_START && addr <= FLASH_SECTOR14_END){
//		return 14;
//	}else if (addr >= FLASH_SECTOR15_START && addr <= FLASH_SECTOR15_END){
//		return 15;
//	}
//	return 16;
//}
// 
///*************************************************************
//** Function name:       STMFLASH_Write
//** Descriptions:        STM32д����
//** Input parameters:    pBuffer ������Ҫ�洢��ָ�롢 NumToWrite ��Ҫд����ֽ�����/8(��������д��˫�ִ�С 8�ֽ�)
//** Output parameters:   None
//** Returned value:      None
//** Remarks:             None
//*************************************************************/
void STMFLASH_Write(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite)	
{ 
	FLASH_EraseInitTypeDef FlashEraseInit;
	HAL_StatusTypeDef FlashStatus = HAL_OK;
	uint32_t PageError = 0;
	uint32_t addrx = 0;
	uint32_t endaddr = 0;	
	if(WriteAddr < FLASH_DATA_ADDR_MIN || WriteAddr % 4)  return;	//�Ƿ���ַ ��ֹд��ķ�Χ
	HAL_FLASH_Unlock();                         //����	
	addrx = WriteAddr;				            //д�����ʼ��ַ
	endaddr = WriteAddr + NumToWrite * 8;	    //д��Ľ�����ַ
	if(addrx < FLASH_DATA_ADDR_MAX)
	{
		while(addrx < endaddr)		        //ɨ��һ���ϰ�.(�Է�FFFFFFFF�ĵط�,�Ȳ���)
		{   
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)	//�з�0XFFFFFFFF�ĵط�,Ҫ�����������
			{   
				FlashEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;    //�������ͣ�ҳ���� 
				FlashEraseInit.Page = STM32G0_GetFlashSector(addrx);      //����ҳ��ʼ����
				FlashEraseInit.NbPages = 1;                          //һ��ֻ����һҳ
			///	SEGGER_RTT_printf(0,"Flash Erase page is %d\r\n",FlashEraseInit.Page);
				if(HAL_FLASHEx_Erase(&FlashEraseInit, &PageError) != HAL_OK) 
				{
			//		SEGGER_RTT_printf(0,"Flash Erase err\r\n");
					break;      //����������	
				}
				FLASH_WaitForLastOperation(FLASH_WAITETIME);            //�ȴ��ϴβ������
			}else {
				addrx += 4;
			}
		}
	}
	FlashStatus = FLASH_WaitForLastOperation(FLASH_WAITETIME);        //�ȴ��ϴβ������
	if(FlashStatus == HAL_OK)
	{
		while(WriteAddr < endaddr)									//д����
		{
			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, WriteAddr, *(uint64_t*)pBuffer) != HAL_OK)//д������
			{
				break;												//д���쳣
			}
			WriteAddr += 8;     //��ַ��8
			pBuffer += 2;       //buff����������32λ��,�������2 ����8���ֽ�
		}  
		
	}
	FLASH_WaitForLastOperation(FLASH_WAITETIME);        //�ȴ��ϴβ������
	HAL_FLASH_Lock();           									//����
}