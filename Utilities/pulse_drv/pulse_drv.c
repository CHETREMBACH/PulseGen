/**
  ******************************************************************************
  * @file    pulse_drv.c
  * @author  Trembach D.N.
  * @version V1.0.0
  * @date    27-02-2021
  * @brief   Файл содержит функции настройки и контроля формирования импульсов таймером
  ******************************************************************************
  * @attention
  * 
  * 
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "pulse_drv.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "pin_dbg.h"

uint16_t StartDelay1 = 300 * 25;
uint16_t TimePulse1 = 750 * 25 - 4;

uint16_t StartDelay2 = 300 * 25 + 750 * 25 - 4;
uint16_t TimePulse2 = 750 * 25 - 4;

int16_t  DeltaDelay = 0;

/**
  * @brief  This function handles TIM1 Break and TIM9 interrupts request.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler(void)
{
	T1_HI;
	/* TIM9_CH1 toggling with frequency = 366.2 Hz */
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		DeltaDelay = DeltaDelay + 50;
		
		if (DeltaDelay > 500)
		{
			DeltaDelay = -500;
		}
		
		TIM_SetCompare3(TIM1, StartDelay2 + TimePulse2 + DeltaDelay);
		TIM_SetCompare4(TIM1, StartDelay2 + DeltaDelay);		
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
	T1_LO;	
}

/**
  * @brief  Configures GPIO / Timer.
  * @param  None 
  * @retval None
  */
void Pulse_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	
	/* Enable TIM1 clock  */	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	
	
	/* Configure TIM1 pins */
	/* Enable GPIO clock  */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
	/* GPIOA Configuration:TIM1 Channel1,2,3 and 4 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
	/* GPIOA Configuration:TIM1 NChannel1,2 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	/* Enable the TIM1 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
	/* Time Base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 56250-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* Channel 1 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = StartDelay1 + TimePulse1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	
	/* Channel 2 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = StartDelay1 - 504;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	/* Channel 3 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = StartDelay2 + TimePulse2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);

	/* Channel 4 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = StartDelay2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	TIM_BDTRStructInit(&TIM_BDTRInitStructure);
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
	TIM_BDTRInitStructure.TIM_DeadTime = 255;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
		
	/* TIM IT enable */
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
	/* TIM1 Main Output Enable */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	/* TIM1 counter enable */
	TIM_Cmd(TIM1, ENABLE);

}
/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/