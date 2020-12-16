#include "stm32f4xx_conf.h"
#include <string.h>
#include <stdio.h>
#include "uart.h"
/*
 * TIM5: Uart (debug purpose)
 * Frequency: 8Hz
 */
void timer5_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	/* (42MHz -> interface clock) * 2 / (84000 -> period * 125 -> prescaler) = 8Hz */
	TIM_TimeBaseInitTypeDef TimeBaseInitStruct = {
		.TIM_Period = 84000 - 1,
		.TIM_Prescaler = 125 - 1,
		.TIM_CounterMode = TIM_CounterMode_Up
	};
	TIM_TimeBaseInit(TIM5, &TimeBaseInitStruct);

	NVIC_InitTypeDef NVIC_InitStruct = {
		.NVIC_IRQChannel = TIM5_IRQn,
		.NVIC_IRQChannelPreemptionPriority = 2,
		.NVIC_IRQChannelCmd = ENABLE
	};
	NVIC_Init(&NVIC_InitStruct);

	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM5, ENABLE);
}

void TIM5_IRQHandler(void){
	static int cnt = 0;
    	char str[1000] = {};
    	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET){
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		sprintf(str, "hello");
		uart3_puts(str);
    	}
}

