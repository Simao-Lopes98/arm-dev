/* main.c */

#include <stdio.h>
#include <stm32f1xx.h>
#include <delay.h>
#include "gpio.h"

gpio_t * gpio_drv;

int main(void)
{


	/* Init GPIO */
	gpio_drv =  gpio_drv_init (GPIO_C);

	/* Set GPIO as OUTPUT */
	gpio_drv->CRH = 0x02 << ((13 - 8) << 2);

	while(1){
		/* Blink */
		gpio_drv->ODR ^= 1 << 13;
		ms_delay(1000);
	}
}