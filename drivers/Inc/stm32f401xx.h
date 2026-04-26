/*
 * stm32f01xx.h
 *
 *  Created on: Mar 21, 2026
 *      Author: Admin
 */

#ifndef INC_STM32F401XX_H_
#define INC_STM32F401XX_H_
#include <stdint.h>

// Microcontroller specific addresses
#define NVIC_ISER0						 (__vo uint32_t*)0xE000E100
#define NVIC_ISER1						 (__vo uint32_t*)0xE000E104
#define NVIC_ISER2						 (__vo uint32_t*)0xE000E108
#define NVIC_ISER3						 (__vo uint32_t*)0xE000E10c

#define NVIC_ICER0						 (__vo uint32_t*)0XE000E180
#define NVIC_ICER1						 (__vo uint32_t*)0XE000E184
#define NVIC_ICER2						 (__vo uint32_t*)0XE000E188
#define NVIC_ICER3						 (__vo uint32_t*)0XE000E18c

#define NO_PR_BITS_IMPLEMENTED			 4
#define NVIC_PR_BASE_ADDR				 (__vo uint32_t*)0xE000E400

#define FLASH_BASEADDR                   0x08000000U
#define ROM_BASEADDR                     0x1FFF0000U          /* System memory */
#define SRAM1_BASEADDR                   0x20000000U
#define SRAM                             SRAM1_BASEADDR

#define PERIPH_BASEADDR                  0x40000000U
#define APB1PERIPH_BASEADDR		    	 PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR				 0x40010000U
#define AHB1PERIPH_BASEADDR				 0x40020000U
#define AHB2PERIPH_BASEADDR				 0x50000000U

#define GPIOA_BASEADDR                   (AHB1PERIPH_BASEADDR + 0x0000U)
#define GPIOB_BASEADDR                   (AHB1PERIPH_BASEADDR + 0x0400U)
#define GPIOC_BASEADDR                   (AHB1PERIPH_BASEADDR + 0x0800U)
#define GPIOD_BASEADDR                   (AHB1PERIPH_BASEADDR + 0x0C00U)
#define GPIOE_BASEADDR                   (AHB1PERIPH_BASEADDR + 0x1000U)
#define GPIOH_BASEADDR                   (AHB1PERIPH_BASEADDR + 0x1C00U)
#define RCC_BASEADDR                     (AHB1PERIPH_BASEADDR + 0x3800U)

#define I2C1_BASEADDR                    (APB1PERIPH_BASEADDR + 0X5400U)
#define I2C2_BASEADDR                    (APB1PERIPH_BASEADDR + 0X5800U)
#define I2C3_BASEADDR                    (APB1PERIPH_BASEADDR + 0X5C00U)
#define SPI2_BASEADDR                    (APB1PERIPH_BASEADDR + 0X3800U)
#define SPI3_BASEADDR                    (APB1PERIPH_BASEADDR + 0X3C00U)
#define USART2_BASEADDR                  (APB1PERIPH_BASEADDR + 0X4400U)

#define SPI1_BASEADDR                    (APB2PERIPH_BASEADDR + 0X3000U)
#define SPI4_BASEADDR                    (APB2PERIPH_BASEADDR + 0X3400U)
#define USART1_BASEADDR                  (APB2PERIPH_BASEADDR + 0X1000U)
#define USART6_BASEADDR                  (APB2PERIPH_BASEADDR + 0X1400U)
#define EXTI_BASEADDR                    (APB2PERIPH_BASEADDR + 0X3C00U)
#define SYSCFG_BASEADDR                  (APB2PERIPH_BASEADDR + 0X3800U)

#define __vo volatile

typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
}GPIO_RegDef_t;

/* GPIO_RegDef_t *pGPIOA = (GPIO_RegDef_t *)GPIOA_BASEADDR; */
#define GPIOA                            ((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB                            ((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC                            ((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD                            ((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE                            ((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOH                            ((GPIO_RegDef_t *)GPIOH_BASEADDR)

typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	uint32_t      Reserved0[2];
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	uint32_t      Reserved1[2];
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	uint32_t      Reserved2[2];
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	uint32_t      Reserved3[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	uint32_t      Reserved4[2];
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	uint32_t      Reserved5[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	uint32_t      Reserved6[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
	uint32_t      Reserved7;
	__vo uint32_t DCKCFGR;
}RCC_RegDef_t;

#define RCC                             ((RCC_RegDef_t *)RCC_BASEADDR)

typedef struct {
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;

#define EXTI 							((EXTI_RegDef_t *)EXTI_BASEADDR)

typedef struct {
	__vo uint32_t MEMRP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	uint32_t Reserved[2];
	__vo uint32_t CMPCR;
}SYSCFG_RegDef_t;

#define SYSCFG							((SYSCFG_RegDef_t *)SYSCFG_BASEADDR)

typedef struct {
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;
}SPI_RegDef_t;

#define SPI1							((SPI_RegDef_t *)SPI1_BASEADDR)
#define SPI2							((SPI_RegDef_t *)SPI2_BASEADDR)
#define SPI3							((SPI_RegDef_t *)SPI3_BASEADDR)
#define SPI4							((SPI_RegDef_t *)SPI4_BASEADDR)

// bit positions of control register of SPI CR1 REG
#define SPI_CR1_CPHA					0
#define SPI_CR1_CPOL					1
#define SPI_CR1_MSTR					2
#define SPI_CR1_BR						3
#define SPI_CR1_SPE						6
#define SPI_CR1_LSBFIRST				7
#define SPI_CR1_SSI						8
#define SPI_CR1_SSM						9
#define SPI_CR1_RXONLY					10
#define SPI_CR1_DFF						11
#define SPI_CR1_CRCNEXT					12
#define SPI_CR1_CRCEN					13
#define SPI_CR1_BIDIOE					14
#define SPI_CR1_BIDIMODE				15

// bit positions of control register of SPI CR2 REG
#define SPI_CR2_RXDMAEN					0
#define SPI_CR2_TXE						1
#define SPI_CR2_SSOE					2
#define SPI_CR2_FRF						4
#define SPI_CR2_ERRIE					5
#define SPI_CR2_RXNEIE					6
#define SPI_CR2_TXEIE					7

// bit positions of control register of SPI SR REG
#define SPI_SR_RXNE						0
#define SPI_SR_TXE						1
#define SPI_SR_CHSIDE					2
#define SPI_SR_UDR						3
#define SPI_SR_CRCERR					4
#define SPI_SR_MODF						5
#define SPI_SR_OVR						6
#define SPI_SR_BSY						7
#define SPI_SR_FRE						8

#define GPIOA_PCLK_EN()                 ( RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()                 ( RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()                 ( RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()                 ( RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()                 ( RCC->AHB1ENR |= (1<<4))
#define GPIOH_PCLK_EN()                 ( RCC->AHB1ENR |= (1<<7))

#define I2C1_PCLK_EN()                  ( RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN()                  ( RCC->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN()                  ( RCC->APB1ENR |= (1<<23))

#define SPI1_PCLK_EN()                  ( RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN()                  ( RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()                  ( RCC->APB1ENR |= (1<<15))
#define SPI4_PCLK_EN()                  ( RCC->APB2ENR |= (1<<13))

#define USART1_PCLK_EN()                ( RCC->APB2ENR |= (1<<4))
#define USART2_PCLK_EN()                ( RCC->APB1ENR |= (1<<17))
#define USART6_PCLK_EN()                ( RCC->APB2ENR |= (1<<5))

#define SYSCFG_PCLK_EN()                ( RCC->APB2ENR |= (1<<14))

#define GPIOA_PCLK_DI()                 ( RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()                 ( RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI()                 ( RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()                 ( RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()                 ( RCC->AHB1ENR &= ~(1<<4))
#define GPIOH_PCLK_DI()                 ( RCC->AHB1ENR &= ~(1<<7))

#define I2C1_PCLK_DI()                  ( RCC->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI()                  ( RCC->APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI()                  ( RCC->APB1ENR &= ~(1<<23))

#define SPI1_PCLK_DI()                  ( RCC->APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI()                  ( RCC->APB1ENR &= ~(1<<14))
#define SPI3_PCLK_DI()                  ( RCC->APB1ENR &= ~(1<<15))
#define SPI4_PCLK_DI()                  ( RCC->APB2ENR &= ~(1<<13))

#define USART1_PCLK_DI()                ( RCC->APB2ENR &= ~(1<<4))
#define USART2_PCLK_DI()                ( RCC->APB1ENR &= ~(1<<17))
#define USART6_PCLK_DI()                ( RCC->APB2ENR &= ~(1<<5))

#define SYSCFG_PCLK_DI()                ( RCC->APB2ENR &= ~(1<<14))

#define ENABLE 							1
#define DISABLE							0
#define SET 							ENABLE
#define RESET 							DISABLE
#define GPIO_PIN_SET 					SET
#define GPIO_PIN_RESET 					RESET
#define FLAG_RESET						RESET
#define FLAG_SET						SET

#define GPIOA_REG_RESET()				do{(RCC -> AHB1RSTR |= (1<<0)); (RCC -> AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOB_REG_RESET()				do{(RCC -> AHB1RSTR |= (1<<1)); (RCC -> AHB1RSTR &= ~(1<<1)); }while(0)
#define GPIOC_REG_RESET()				do{(RCC -> AHB1RSTR |= (1<<2)); (RCC -> AHB1RSTR &= ~(1<<2)); }while(0)
#define GPIOD_REG_RESET()				do{(RCC -> AHB1RSTR |= (1<<3)); (RCC -> AHB1RSTR &= ~(1<<3)); }while(0)
#define GPIOE_REG_RESET()				do{(RCC -> AHB1RSTR |= (1<<4)); (RCC -> AHB1RSTR &= ~(1<<4)); }while(0)
#define GPIOH_REG_RESET()				do{(RCC -> AHB1RSTR |= (1<<5)); (RCC -> AHB1RSTR &= ~(1<<5)); }while(0)

#define SPI1_REG_RESET()  				do{ (RCC->APB2RSTR |= (1<<12)); (RCC->APB2RSTR &= ~(1<<12)); }while(0)
#define SPI2_REG_RESET()  				do{ (RCC->APB1RSTR |= (1<<14)); (RCC->APB1RSTR &= ~(1<<14)); }while(0)
#define SPI3_REG_RESET()  				do{ (RCC->APB1RSTR |= (1<<15)); (RCC->APB1RSTR &= ~(1<<15)); }while(0)

#define GPIO_BASEADDR_TO_CODE(x)		((x==GPIOA)? 0 : (x==GPIOB)? 1 : (x==GPIOC)? 2 : (x==GPIOD)? 3 : (x==GPIOE)? 4 : (x==GPIOH)? 5 : 0)

#define IRQ_NO_EXTI0					6
#define IRQ_NO_EXTI1					7
#define IRQ_NO_EXTI2					8
#define IRQ_NO_EXTI3					9
#define IRQ_NO_EXTI4					10
#define IRQ_NO_EXTI9_5					23
#define IRQ_NO_EXTI15_10				40

#define NVIC_IRQ_PRIO_15				15  //make from 0 to 15

#include "stm32f401xx_gpio_driver.h"
#include "stm32f401xx_spi_driver.h"

#endif /* INC_STM32F401XX_H_ */
