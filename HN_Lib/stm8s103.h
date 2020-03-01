//Header file. Created by HuuNgan    09/01/2020
#ifndef    __STM8S103__H
#define    __STM8S103__H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/*Functions ------------------------------------------------------------------*/
void CLK_CONFIG_16MHZ_HSE(void);
void Delay_Using_Timer4_Init(void);
void Delay_ISR(void);
void Delay_ms(uint32_t time);

//uint32_t milisec();


#endif