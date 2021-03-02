/**
  ******************************************************************************
  * @file    eeprom_drv.c
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

/* Includes ------------------------------------------------------------------*/
#include "eeprom_drv.h"
#include "eeprom_emul.h"
#include "printf_dbg.h"

uint32_t a_VarDataTab[NB_OF_VARIABLES] = { 0 };

/**
  * @brief  Инициализация емулятора eeprom.
  * @param  None 
  * @retval None
  */
void Em_EEPROM_Init(void)
{
	EE_Status ee_status = EE_OK;
	uint32_t VarValue = 0;
	uint32_t Index = 1;
	__IO uint32_t ErasingOnGoing = 0;	
	
	/* Unlock the Flash Program Erase controller */
	FLASH_Unlock();	
	
	ee_status = EE_Init(EE_FORCED_ERASE);
	if (ee_status != EE_OK) {
		printf(" Eeprom init error!!! ");
		while (1);
	}
	
	uint32_t temp;
	
	
	//ee_status = EE_WriteVariable32bits(0x5501, 0xA1234567);
	//ee_status = EE_WriteVariable32bits(0x5501, 0xA1234567);
	//ee_status = EE_WriteVariable32bits(0x5501, 0xA1234567);
	
	EE_ReadVariable32bits(0x5501, &temp);
	EE_ReadVariable32bits(0x5501, &temp);
	EE_ReadVariable32bits(0x5501, &temp);


	FLASH_Lock();
}
/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/