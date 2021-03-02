/**
  ******************************************************************************
  * @file    eeprom_drv.h
  * @author  Trembach D.N.
  * @version V1.0.0
  * @date    02-03-2021
  * @brief   Файл содержит функции поддержки емуляции eeprom
  ******************************************************************************
  * @attention
  * 
  * 
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_DRV_H
#define __EEPROM_DRV_H

  /* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
  
/**
  * @brief  Инициализация емулятора eeprom.
  * @param  None 
  * @retval None
  */
void Em_EEPROM_Init(void);

#endif /* __EEPROM_DRV_H */
/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/

