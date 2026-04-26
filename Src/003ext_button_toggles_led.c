/*
 * 002button_toggles_led.c
 *
 *  Created on: Apr 4, 2026
 *      Author: Admin
 */
#include "stm32f401xx.h"

void delay(void)
{
	for (uint32_t i =0;i<50000; i++);
}

int main(void)
{
	GPIO_Handle_t GPIOled;
	GPIO_Handle_t GPIOswitch;

	GPIOled.pGPIOx=GPIOA;
	GPIOled.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_5;
	GPIOled.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT;
	GPIOled.GPIO_PinConfig.GPIO_PinSpeed=GPIO_SPEED_FAST;
	GPIOled.GPIO_PinConfig.GPIO_PinOPType=GPIO_OP_TYPE_PP;
	GPIOled.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&GPIOled);

	GPIOswitch.pGPIOx=GPIOB;
	GPIOswitch.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_12;
	GPIOswitch.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_IN;

	GPIO_PeriClockControl(GPIOB, ENABLE);
	GPIO_Init(&GPIOswitch);
	while(1)
	{
		if (!GPIO_ReadFromInputPin(GPIOB, 12))  // in nucleo the switch is pulled up all the time, so when button is pressed its pulled down
		{
			delay();
			GPIO_ToggleOutputPin(GPIOA, 5); //toggles the led
			//while(!GPIO_ReadFromInputPin(GPIOB, 12)); //waits till button isnt pressed
		}
	}






	return 0;
}

// interrupt handlers dont take anything dont return anything
void EXTI0_IRQHandler(void)
{
	// handle the interrupt
	GPIO_IRQHandling(0);
}
