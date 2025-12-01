/* main.c */

#include <stdio.h>
#include <stm32f1xx.h>
#include <delay.h>

int main(void)
{
	/* Set CLK ON */
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

	/* Set GPIO as OUTPUT */
	GPIOC->CRH = 0x02 << ((13 - 8) << 2);
	while(1){
		/* Blink */
		GPIOC->ODR ^= 1 << 13;
		ms_delay(1000);
	}
}