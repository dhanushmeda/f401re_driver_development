/*
 * stm32f4xx_spi_driver.c
 *
 *  Created on: Apr 24, 2026
 *      Author: Admin
 */
#include <stdint.h>
#include "stm32f401xx_spi_driver.h"

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
		{
			if (pSPIx == SPI1)
			{
				SPI1_PCLK_EN();
			}
			else if (pSPIx == SPI2)
			{
				SPI2_PCLK_EN();
			}
			else if (pSPIx == SPI3)
			{
				SPI3_PCLK_EN();
			}
			else if (pSPIx == SPI4)
			{
				SPI4_PCLK_EN();
			}
		}
		else
		{
			if (pSPIx == SPI1)
			{
				SPI1_PCLK_DI();
			}
			else if (pSPIx == SPI2)
			{
				SPI2_PCLK_DI();
			}
			else if (pSPIx == SPI3)
			{
				SPI3_PCLK_DI();
			}
			else if (pSPIx == SPI4)
			{
				SPI4_PCLK_DI();
			}

		}
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	//enabling clock here
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	uint32_t temp = 0;

	//configure device mode
	temp |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;

	//configure bus config
	if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//bidi mode should be cleared
		temp &= ~(1<<SPI_CR1_BIDIMODE);
	}
	else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//bidi mode should be set
		temp |= (1<<SPI_CR1_BIDIMODE);
	}
	else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		//bidi mode should be cleared and RXONLY bit must be set
		temp &= ~(1<<SPI_CR1_BIDIMODE);
		temp |= (1<<SPI_CR1_RXONLY);
	}
	temp |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	// configure spi serial clock speed
	temp |= pSPIHandle->SPIConfig.SPI_SclkSpeed<<SPI_CR1_BR;

	//configure the dff
	temp |= pSPIHandle->SPIConfig.SPI_DFF<<SPI_CR1_DFF;

	// configure CPOL
	temp |= pSPIHandle->SPIConfig.SPI_CPOL<<SPI_CR1_CPOL;

	//configure CPHA
	temp |= pSPIHandle->SPIConfig.SPI_CPHA<<SPI_CR1_CPHA;

	pSPIHandle->pSPIx->CR1 = temp;

}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();
	}
	else if(pSPIx == SPI2)
	{
		SPI2_REG_RESET();
	}
	else if(pSPIx == SPI3)
	{
		SPI3_REG_RESET();
	}
}

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if (EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1<<SPI_CR1_SPE);
	}
	else
	{
		pSPIx->CR1 &= ~(1<<SPI_CR1_SPE);
	}
}


uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if (pSPIx->SR & (1<<FlagName))
		return FLAG_SET;
	else
		return FLAG_RESET;
}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	// when we set ssm as 1 it causes master mode fault, therfore ssi should be made 1
	if (EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1<<SPI_CR1_SSI);
	}
	else
	{
		pSPIx->CR1 &= ~(1<<SPI_CR1_SSI);
	}
}

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if (EnOrDi == ENABLE)
		{
			pSPIx->CR2 |= (1<<SPI_CR2_SSOE);
		}
		else
		{
			pSPIx->CR2 &= ~(1<<SPI_CR2_SSOE);
		}
}

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len)
{
	//len is number of bytes to be transferred
	while (len>0)
	{
		// wait until TXE is set
		while(!SPI_GetFlagStatus(pSPIx,SPI_SR_TXE));

		//check dff bit
		if ((pSPIx->CR1) & (1<<SPI_CR1_DFF))
		{
			//16bit dff
			// load data into data register
			pSPIx->DR= *((uint16_t *)pTxBuffer);
			len=len-2;
			pTxBuffer += 2;
		}
		else
		{
			//8bit dff
			// load data into data register
			pSPIx->DR= *pTxBuffer;
			len=len-1;
			pTxBuffer += 1;
		}
	}
}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t len)
{
	while (len > 0)
	{
		while (! SPI_GetFlagStatus(pSPIx, SPI_SR_RXNE));
		if ((pSPIx->CR1) & (1<<SPI_CR1_DFF))
		{
			//16bit dff
			// load data into data register
			*((uint16_t *)pRxBuffer) = pSPIx->DR;
			len=len-2;
			pRxBuffer += 2;
		}
		else
		{
			//8bit dff
			// load data into data register
			*pRxBuffer = pSPIx->DR;
			len=len-1;
			pRxBuffer += 1;
		}

	}
}

void SPI_IRQITConfig(uint8_t IRQNumber,  uint8_t EnorDi)
{

}

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{

}

void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{

}
