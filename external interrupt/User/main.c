/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s103.h"
#include "stm8s_it.h"

uint32_t delay_time = 200;

void main(void)
{
  //Clock default = 2MHz
 
  /* GPIO configuration -----------------------------------------*/
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);

  Delay_Using_Timer4_Init();
  
  /*Config PE0, PD0 as input pull up for external interrupt*/
  GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)(GPIO_PIN_1), GPIO_MODE_IN_PU_IT);
  GPIO_Init(GPIOD, (GPIO_PIN_4), GPIO_MODE_IN_PU_IT);
  
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA, EXTI_SENSITIVITY_FALL_ONLY);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);
  
  /*Note: PD7 is TLU, use INTERRUPT_HANDLER(TLI_IRQHandler,0) */
  
  //enableInterrupts();
  
  while (1)
  {
//     GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
//     Delay_ms(delay_time);
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
