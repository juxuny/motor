#ifndef _X_STM32_
#define _X_STM32_

#include "stm32f10x_lib.h"

#define GPIO_PIN_0 GPIO_Pin_0
#define GPIO_PIN_1 GPIO_Pin_1
#define GPIO_PIN_2 GPIO_Pin_2
#define GPIO_PIN_3 GPIO_Pin_3
#define GPIO_PIN_4 GPIO_Pin_4
#define GPIO_PIN_5 GPIO_Pin_5
#define GPIO_PIN_6 GPIO_Pin_6
#define GPIO_PIN_7 GPIO_Pin_7
#define GPIO_PIN_8 GPIO_Pin_8
#define GPIO_PIN_9 GPIO_Pin_9
#define GPIO_PIN_10 GPIO_Pin_10
#define GPIO_PIN_11 GPIO_Pin_11
#define GPIO_PIN_12 GPIO_Pin_12
#define GPIO_PIN_13 GPIO_Pin_13
#define GPIO_PIN_14 GPIO_Pin_14
#define GPIO_PIN_15 GPIO_Pin_15
#define GPIO_PIN_ALL GPIO_Pin_All





static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数


void NVIC_Configuration(void);
void RCC_Configuration(void);
void GPIOx_Init(GPIO_TypeDef* GPIOx , u16 GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed , GPIOMode_TypeDef GPIO_Mode);
void delay_init(void);
void delay_us(u32 nus);
void delay_ms(u16 nms);





#endif


