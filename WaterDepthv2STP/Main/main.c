#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "myiic.h"
#include "MS5837.h"

u8 ENABLE_SEND = 0;

u16 u_temp = 0;
u16 u_pres = 0;
u16 u_depth = 0;
    
void TIM3_Int_Init(u16 arr,u16 psc);

static inline void UART_Trans(u16 data)
{
    USART_SendData(USART1, data);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
}

int main(void)
{
    ENABLE_SEND = 0;
    float temp=0.0;
    float pres=0.0;
    float depth=0.0;
    
	delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();
    uart_init(921600);
    TIM3_Int_Init(500,2000);
    IIC_Init();
    MS5837_Init();
    
    while(1)
    {
        
        MS5837_getData(&temp, &pres);
        LED=0;
        MS5837_ReadDepth_filtered(&depth);
        u_temp = (u16)temp;
        u_pres = (u16)pres;
        u_depth = depth*1000;
        
        if(KEY_IN == 0) //debug mode
        {
            printf("%d,%d,%d\r\n", u_temp, u_pres, u_depth);
        }
        else if(ENABLE_SEND == 1)
        {
            UART_Trans((u8)((u_temp&0xFF00)>>8));
            UART_Trans((u8)u_temp&0x00FF);
            UART_Trans((u8)((u_pres&0xFF00)>>8));
            UART_Trans((u8)u_pres&0x00FF);
            UART_Trans((u8)((u_depth&0xFF00)>>8));
            UART_Trans((u8)u_depth&0x00FF);
            ENABLE_SEND = 0;
        }
    }
}

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        LED=1;
        ENABLE_SEND = 1;
	}
}
