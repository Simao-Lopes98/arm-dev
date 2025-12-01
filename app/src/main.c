/* main.c */

#include <stdio.h>
#include <stm32f1xx.h>
#include <delay.h>
#include "gpio.h"

gpio_t gpio_drv = {0};

int main(void)
{
	/* Set CLK ON */
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

	/* Init GPIO */
	(void) gpio_drv_init (&gpio_drv, GPIO_C);

	/* Set GPIO as OUTPUT */
	// GPIOC->CRH = 0x02 << ((13 - 8) << 2);
	gpio_drv.CRH = 0x02 << ((13 - 8) << 2);

	while(1){
		/* Blink */
		// GPIOC->ODR ^= 1 << 13;
		gpio_drv.ODR ^= 1 << 13;
		ms_delay(1000);
	}
}