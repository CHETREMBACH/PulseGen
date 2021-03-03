/**
  ******************************************************************************
  * @file    EEPROM_Emul/Porting/STM32G0/flash_interface.c
  * @author  MCD Application Team
  * @brief   This file provides all the EEPROM emulation flash interface functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "eeprom_emul.h"
#include "flash_interface.h"
#include "CRC16.h"

/* Delay definition */   
#define EraseTimeout          ((uint32_t)0x000B0000)
#define ProgramTimeout        ((uint32_t)0x00002000)


/** @addtogroup EEPROM_Emulation
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @addtogroup EEPROM_Private_Functions
  * @{
  */

/**
  * @brief  Write a double word at the given address in Flash
  * @param  Address Where to write
  * @param  Data What to write
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE_WRITE_ERROR: if an error occurs
  */
EE_Status FI_WriteDoubleWord(uint32_t Address, uint64_t Data)
{
	uint32_t *Dat = (uint32_t*)&Data; 
	
	if (FLASH_ProgramWord(Address, Dat[0]) == FLASH_COMPLETE)
	{
		if (FLASH_ProgramWord(Address + 4, Dat[1]) == FLASH_COMPLETE)
		{
			return EE_OK; 
		}
	}
	return EE_WRITE_ERROR;
}

/**
  * @brief  Erase a page in polling mode
  * @param  Page Page number
  * @param  NbPages Number of pages to erase
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE error code: if an error occurs
  */
EE_Status FI_PageErase(uint32_t Page, uint16_t NbPages)
{
	EE_Status status = EE_OK;
	
	for (uint32_t cntic = 0; cntic < NbPages; cntic++)	
	{
		if (FLASH_ErasePage((Page + cntic) * FLASH_PAGE_SIZE) != FLASH_COMPLETE) 
		{
			return EE_ERASE_ERROR;
		}
	}
	return EE_OK;
}

/**
  * @brief  Erase a page with interrupt enabled
  * @param  Page Page number
  * @param  NbPages Number of pages to erase
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE error code: if an error occurs
  */
EE_Status FI_PageErase_IT(uint32_t Page, uint16_t NbPages)
{
	return EE_ERASE_ERROR;
}

/**
  * @brief  Flush the caches if needed to keep coherency when the flash content is modified
  */
void FI_CacheFlush()
{
  /* No flush needed. There is no D-Cache for the STM32G0x0 and STM32G0x1 products. */
  return;
}

#ifdef FLASH_BANK_2
/**
  * @brief  Gets the bank of a given address
  * @param  Address Address of the FLASH Memory
  * @retval Bank_Number The bank of a given address
  */
static uint32_t GetBankNumber(uint32_t Address)
{
  uint32_t bank = 0U;

  if (OB_USER_DUALBANK_SWAP_DISABLE)
  {
    /* No Bank swap */
    if (Address < (FLASH_BASE + FLASH_BANK_SIZE))
    {
      bank = FLASH_BANK_1;
    }
    else
    {
      bank = FLASH_BANK_2;
    }
  }
  else
  {
    /* Bank swap */
    if (Address < (FLASH_BASE + FLASH_BANK_SIZE))
    {
      bank = FLASH_BANK_2;
    }
    else
    {
      bank = FLASH_BANK_1;
    }
  }

  return bank;
}
#endif

/**
  * @brief  Delete corrupted Flash address, can be called from NMI. No Timeout.
  * @param  Address Address of the FLASH Memory to delete
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE error code: if an error occurs
  */
EE_Status FI_DeleteCorruptedFlashAddress(uint32_t Address)
{
  EE_Status status = EE_OK;

  /* Set FLASH Programmation bit */
  SET_BIT(FLASH->CR, FLASH_CR_PG);

  /* Program double word of value 0 */
  *(__IO uint32_t*)(Address) = (uint32_t)0U;
  *(__IO uint32_t*)(Address+4U) = (uint32_t)0U;

  /* Wait programmation completion */
#if defined(FLASH_DBANK_SUPPORT)
  uint32_t bank = GetBankNumber(Address);
  if(bank == FLASH_BANK_1)
  {
    while(FLASH->SR & FLASH_SR_BSY1)
    {
    }
  }
  else
  {
    while(FLASH->SR & FLASH_SR_BSY2)
    {
    }
  }
#else  
	while (FLASH->SR & FLASH_SR_BSY)
  {
  }
#endif
  
  /* Check if error occured */
	if ((FLASH->SR & FLASH_SR_WRPRTERR) || (FLASH->SR & FLASH_SR_PGERR))
  {
    status = EE_DELETE_ERROR;
  }

  /* Check FLASH End of Operation flag  */
  if (FLASH->SR & FLASH_SR_EOP)
  {
    /* Clear FLASH End of Operation pending bit */
	IS_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP);
  }

  /* Clear FLASH Programmation bit */
  CLEAR_BIT(FLASH->CR, FLASH_CR_PG);

  return status;
}

/**
  * @brief  Check if the configuration is 128-bits bank or 2*64-bits bank
  * @param  None
  * @retval EE_Status
  *           - EE_OK: on success
  *           - EE error code: if an error occurs
  */
EE_Status FI_CheckBankConfig(void)
{
#if defined (FLASH_DBANK_SUPPORT)
  EE_Status status;

  /* Check the value of the DBANK user option byte */
  if (OB_USER_DUALBANK_ENABLE)
  {
    status = EE_OK;
  }
  else
  {
    status = EE_INVALID_BANK_CFG;
  }

  return status;
#else
  /* No feature 128-bits single bank, so always 64-bits dual bank */
  return EE_OK;
#endif
}

/* Структура подсчета CRC */
Table crc16_table;

/**
  * @brief  This function configures CRC Instance.
  * @param  None
  * @retval None
  */
void ConfigureCrc(void)
{
	/* Формируем таблицу для заданного алгоритма. */
	MakeTable(&CRC16_ARC, &crc16_table);
}

/**
  * @brief  This function performs CRC calculation on Data and Virtual Address.
  * @param  Data value of  the eeprom variable.
  * @param  VirtAddress address of the eeprom variable.
  * @retval 16-bit CRC value computed on Data and Virtual Address.
  */
uint16_t CalculateCrc(EE_DATA_TYPE Data, uint16_t VirtAddress)
{
	uint8_t mas[sizeof(EE_DATA_TYPE) + sizeof(uint16_t)];	

	*((uint16_t*)&(mas[0])) = VirtAddress;
	*((EE_DATA_TYPE*)&(mas[sizeof(uint16_t)])) = Data;
	
	return ChecksumCRC(mas, sizeof(mas), &crc16_table);
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
