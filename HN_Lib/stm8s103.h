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
void spi_master_initialize(SPI_BaudRatePrescaler_TypeDef SPI_BaudRatePrescaler_X,
                           GPIO_TypeDef* CS_PORT,
                           GPIO_Pin_TypeDef CS_PIN);

void spi_master_transmit_receive(GPIO_TypeDef* CS_PORT,
                                 GPIO_Pin_TypeDef CS_PIN,
                                 uint8_t* send_data,
                                 uint8_t* receive_data,
                                 uint16_t length);



#endif