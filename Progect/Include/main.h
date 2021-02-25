/**
  ******************************************************************************
  * @file    main.h
  * @author  Trembach D.N.
  * @version V1.0.0
  * @date    25-02-2021
  * @brief   Файл стартовой функции проекта.
  *
  *
  ******************************************************************************
  * @attention
  *
  *
  * <h2><center>&copy; COPYRIGHT 2021 ONE TO ONE</center></h2>
  ******************************************************************************
  */

#ifndef _MAIN_H
#define _MAIN_H

/* Includes ------------------------------------------------------------------*/   
/* FreeRTOS includes. */
#include "stm32f10x.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
    
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/ 
/*-------------------------------- Tasks Priority ----------------------------*/
   
/* For configMAX_PRIORITIES =7 */   
typedef enum {
	TreadPrioIdle = configMAX_PRIORITIES - 7,
	           ///< priority: idle (lowest)
	TreadPrioLow = configMAX_PRIORITIES - 6, 
	          ///< priority: low
	TreadPrioBelowNormal = configMAX_PRIORITIES - 5, 
	          ///< priority: below normal
	TreadPrioNormal = configMAX_PRIORITIES - 4, 
	          ///< priority: normal (default)
	TreadPrioAboveNormal = configMAX_PRIORITIES - 3, 
	          ///< priority: above normal
	TreadPrioHigh = configMAX_PRIORITIES - 2,
	           ///< priority: high
	TreadPrioRealtime = configMAX_PRIORITIES - 1,
	           ///< priority: realtime (highest)
} thread_prio_t;   

#endif