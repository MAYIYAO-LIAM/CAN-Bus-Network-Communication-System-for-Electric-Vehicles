#include "stm32f10x.h"
#include "can.h"
#include "led.h"



void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}
/*�����ܽų�ʼ��*/
void KeyInit(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ������ʱ��
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ������ʱ��

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 ;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //����������10MHz
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //����������10MHz
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
        GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*����Ƿ��а�������*/
void  GetKey(void)
{
        

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13))
        {
                Delay(1000000);//ȥ����//ȥ����
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)){ ; }//�ȴ������ͷ�                        
                        can_tx(0X55,0X77); 
                }
        }

        if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
        {
                 Delay(1000000);//ȥ����//ȥ����
                if(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
                {
                        while(Bit_RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)){ ; }//�ȴ������ͷ�                        
                        can_tx(0X99,0Xbb); 	
                }
        }       

      
}



int main(void)
{   
	SystemInit(); //����ϵͳʱ��Ϊ72M
	KeyInit();	  //�����ܽų�ʼ��
	LED_GPIO_Config();//LED�ܽų�ʼ��
	CAN_GPIO_Config();//CAN�ܽų�ʼ��
	CAN_NVIC_Configuration(); //CAN�жϳ�ʼ��   
	CAN_INIT();//CAN��ʼ��ģ��	
 	while(1)
    {
	 GetKey();	//����Ƿ��а�������
	   
  	}
}




