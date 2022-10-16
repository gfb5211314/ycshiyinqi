#ifndef  __U_FLASH_H_
#define  __U_FLASH_H_
#include "main.h"

//#define PAGE_SIZE                128
//#define PAGE_NUM                 512
//#define ADDR_FLASH_PAGE_505      0X08000000 + 128*504   //
//#define ADDR_FLASH_PAGE_506      0X08000000 + 128*505   //
//#define ADDR_FLASH_PAGE_507      0X08000000 + 128*506   //
//#define ADDR_FLASH_PAGE_508      0X08000000 + 128*507   //
//#define ADDR_FLASH_PAGE_509      0X08000000 + 128*508   //
//#define ADDR_FLASH_PAGE_510      0X08000000 + 128*509   //
//#define ADDR_FLASH_PAGE_511      0X08000000 + 128*510   //
//#define ADDR_FLASH_PAGE_512      0X08000000 + 128*511   //���һҳ

#define U_FLASH_PAGE_SIZE                                           (2*1024)
#define U_PAGE_NUM                                             16  //16������

#define FLASH_BASE_ADDR                                         0X08000000
#define SN_ADDR_FLASH                                          (FLASH_BASE_ADDR+(U_PAGE_NUM-1)*U_FLASH_PAGE_SIZE)   //15
#define FLASH_WAITETIME                                         1000

//����ģʽ
#define FACTORY_ADDR_FLASH                                      (FLASH_BASE_ADDR+(U_PAGE_NUM-2)*U_FLASH_PAGE_SIZE) //14

//stm32g030��16������  һ������2K         P6F6  32k/2 ����
#define FLASH_SECTOR14_START                      0x08007000
#define FLASH_SECTOR14_END                        0x080077FF
#define FLASH_SECTOR15_START                      0x08007800
#define FLASH_SECTOR15_END                        0x08007FFF
// 
#define FLASH_DATA_ADDR_MIN                         FLASH_SECTOR14_START
#define FLASH_DATA_ADDR_MAX                         FLASH_SECTOR15_END
// 
//#define FLASH_DATA_ADDR_BASE                        FLASH_DATA_ADDR_MIN
//#define CALIBRATION_L_LR_VALUE_ADDR                 FLASH_DATA_ADDR_BASE+0
//#define CALIBRATION_L_UD_VALUE_ADDR                 FLASH_DATA_ADDR_BASE+12
//#define CALIBRATION_R_LR_VALUE_ADDR                 FLASH_DATA_ADDR_BASE+24
//#define CALIBRATION_R_UD_VALUE_ADDR                 FLASH_DATA_ADDR_BASE+36
//#define FLASH_WAITETIME                             1000


#define SN_CODE                  "ycsyq0112345"    //

extern void STMFLASH_Write(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite)	;
extern void Flash_Write_Num_Word(uint32_t WriteAddr, uint32_t * pBuffer, uint32_t NumToWrite );

/**
  * ��������: ��ȡָ����ַ�İ���(16λ����)
  * �������: faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
  * �� �� ֵ: ����ֵ:��Ӧ����.
  * ˵    ������
  */
extern uint32_t STMFLASH_ReadWord ( uint32_t faddr );

/**
  * ��������: ��ָ����ַ��ʼ����ָ�����ȵ�����
  * �������: ReadAddr:��ʼ��ַ
  *           pBuffer:����ָ��
  *           NumToRead:����(16λ)��
  * �� �� ֵ: ��
  * ˵    ������
  */
extern void Flash_Read_Word( uint32_t ReadAddr, uint32_t *pBuffer, uint32_t NumToRead )  ; 	

#endif