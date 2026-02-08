/* main.c */

#include <stdio.h>
#include <stm32f1xx.h>
#include <delay.h>
#include <stddef.h>  // for size_t
#include <unistd.h>  // for STDERR_FILENO
#include "gpio.h"
#include "uart.h"


void uart_write (char * buf, size_t len)
{
	while ((USART1->SR & USART_SR_TXE) == 0)
	{ /* Wait for TX buffer to be ready */	}
	
	/* Test with A */
	for (size_t i = 0; i < len; i++)
	{
		USART1->DR = buf[i];
		/* Wait until transmit is done */
		while (!(USART1->SR & USART_SR_TC));
	}
}

int _write(int fd, char *buf, size_t len)
{
	uart_write (buf, len);
	return len;
}

int main(void)
{

	/* Init GPIO Port C, Init GPIO Port A , Init GPIO Port A, Init AFIO */
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

	/* Set GPIO on PORT C - P13 */
	GPIOC->CRH &= ~(0xF << ((13 - 8) * 4));
	GPIOC->CRH |=  (0x2 << ((13 - 8) * 4));


	uartDrvInit (USART_DRV_1, 115200);
	uartDrvEnable (USART_DRV_1);

	while(1){
		/* Blink */
		GPIOC->ODR ^= 1 << 13;
		printf("A Inês é uma linda\r\n");
		ms_delay(1000);
	}
}