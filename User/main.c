#include"stm32f10x.h"

#define GPIO_M1_PLUS GPIO_Pin_13
#define GPIO_M1_MINUS GPIO_Pin_12
#define GPIO_M1 GPIOB

#define GPIO_M2_PLUS GPIO_Pin_8
#define GPIO_M2_MINUS GPIO_Pin_9
#define GPIO_M2 GPIOA

#define GPIO_M3_PLUS GPIO_Pin_11
#define GPIO_M3_MINUS GPIO_Pin_10
#define GPIO_M3 GPIOA

#define GPIO_M4_PLUS GPIO_Pin_5
#define GPIO_M4_MINUS GPIO_Pin_6
#define GPIO_M4 GPIOB

#define M1_PMW 90
#define M2_PMW 90
#define M3_PMW 90
#define M4_PMW 90


int Start = 0;


void Delay(uint16_t);
void GPIO_Config();
void NVIC_Config();
void EXTI_Config();


int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_Config();
	NVIC_Config();
	EXTI_Config();

	GPIO_WriteBit(GPIO_M1,GPIO_M1_MINUS,0);
	GPIO_WriteBit(GPIO_M2,GPIO_M2_MINUS,0);
	GPIO_WriteBit(GPIO_M3,GPIO_M3_MINUS,0);
	GPIO_WriteBit(GPIO_M4,GPIO_M4_MINUS,0);
	
	int timeValue = 100;
	while(1) {
		while(!Start) {
			
		}
		
		while (Start)
		{
			if(timeValue == 0) {
					timeValue = 100;
			}
			
			if(timeValue<M2_PMW) {
				GPIO_WriteBit(GPIO_M1,GPIO_M1_PLUS,1);
			} else {
				GPIO_WriteBit(GPIO_M1,GPIO_M1_PLUS,0);
			}
			
			if(timeValue<M2_PMW) {
				GPIO_WriteBit(GPIO_M2,GPIO_M2_PLUS,1);
			} else {
				GPIO_WriteBit(GPIO_M2,GPIO_M2_PLUS,0);
			}
			
			if(timeValue<M3_PMW) {
				GPIO_WriteBit(GPIO_M3,GPIO_M3_PLUS,1);
			} else {
				GPIO_WriteBit(GPIO_M3,GPIO_M3_PLUS,0);
			}
			
			if(timeValue<M4_PMW) {
				GPIO_WriteBit(GPIO_M4,GPIO_M4_PLUS,1);
			} else {
				GPIO_WriteBit(GPIO_M4,GPIO_M4_PLUS,0);
			}
			
			timeValue--;
			Delay(1);
		}
		
		GPIO_WriteBit(GPIO_M1,GPIO_M1_PLUS,0);
		GPIO_WriteBit(GPIO_M2,GPIO_M2_PLUS,0);
		GPIO_WriteBit(GPIO_M3,GPIO_M3_PLUS,0);
		GPIO_WriteBit(GPIO_M4,GPIO_M4_PLUS,0);
	}
}

void Delay(uint16_t c)
{
	uint16_t a;
	for(; c>0; c--)
		for(a=6000; a>0; a--);
}

void GPIO_Config() {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_M1_PLUS | GPIO_M1_MINUS;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_M1,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_M2_PLUS | GPIO_M2_MINUS;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_M2,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_M3_PLUS | GPIO_M3_MINUS;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_M3,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_M4_PLUS | GPIO_M4_MINUS;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_M4,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
}

void NVIC_Config() {
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI_Config() {
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStructure);
}

void EXTI0_IRQHandler(void)
{
	Start = !Start;
	Delay(1000);
  EXTI_ClearFlag(EXTI_Line0);
}


