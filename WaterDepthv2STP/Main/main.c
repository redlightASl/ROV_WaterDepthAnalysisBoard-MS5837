#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "myiic.h"
#include "MS5837.h"

int main(void)
{
    float temp=0.0;
    float pres=0.0;
    float depth=0.0;
    
	delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();
    uart_init(921600);
    IIC_Init();
    MS5837_Init();
    
    while(1)
    {
        LED=1;
        MS5837_getData(&temp, &pres);
        LED=0;
        MS5837_ReadDepth_filtered(&depth);
//        MS5837_ReadDepth(&depth);
//        printf("%f, %f\r\n",temp,pres);
        printf("%f\r\n",depth);
        
    }
}
