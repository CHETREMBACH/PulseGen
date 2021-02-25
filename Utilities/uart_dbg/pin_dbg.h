/**
  ******************************************************************************
  * @file    pin_dbg.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PIN_DBG_H
#define __PIN_DBG_H

#ifdef __cplusplus
extern "C" {
#endif

#if  (DBG_PIN_ENABLE == 1)

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"	

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define T1_CLK     	         RCC_APB2Periph_GPIOC
#define T1_PIN               GPIO_Pin_13
#define T1_PORT              GPIOC  
#define T1_HI                GPIO_SetBits(T1_PORT,T1_PIN)
#define T1_LO                GPIO_ResetBits(T1_PORT,T1_PIN)
	
#define T2_CLK             	 RCC_APB2Periph_GPIOC
#define T2_PIN               GPIO_Pin_13
#define T2_PORT              GPIOC  
#define T2_HI                GPIO_SetBits(T2_PORT,T2_PIN)
#define T2_LO                GPIO_ResetBits(T2_PORT,T2_PIN)
	
/**
  * @brief  Инициализация GPIO для отладки.
  * @param  None
  * @retval None
  */
void DBG_PIN_Setup(void);

#endif /*  (DBG_PIN_ENABLE == 1) */

#ifdef __cplusplus
}
#endif

#endif /* __PIN_DBG_H */

/******************* (C) COPYRIGHT 2020 OneTiOne  *****END OF FILE****/
