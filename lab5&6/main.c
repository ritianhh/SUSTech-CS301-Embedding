#include "led.h"
#include "delay.h"
#include "sys.h"
#include "pwm.h"
#include "usart.h"
#include "exti.h"
#include "key.h"

extern volatile int flag;
int main(void)
{
	int a;
	GPIO_InitTypeDef  GPIO_InitStructure;
	u16 led0pwmval = 0;
	u8 dir = 1;
	delay_init();	    	 //???????	  
	LED_Init();		  	//????LED???????
	TIM1_PWM_Init(899, 0);//????PWM??=72000/(899+1)=80Khz 
	uart_init(9600);
	EXTIX_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	while (1) {
		if (flag) {
			delay_ms(10);
			if (dir)
				led0pwmval++;
			else
				led0pwmval--;
			if (led0pwmval > 300)
				dir = 0;
			if (led0pwmval == 0) {
				dir = 1;
				//printf("The light is off.\n");
				delay_ms(1000);
			}
			TIM_SetCompare1(TIM1, led0pwmval);
		}
		else {
      GPIO_Init(GPIOA, &GPIO_InitStructure);
			for(a = 0; a < 10; ++a){
			  LED0=!LED0;
			  delay_ms(100);
		  }
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, DISABLE);	
		  TIM1_PWM_Init(899, 0);
		  uart_init(9600);
			TIM1->CCER =1;
			TIM1->CR2=0;
			flag = 1;
		}
	}
}
