/*
 * 001led_toggle.c
 *
 *  Created on: Apr 3, 2026
 *      Author: Admin
 */
#include "stm32f401xx.h"

void delay(void)
{
	for (uint32_t i =0;i<50000; i++);
}

int main (void)
{
	GPIO_Handle_t GPIOled;
	GPIOled.pGPIOx = GPIOA;
	GPIOled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIOled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_Init(&GPIOled);
	while (1)
	{
		GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
		delay();
	}


	return 0;
}

