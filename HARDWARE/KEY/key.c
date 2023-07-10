#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 

void KEY_Init(void) 
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOB, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //连按		  
	if(key_up&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0||GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0||GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0||GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)return KEY0_PRES;
		else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0)return KEY1_PRES;
		else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0)return KEY2_PRES;
		else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)return WKUP_PRES;
	}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1&&GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1&&GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)key_up=1; 	    
 	return 0;// 无按键按下
}
