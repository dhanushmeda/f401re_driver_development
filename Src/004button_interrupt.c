/*
 * 002button_toggles_led.c
 *
 *  Created on: Apr 4, 2026
 *      Author: Admin
 */
#include "stm32f401xx.h"
#include <string.h>
void delay(void)
{
	for (uint32_t i =0;i<50000; i++);
}

int main(void)
{
	GPIO_Handle_t GPIOled;
	GPIO_Handle_t GPIOswitch;
	memset(&GPIOled, 0, sizeof(GPIOled));
	memset(&GPIOswitch, 0, sizeof(GPIOswitch));
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
	GPIOswitch.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_IT_FT;

	GPIO_PeriClockControl(GPIOB, ENABLE);
	GPIO_Init(&GPIOswitch);

	// IRQ Handling
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRIO_15);
	GPIO_IRQITConfig(IRQ_NO_EXTI15_10, ENABLE);
	while (1);
	return 0;
}

// interrupt handlers dont take anything dont return anything
void EXTI15_10_IRQHandler(void)
{
	delay();
	// handle the interrupt
	GPIO_IRQHandling(GPIO_PIN_NO_12);
	GPIO_ToggleOutputPin(GPIOA, 5);

}
