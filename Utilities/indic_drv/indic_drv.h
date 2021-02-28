/**
  ******************************************************************************
  * @file    indic_drv.h
  * @author  Trembach D.N.
  * @version V1.0.0
  * @date    28-02-2021
  * @brief   Файл содержит функции задачи динамической индикации 
  ******************************************************************************
  * @attention
  * 
  * 
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INDIC_DRV_H
#define __INDIC_DRV_H

  /* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "main.h"

//#define LED_PIN                     GPIO_Pin_13
//#define LED_GPIO_PORT               GPIOC
//#define LED_GPIO_CLK                RCC_APB2Periph_GPIOC  
//#define LED_HI		                GPIO_SetBits(LED_GPIO_PORT,LED_PIN)
//#define LED_LO		                GPIO_ResetBits(LED_GPIO_PORT,LED_PIN)
  
/**
  * @brief  Configures Indic.
  * @param  None 
  * @retval None
  */
void Indic_Init(void);

#endif /* __INDIC_DRV_H */
/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/

