#include "debug_usart_hal.h"
#include "stdio.h"
//�ض����ӡ����

int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

