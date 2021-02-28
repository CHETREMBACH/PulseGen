/**
  ******************************************************************************
  * @file    hooks.c 
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

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "hooks.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

static volatile unsigned int stackOverflow;
static volatile unsigned int mallocFailed;

/**
  * @brief  Функция вызывается при переполнении стека FreeRTOS, 
  * @param  TaskHandle_t xTask - хэндл задачи
  * @param  char * pcTaskName  - имя текущей задачи
  * @retval None
  */
void vApplicationStackOverflowHook( TaskHandle_t xTask,	char * pcTaskName)
{
	stackOverflow++;
	printf("StackOverflowHook: %s\n", pcTaskName);
        while(1);
}

/**
  * @brief  Функция вызывается при отсутствии памяти в куче FreeRTOS, 
  *    
  * @param  None
  * @retval None
  */
void vApplicationMallocFailedHook(void)
{
	mallocFailed++;
	printf("MallocFailedHook: %d\n", xPortGetFreeHeapSize());
        while(1);
}

/**
  * @brief  Функция настройки и запуска таймера, 
  *         который используется для подсчета времени работы задач FreeRTOS 
  *         
  *         Время тика таймера должено быть, по крайней мере в 10 раз меньше
  *         частоты тика FreeRTOS
  *    
  * @param  None
  * @retval None
  */
void vConfigureTimerForRunTimeStats(void)
{
	TIM_TimeBaseInitTypeDef timer;
	
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
        TIM_TimeBaseStructInit(&timer);
	    timer.TIM_Prescaler = 2500 - 1;
        timer.TIM_Period = 0xFFFF;
        TIM_TimeBaseInit(TIM4, &timer);
	
        TIM_Cmd(TIM4, ENABLE);
}

unsigned long hi_cntr = 0;
unsigned long old_cnt = 0;
unsigned long new_cnt = 0;

/**
  * @brief  Функция возращает значения счетчика таймера, 
  *         который используется для подсчета времени работы задач FreeRTOS 
  *         для 16 разрядных счетчиков
  *         
  * @param  None
  * @retval unsigned long значение счетчика таймера
  */
unsigned long ulGetRuntimeCounterValue(void)
{
	new_cnt = (unsigned long)(TIM4->CNT);
	if (old_cnt > new_cnt)  hi_cntr += 0x00010000;
	old_cnt = new_cnt;
	return hi_cntr + new_cnt;		
}
/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/