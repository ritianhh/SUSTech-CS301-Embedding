#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h" 
//
//ʵ�飨�壩�ⲿ�ж�ʵ��   
//
 int main(void)
 {	
 
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
 	EXTIX_Init();		//�ⲿ�жϳ�ʼ��
  LED0=0;				//����LED
	while(1)
	{	    
		printf("OK\n");	
		delay_ms(3000);	  
	} 
}


