

#include "main.h"

int main()
{
	RCC_Configuration();
	NVIC_Configuration();
	delay_init();
	USART1_Init();
//	GPIOx_Init(GPIOB,GPIO_PIN_0 , GPIO_Speed_50MHz , GPIO_Mode_Out_PP);
	TIM3_PWM_Conguration();

	delay_ms(1000);
	TIM_SetCompare3(TIM3,1000);
	delay_ms(5000);
	TIM_SetCompare3(TIM3,1200);
	while(1)
	{
	}
}
