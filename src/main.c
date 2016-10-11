/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 6.0.0   2016-10-11

The MIT License (MIT)
Copyright (c) 2009-2016 Atollic AB

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************
*/

/* Includes */
#include <stddef.h>
#include "stm32l1xx.h"


/* Private typedef */
/* Private define  */
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

//initialization of the potenciometer
void adcInit(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;
 ADC_InitTypeDef ADC_InitStructure;
 /* Enable GPIO clock */
 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
 /* Configure ADCx Channel 2 as analog input */
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
 GPIO_Init(GPIOC, &GPIO_InitStructure);
/* Enable the HSI oscillator */
 RCC_HSICmd(ENABLE);
/* Check that HSI oscillator is ready */
 while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
 /* Enable ADC clock */
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
 /* Initialize ADC structure */
 ADC_StructInit(&ADC_InitStructure);
 /* ADC1 configuration */
 ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
 ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
 ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
 ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
 ADC_InitStructure.ADC_NbrOfConversion = 1;
 ADC_Init(ADC1, &ADC_InitStructure);
/* ADCx regular channel8 configuration */
 ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_16Cycles);
 /* Enable the ADC */
 ADC_Cmd(ADC1, ENABLE);
 /* Wait until the ADC1 is ready */
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
  {
  }
  /* Start ADC Software Conversion */
  ADC_SoftwareStartConv(ADC1);
}

 //inicialization of the LED
void initLED(void){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpioInitStruc;
	gpioInitStruc.GPIO_Mode = GPIO_Mode_OUT;
	gpioInitStruc.GPIO_OType = GPIO_OType_PP;
	gpioInitStruc.GPIO_Pin = GPIO_Pin_5;
	gpioInitStruc.GPIO_Speed=GPIO_Speed_400KHz;
	GPIO_Init(GPIOA,&gpioInitStruc);
}

//Set the LED frek based on the AD_value
void setFrek(uint16_t AD_value){
	if(AD_value<2200){
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
			delay(50000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			delay(50000);
	}
	else if(AD_value<3200){
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
			delay(150000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			delay(150000);
	}
	else if(AD_value<3600){
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
			delay(300000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			delay(300000);
	}
	else if(AD_value<3800){
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
			delay(500000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			delay(500000);
		}
	else{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
	}
}

//delay function
void delay(int pocet){
	int i=0;
	for(i;i<pocet;i++){}
}
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
 int main(void)
 {

   adcInit();
   initLED();
   uint16_t AD_value=(uint16_t)0;

   while(1){
 	  ADC_SoftwareStartConv(ADC1);
 	  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)){}
 	  AD_value=ADC_GetConversionValue(ADC1);
 	  setFrek(AD_value);
   }
   return 0;
 }

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
