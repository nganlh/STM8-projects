/**
  *******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.3.0
  * @date    16-June-2017
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s103.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
uint8_t adc_send_data[] = {0x06, 0x00, 0x00};
uint8_t adc_receive_data[3];
volatile uint16_t adc_value;
volatile float voltage = 0;

void main(void)
{
  Delay_Using_Timer4_Init();
  spi_master_initialize(SPI_BAUDRATEPRESCALER_128, GPIOC, GPIO_PIN_3);
  
  uint8_t data = 1;
  
  /* Infinite loop */
  while (1)
  {
    /*
    spi_master_transmit_receive(GPIOC, GPIO_PIN_3, adc_send_data, adc_receive_data, 3);
    adc_value = ((adc_receive_data[1]&0x0f)<<8)|(adc_receive_data[2]);
    voltage = (adc_value/4096.0)*4.096;
    */
    GPIO_WriteLow(GPIOC, GPIO_PIN_3);
    SPI_SendData(~data);
    GPIO_WriteHigh(GPIOC, GPIO_PIN_3);
    
    data =data <<1;
    if(data ==0) data =1;
    Delay_ms(100);
  }
  
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
