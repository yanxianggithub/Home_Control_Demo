#include "usart3.h"
#include "gizwits_product.h"
   

//串口3中断服务函数
void USART3_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收到数据
	{	 
		res =USART_ReceiveData(USART3);		 
		gizPutData(&res, 1);//数据写入到缓冲区
	}  				 											 
}   

 
void usart3_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	                      
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);              

 	USART_DeInit(USART3); 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	                          
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                       
   

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                      
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                         
	
	USART_InitStructure.USART_BaudRate = bound;                                 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;              
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                
	USART_InitStructure.USART_Parity = USART_Parity_No;                    
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	   
  
	USART_Init(USART3, &USART_InitStructure);   
  

	USART_Cmd(USART3, ENABLE);                
	
	//使能接收中断
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
	NVIC_Init(&NVIC_InitStructure);	
	
}
