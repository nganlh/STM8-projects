#include "stm8s_clk.h"
#include "stm8s103.h"

volatile uint32_t time_keeper =0 ;    //using for delay functions

void CLK_CONFIG_16MHZ_HSE(void)
{
  CLK_DeInit();
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}

void Delay_Using_Timer4_Init(void)
{
  /*
    De duoc 1ms ta tinh duoc 125 chu ky nhung do vdk can 1 chu ky de nhay
    vao ngat nen ta se dung 124 moi that su chinh xac 
  */
  TIM4_TimeBaseInit(TIM4_PRESCALER_16,124); //1ms if f_master = 2MHz
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  
  enableInterrupts();
  TIM4_Cmd(ENABLE);  
}

void Delay_ISR(void)
{
  if(TIM4_GetITStatus(TIM4_IT_UPDATE)==SET)
  {
     if(time_keeper!=0)    time_keeper--;
     TIM4_ClearITPendingBit(TIM4_IT_UPDATE);            //Clear interrupt flag
  }
}

void Delay_ms(uint32_t time)
{
  time_keeper = time;
  while(time_keeper);
}

void spi_master_initialize(SPI_BaudRatePrescaler_TypeDef SPI_BaudRatePrescaler_X,
                           GPIO_TypeDef* CS_PORT,
                           GPIO_Pin_TypeDef CS_PIN)
{
  //Enable SPI clock
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, ENABLE);
  
  //Set the MOSI, MISO and SCK at high level
  GPIO_ExternalPullUpConfig(GPIOC, (GPIO_Pin_TypeDef)(GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7), ENABLE);
  
  //Initialize SPI mode master 0
  SPI_Init(SPI_FIRSTBIT_MSB,
           SPI_BaudRatePrescaler_X,
           SPI_MODE_MASTER,
           SPI_CLOCKPOLARITY_LOW,
           SPI_CLOCKPHASE_1EDGE,
           SPI_DATADIRECTION_2LINES_FULLDUPLEX,
           SPI_NSS_SOFT, 0x07);
  
  //SD_SPI Enable
  SPI_Cmd(ENABLE);
  
  //Set ChipSelect Pin in Output push-pull high level
  GPIO_Init(CS_PORT, CS_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}