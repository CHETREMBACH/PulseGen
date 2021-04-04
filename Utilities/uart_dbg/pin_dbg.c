/**
  ******************************************************************************
  * @file    pin_dbg.c
  * @version V1.0.0
  * @date    07-09-2020
  * @brief   Инициализация драйвера GPIO для отладки
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2020 OneTiOne </center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "pin_dbg.h"

#if  (DBG_PIN_ENABLE == 1)
/**
  * @brief  Инициализация GPIO для отладки.
  * @param  None
  * @retval None
  */
void DBG_PIN_Setup(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
#ifdef T1_PORT  
	RCC_APB2PeriphClockCmd(T1_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = T1_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(T1_PORT, &GPIO_InitStructure);
	
	T1_LO;
#endif
	
#ifdef T2_PORT
	RCC_APB2PeriphClockCmd(T2_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = T2_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(T2_PORT, &GPIO_InitStructure);
	T2_LO;
#endif
	
}

#endif  /* (DBG_PIN_ENABLE == 1) */
/******************* (C) COPYRIGHT 2020 OneTiOne  *****END OF FILE****/
