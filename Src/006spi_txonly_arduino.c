

// alternate func mode is 5
// PB 9 as SPI2 NSS
// PB10 as SPI2 SCK
// PB15 as SPI2 MOSI
// PB14 as SPI2 MISO

#include <stdint.h>
#include "stm32f401xx.h"
#include <string.h>

void delay(void)
{
	for (uint32_t i =0;i<50000; i++);
}

void SPI2_GPIO_Init(void)
{
	GPIO_Handle_t SPIPins;
	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	//GPIO_Init(&SPIPins);

	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&SPIPins);
}

void SPI2_Init(void)
{
	SPI_Handle_t SPI2handle;
	SPI2handle.pSPIx=SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI; // software nss

	SPI_Init(&SPI2handle);

}

void GPIO_Button_Init()
{
	GPIO_Handle_t GPIOswitch;

	GPIOswitch.pGPIOx=GPIOC;
	GPIOswitch.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_13;
	GPIOswitch.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_IN;

	GPIO_Init(&GPIOswitch);

}

int main(void)
{
	char user_data[] = "Hello mfffffffssss";

	GPIO_Button_Init();

	SPI2_GPIO_Init();
	SPI2_Init();

	// enable to enable the NSS pin when hardware connection is done
	SPI_SSOEConfig(SPI2, ENABLE);

	while(1)
	{
	    if(GPIO_ReadFromInputPin(GPIOC, 13) == 0)
	    {
	        delay(); // debounce

	        while(GPIO_ReadFromInputPin(GPIOC, 13) == 0); // wait release

	        SPI_PeripheralControl(SPI2, ENABLE);

	        delay(); // give slave time

	        uint8_t dataLength = strlen(user_data);
	        SPI_SendData(SPI2, &dataLength, 1);
	        SPI_SendData(SPI2, (uint8_t *)user_data, dataLength);

	        while(SPI_GetFlagStatus(SPI2, SPI_SR_BSY));

	        SPI_PeripheralControl(SPI2, DISABLE);
	    }
	}
	return 0;
}
