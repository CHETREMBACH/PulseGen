/**
  ******************************************************************************
  * @file    hooks.h 
  * @author  Trembach D.N.
  * @version V1.0.0
  * @date    22-11-2015
  * @brief   Файл вспомогательных функций портирования FreeRTOS.
  *
  *
  ******************************************************************************
  * @attention
  *
  *
  * <h2><center>&copy; (C) COPYRIGHT ONE TO ONE</center></h2>
  ******************************************************************************
  */
 
#ifndef HOOKS_H_
#define HOOKS_H_

/**
  * @brief  Функция настройки и запуска таймера, 
  *         который используется для подсчета времени работы задач FreeRTOS 
  *         
  * @param  None
  * @retval None
  */
void vConfigureTimerForRunTimeStats(void);

/**
  * @brief  Функция возращает значения счетчика таймера, 
  *         который используется для подсчета времени работы задач FreeRTOS 
  *         
  * @param  None
  * @retval unsigned long значение счетчика таймера
  */
unsigned long ulGetRuntimeCounterValue(void);

#endif /* HOOKS_H_ */
/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/
