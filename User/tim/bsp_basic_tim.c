/**
  ******************************************************************************
  * @file    bsp_basic_tim.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2017-12-5
  * @brief   ������ʱ����ʱ����
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "./tim/bsp_basic_tim.h"

TIM_HandleTypeDef TimHandle;
uint32_t uwPrescalerValue = 0;
/*
 * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
 * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
 * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
 *-----------------------------------------------------------------------------
 * TIM_Prescaler         ����
 * TIM_CounterMode			 TIMx,x[6,7]û�У��������У�������ʱ����
 * TIM_Period            ����
 * TIM_ClockDivision     TIMx,x[6,7]û�У���������(������ʱ��)
 * TIM_RepetitionCounter TIMx,x[1,8]����(�߼���ʱ��)
 *-----------------------------------------------------------------------------
 */
void TIM_Config(void)
{
  /* Compute the prescaler value to have TIM6 counter clock equal to 10 KHz */
  uwPrescalerValue = (uint32_t) (SystemCoreClock / 10000) - 1;

	TimHandle.Instance = BASIC_TIM;
	/* �ۼ� TIM_Period�������һ�����»����ж�*/		
	//����ʱ����0������9999����Ϊ10000�Σ�Ϊһ����ʱ����
	TimHandle.Init.Period = 10000-1;
	
	//��ʱ��ʱ��ԴTIMxCLK = 2 * PCLK1
	//				PCLK1 = HCLK / 4 
	//				=> TIMxCLK=HCLK/2=SystemCoreClock/2=84MHz
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=10000Hz
	TimHandle.Init.Prescaler = uwPrescalerValue;	
	TimHandle.Init.ClockDivision = 0;
  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	
  if(HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /*##-2- Start the TIM Base generation in interrupt mode ####################*/
  /* Start Channel1 */
  if(HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }	
}

/*********************************************END OF FILE**********************/
