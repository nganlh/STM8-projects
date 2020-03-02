/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s103.h"
#include "stm8s_it.h"

volatile uint16_t adc_value = 0;
uint32_t delay_time = 500;

void main(void)
{
  //Clock default = 2MHz

  //TIM4 config for delay 
  Delay_Using_Timer4_Init();
 
  /* GPIO configuration -----------------------------------------*/
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);  //LED PIN

  //Init GPIO for ADC IN0
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_FL_NO_IT);
  
  //De-Init ADC Module
  ADC1_DeInit();
  
  //Init ADC1 Module
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,
            ADC1_CHANNEL_4,
            ADC1_PRESSEL_FCPU_D2,
            ADC1_EXTTRIG_TIM, DISABLE,
            ADC1_ALIGN_RIGHT,
            ADC1_SCHMITTTRIG_CHANNEL4,
            DISABLE);
  
  //Enable ADC1 End of conversion interrupt
  ADC1_ITConfig(ADC1_IT_EOCIE, ENABLE);
  
  //Enable Global Interrupt
  enableInterrupts();
  
  //Start Conversion
  ADC1_StartConversion();
  
  while (1)
  {
     GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
     Delay_ms(delay_time);
  }
}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
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

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
