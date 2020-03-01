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
