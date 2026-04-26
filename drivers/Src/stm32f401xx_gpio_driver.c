/*
 * stm32f401xx_gpio_driver.c
 *
 *  Created on: Mar 22, 2026
 *      Author: Admin
 */

#include "stm32f401xx_gpio_driver.h"

/*
 * @fn - GPIO_PeriClockControl
 * @brief - used to enable or disable the peripheral clock for a GPIO port
 * @p1 - pGPIOx - base address of the GPIO Port
 * @p2 - EnorDi - enable or disable flag (ENABLE DISABLE macro)
 * @return type - none
 * @note - none
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
	}
	else
	{
		if (pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}
	}
}

/*
 * @fn - GPIO_Init
 * @brief - used to initialise the GPIO port
 * @p1 - pGPIOHandle - GPIO Port handler
 * @return type - none
 * @note - none
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	//enabling clock here
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);
	uint32_t temp = 0;
	// 1 - configure the mode of gpio pin
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG )
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER |= temp;
	}
	else
	{
		if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			// 1 configure FTSR (Falling trigger selection register
			EXTI->FTSR |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//safe to clear corresponding RTSR bit
			EXTI->RTSR &= ~(1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			// 1 configure RTSR
			EXTI->RTSR |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//safe to clear corresponding FTSR bit
			EXTI->FTSR &= ~(1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			// 1 configure both FTSR and RTSR
			EXTI->FTSR |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		//2 configure the GPIO port in SYSCFG_EXTICR
		SYSCFG_PCLK_EN();
		uint8_t temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4);
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG->EXTICR[temp] |= (portcode << (4*(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4))) ;

		//3 enable interrupt delivery using IMR (Interrupt Mask register)
		EXTI->IMR |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	temp = 0;

	// 2 - configure the speed
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;

	// 3 - configure the pupd settings
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp = 0;

	// 4 - configure the optype
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;

	// 5 - configure alt functionality
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint8_t temp1, temp2;
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4* temp2));
		pGPIOHandle -> pGPIOx -> AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
	}
}

/*
 * @fn - GPIO_DeInit
 * @brief - to reset them to their reset value using rcc peripheral reset register
 * @p1 - pGPIOx - GPIO Port base address
 * @return type - none
 * @note - none
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx) // to reset them to their reset value using rcc peripheral reset register
{
	if (pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if (pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}
	else if (pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}
	else if (pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}
	else if (pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}
	else if (pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}
}

/*
 * @fn - GPIO_ReadFromInputPin
 * @brief - read from an pin
 * @p1 - pGPIOx - GPIO Port base address
 * @p2 - PinNumber - pin number
 * @return type - value read from the pin can be bool or uint8_t
 * @note - none
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t) ((pGPIOx -> IDR >> PinNumber) & 0x00000001);
	return value;
}

/*
 * @fn - GPIO_ReadFromInputPort
 * @brief - read from a port
 * @p1 - pGPIOx - GPIO Port base address
 * @return type - value read from the pin can be  uint16_t
 * @note - none
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t) (pGPIOx -> IDR ) ;
	return value;
}

/*
 * @fn - GPIO_WriteToOutputPin
 * @brief - write to a pin
 * @p1 - pGPIOx - GPIO Port base address
 * @p2 - PinNumber - pin number
 * @p3 - value - value written to the pin
 * @return type - none
 * @note - none
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1<<PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1<<PinNumber);
	}
}

/*
 * @fn - GPIO_WriteToOutputPort
 * @brief - write to a port
 * @p1 - pGPIOx - GPIO Port base address
 * @p2 - value - value written to the pin
 * @return type - none
 * @note - none
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}

/*
 * @fn - GPIO_ToggleOutputPin
 * @brief - toggle a pin
 * @p1 - pGPIOx - GPIO Port base address
 * @p2 - PinNumber - pin number
 * @return type - none
 * @note - none
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= ( 1<<PinNumber );
}

/*
 * @fn - GPIO_IRQConfig
 * @brief - configure the interrupts
 * @p1 - IRQNumber - Interrupt number
 * @p2 - IRQPriority - Interrupt priority
 * @p3 - EnorDi - Enable or Disable using macros
 * @return type - none
 * @note - none
 */
void GPIO_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (IRQNumber < 32)
		{
			//configure NVIC ISER0
			*NVIC_ISER0 |= (1<<IRQNumber);
		}
		else if (IRQNumber >= 32 && IRQNumber < 64)
		{
			// configure NVIC ISER1
			*NVIC_ISER1 |= (1<<(IRQNumber%32));
		}
		else if (IRQNumber >= 64 && IRQNumber < 96 ) // this much is enough for our controller
		{
			*NVIC_ISER2 |= (1<<(IRQNumber%64));
		}
	}
	else
	{
		if (IRQNumber < 32)
		{
			//configure NVIC ICER0
			*NVIC_ICER0 |= (1<<IRQNumber);
		}
		else if (IRQNumber >= 32 && IRQNumber < 64)
		{
			// configure NVIC ICER1
			*NVIC_ICER1 |= (1<<(IRQNumber%32));
		}
		else if (IRQNumber >= 64 && IRQNumber < 96 )
		{
			*NVIC_ICER2 |= (1<<(IRQNumber%64));
		}
	}
}

/*
 * @fn - GPIO_IRQPriorityConfig
 * @brief - handle the priority
 * @p1 - PinNumber - which pin is related to that interrupt
 * @return type - none
 * @note - none
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	// 1. find the iprx register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	//2. write to the nvic priority reg . Note that lower half of priority register is not implemented
	uint8_t shift_amount = (8*iprx_section) + (8-NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}

/*
 * @fn - GPIO_IRQHandling
 * @brief - handle the interrupts
 * @p1 - PinNumber - which pin is related to that interrupt
 * @return type - none
 * @note - none
 */
void GPIO_IRQHandling(uint8_t PinNumber)
{
	//Implement ISR function in the application layer
	//Store the address of the ISR at the vector address of the IRQ number (taken care by startup code)

	// 1. clear the exti PR corresponding to the pin number
	if (EXTI->PR & (1<< PinNumber))
	{
		// clear
		EXTI->PR |= (1<<PinNumber);
	}
}
