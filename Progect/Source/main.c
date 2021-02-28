/**
  ******************************************************************************
  * @file    main.c
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "board.h"
#include "printf_dbg.h"
#include "cmd_process.h"
#include "pin_dbg.h"
#include "indic_drv.h"
#include "pulse_drv.h"
#include <stdio.h>

volatile const char __version__[] = "PULSE_BOARD";    
volatile const char __date__[] = __DATE__;
volatile const char __time__[] = __TIME__;
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
 * @brief  Start Thread 
 * @param  None
 * @retval None
 */
void system_thread(void *arg)
{ 
	//Подключение интерфейса отладки
	DBG_Hardware_Setup();
	//Подключения для отладки GPIO 
	DBG_PIN_Setup();	

	// Информационная шапка программы
	printf("______________________________________________\r\n");
	printf("\r\n");
	printf("   %s \r\n", __version__);
	printf("   DATA: %s \r\n", __date__);
	printf("   TIME: %s \r\n", __time__);
	printf("   CPU FREQ = %.9lu Hz \r\n", SystemCoreClock);  
	printf("______________________________________________\r\n"); 	
	
	//Инициализация задачи диагностического терминала 
	xTaskCreate(terminal_task, (const char*)"CmdTrmnl", configMINIMAL_STACK_SIZE * 5, NULL, TreadPrioNormal, NULL);	
	
	/* Запуск задачи контроля платы */
	xTaskCreate(board_task, "BOARD", configMINIMAL_STACK_SIZE, NULL, TreadPrioNormal, NULL);
  
	/* Configures Indic.*/
	Indic_Init();	
	
	/* Configures GPIO / Timer.*/
	Pulse_Init();
	
	// Initialise the xLastWakeTime variable with the current time.
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 1000;  	
	xLastWakeTime = xTaskGetTickCount();  
	for (;;)
	{
		// Wait for the next cycle.
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}


int main(void)
{
	/* Обновление переменных тактирование по состоянию регистров тактирования    */
	SystemCoreClockUpdate();
	/* Настройка групп приоритеов все 4 бита для управления приоритетом, 0 бит для подприоритета */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
	/* Init thread */
	xTaskCreate(system_thread, (const char*)"SysTask", configMINIMAL_STACK_SIZE, NULL, TreadPrioNormal, NULL);
	/* Start scheduler */
	vTaskStartScheduler();
	/* We should never get here as control is now taken by the scheduler */
	NVIC_SystemReset();  
	/* Зацикливание программы */
	while (1) ;
}

#ifdef USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	 /* Infinite loop */
	while (1)
	{}
}
#endif
/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/
