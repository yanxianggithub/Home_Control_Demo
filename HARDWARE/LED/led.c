#include "led.h"


void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_3;			
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOB, &GPIO_InitStructure);				
 GPIO_ResetBits(GPIOB,GPIO_Pin_0);					
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;		
 GPIO_Init(GPIOA, &GPIO_InitStructure);		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
 GPIO_Init(GPIOC, &GPIO_InitStructure);		
}
 
