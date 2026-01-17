/* main.c */

#include <stdio.h>
#include <stm32f1xx.h>
#include <delay.h>
#include <stddef.h>  // for size_t
#include <unistd.h>  // for STDERR_FILENO
#include "gpio.h"


void uart_write (char * buf, size_t len)
{
	while ((USART1->SR & USART_SR_TXE) == 0)
	{/* Wait for TX buffer to be ready */	}
	
	/* Test with A */
	USART1->DR = 'A';
}

int _write(int fd, char *buf, size_t len)
{
	uart_write (buf, len);
	return len;
}

int main(void)
{

	/* Init GPIO Port C, Init GPIO Port A , Init GPIO Port A, Init AFIO */
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | 
					RCC_APB2ENR_IOPAEN |
					RCC_APB2ENR_USART1EN | 
					RCC_APB2ENR_AFIOEN;

	/* Set GPIO on PORT C - P13 */
	GPIOC->CRH &= ~(0xF << ((13 - 8) * 4));
	GPIOC->CRH |=  (0x2 << ((13 - 8) * 4));

	/* 
	Configure as Alternate function output Push-pull 
	and Output mode, max speed
	*/

	/* Clear PA9 config */
	GPIOA->CRH &= ~GPIO_CRH_CNF9_Msk;
	GPIOA->CRH &= ~GPIO_CRH_MODE9_Msk;

	/* MODE9 = 11 (50 MHz), CNF9 = 10 (Alternate Function push-pull) */
	GPIOA->CRH |=  GPIO_CRH_CNF9_1;
	GPIOA->CRH |=  GPIO_CRH_MODE9_1 | GPIO_CRH_MODE9_0;

	/* 
	See section 27.3.4 from RM0008 Rev 21
	Baud = fCLK / (16 * USARTDIV) 
	USARTDIV = fCLK / (16 * Baud)
	USARTDIV = 8,000,000 / (16 * 115200)
	USARTDIV = 4.340277 (...)
	Mantissa = 4
	Div = 0.340277 * 16 = 5.44
	*/
	USART1->BRR = (4 << 4) | (5 << 0);

	USART1->CR1 = USART_CR1_TE;  // enable transmitter
	USART1->CR1 |= USART_CR1_UE; // enable USART	

	printf("Ola\n");

	while(1){
		/* Blink */
		printf("Ola\n");
		GPIOC->ODR ^= 1 << 13;
		ms_delay(1000);
	}
}