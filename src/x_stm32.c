

#include "x_stm32.h"

void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif 


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
}


void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);

    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1 = HCLK/4 */
    RCC_PCLK1Config(RCC_HCLK_Div4);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {}

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {}
  }
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
  						  RCC_APB2Periph_GPIOB |
  						  RCC_APB2Periph_GPIOC |
						  RCC_APB2Periph_GPIOD , 
						  ENABLE);
}

void GPIOx_Init(GPIO_TypeDef* GPIOx , u16 GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed , GPIOMode_TypeDef GPIO_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;

	GPIO_Init(GPIOx,&GPIO_InitStructure);
}


void delay_init()	 
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=72000/8000;	//为系统时钟的1/8  

	fac_ms=(u16)fac_us*1000;//非ucos下,代表每个ms需要的systick时钟数   

}

void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	//SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数	 
	SysTick_CounterCmd(SysTick_Counter_Enable);			 //开始倒数
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	//SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick_CounterCmd(SysTick_Counter_Disable);	 //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}

void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	//SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数  
	SysTick_CounterCmd(SysTick_Counter_Enable);
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	//SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick_CounterCmd(SysTick_Counter_Disable);
	SysTick->VAL =0X00;       //清空计数器	  	    
} 









