#include "u_flash.h"
#include "stm32g0xx.h"
#include "stdio.h"
#include "string.h"

//stm32g030有16个扇区  一个扇区2K         P6F6  32k/2 扇区



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
//		printf("非法地址\r\n");
//	  return;//非法地址
//	}
//		HAL_FLASH_Unlock(); 
//	 //  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
//	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP  | FLASH_FLAG_WRPERR);   //擦除之前先清标志，（一定要加这个）
//	
//	   EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;	// 刷除方式
//	  EraseInitStruct.Page = STM32G0_GetFlashSector(WriteAddr);	// 起始地址
//     EraseInitStruct.NbPages = 1;
//	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
//      {
//        // 如果刷除错误
//        printf("\r\n FLASH Erase Fail\r\n");
//        printf("Fail Code:%d\r\n",HAL_FLASH_GetError());
//        printf("Fail Page:%d\r\n",PAGEError);
//      }
//				FLASH_WaitForLastOperation(FLASH_WAITETIME);            //等待上次操作完成
//			for(uint32_t i=0;i<NumToWrite;i++)
//			{
//				//8个字节
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
  * 函数功能: 读取指定地址的半字(16位数据)
  * 输入参数: faddr:读地址(此地址必须为2的倍数!!)
  * 返 回 值: 返回值:对应数据.
  * 说    明：无
  */
uint32_t STMFLASH_ReadWord ( uint32_t faddr )
{
	return *(__IO uint32_t*)faddr; 
}
/**
  * 函数功能: 从指定地址开始读出指定长度的数据
  * 输入参数: ReadAddr:起始地址
  *           pBuffer:数据指针
  *           NumToRead:半字(16位)数
  * 返 回 值: 无
  * 说    明：无
  */
void Flash_Read_Word( uint32_t ReadAddr, uint32_t *pBuffer, uint32_t NumToRead )   	
{
	uint16_t i;
	
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//读取4个字节.
		ReadAddr+=4;//偏移4个字节.	
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
//** Descriptions:        获取G030芯片中addr所在的扇区
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
//** Descriptions:        STM32写操作
//** Input parameters:    pBuffer 传入需要存储的指针、 NumToWrite 需要写入的字节数量/8(单次最少写入双字大小 8字节)
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
	if(WriteAddr < FLASH_DATA_ADDR_MIN || WriteAddr % 4)  return;	//非法地址 禁止写入的范围
	HAL_FLASH_Unlock();                         //解锁	
	addrx = WriteAddr;				            //写入的起始地址
	endaddr = WriteAddr + NumToWrite * 8;	    //写入的结束地址
	if(addrx < FLASH_DATA_ADDR_MAX)
	{
		while(addrx < endaddr)		        //扫清一切障碍.(对非FFFFFFFF的地方,先擦除)
		{   
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)	//有非0XFFFFFFFF的地方,要擦除这个扇区
			{   
				FlashEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;    //擦除类型，页擦除 
				FlashEraseInit.Page = STM32G0_GetFlashSector(addrx);      //从哪页开始擦除
				FlashEraseInit.NbPages = 1;                          //一次只擦除一页
			///	SEGGER_RTT_printf(0,"Flash Erase page is %d\r\n",FlashEraseInit.Page);
				if(HAL_FLASHEx_Erase(&FlashEraseInit, &PageError) != HAL_OK) 
				{
			//		SEGGER_RTT_printf(0,"Flash Erase err\r\n");
					break;      //发生错误了	
				}
				FLASH_WaitForLastOperation(FLASH_WAITETIME);            //等待上次操作完成
			}else {
				addrx += 4;
			}
		}
	}
	FlashStatus = FLASH_WaitForLastOperation(FLASH_WAITETIME);        //等待上次操作完成
	if(FlashStatus == HAL_OK)
	{
		while(WriteAddr < endaddr)									//写数据
		{
			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, WriteAddr, *(uint64_t*)pBuffer) != HAL_OK)//写入数据
			{
				break;												//写入异常
			}
			WriteAddr += 8;     //地址加8
			pBuffer += 2;       //buff传进来的是32位的,所以这里＋2 便是8个字节
		}  
		
	}
	FLASH_WaitForLastOperation(FLASH_WAITETIME);        //等待上次操作完成
	HAL_FLASH_Lock();           									//上锁
}