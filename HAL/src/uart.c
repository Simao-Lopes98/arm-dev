/*
 * uart.c
 * UART Hardware Abstraction Layer Implementation
 */

/* Includes */
#include "uart.h"

/* Private variables */

/* USART driver list */
static USART_TypeDef * usartDrvs [4] = 
    {
    NULL,
    USART1,
    USART2,
    USART3
    };

/* Private function prototypes */
static void usart1Init (void);
static STATUS configBaud (USART_TypeDef * usart, uint32_t baud);
static STATUS checkUsartDrvNum (usartDrvNum_t usartNum);

/* Public functions */

STATUS uartDrvInit (usartDrvNum_t usartNum, uint32_t baud)
{
    if (checkUsartDrvNum(usartNum) != OK)
        return ERROR;

    USART_TypeDef * usartDrv = usartDrvs[usartNum];

    /* Not pretty, it is what it is */
    switch (usartNum)
    {
    case USART_DRV_1:
        usart1Init();
        break;
    case USART_DRV_2:
        /* TODO */
        break;
    case USART_DRV_3:
        /* TODO */
        break;
    
    default:
        /* Should not reach this */
        break;
    }

    if (configBaud (usartDrv, baud) != OK)
    {
        return ERROR;
    }

    /* enable TX and RX */
    usartDrv->CR1 = USART_CR1_TE | USART_CR1_RE;  

    return OK;
}

STATUS uartDrvEnable (usartDrvNum_t usartNum)
{
    if (checkUsartDrvNum(usartNum) != OK)
        return ERROR;

    USART_TypeDef * usartDrv = usartDrvs[usartNum];
    
    /* enable USART */
    usartDrv->CR1 |= USART_CR1_UE;
    
    return OK;
}

STATUS uartDrvStop (usartDrvNum_t usartNum)
{
    if (checkUsartDrvNum(usartNum) != OK)
        return ERROR;

    USART_TypeDef * usartDrv = usartDrvs[usartNum];
    
    /* stop USART */
    usartDrv->CR1 &= ~USART_CR1_UE;
    
    return OK;
}

/* Private functions */

static void usart1Init (void)
{
    /* Init USART 1, Alternate function and IO Port A */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | 
                    RCC_APB2ENR_AFIOEN |
                    RCC_APB2ENR_IOPAEN;

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
}

static STATUS checkUsartDrvNum (usartDrvNum_t usartNum)
{
    if (usartNum > USART_DRV_3 || usartNum < USART_DRV_1)
    {
        return ERROR;
    }

    return OK;
}

/* Configures the baud rate */
static STATUS configBaud (USART_TypeDef * usart, uint32_t baud)
{
	/* 
	See section 27.3.4 from RM0008 Rev 21
    Example for a baud of 115200 
	Baud = fCLK / (16 * USARTDIV) 
	USARTDIV = fCLK / (16 * Baud)
	USARTDIV = 8,000,000 / (16 * 115200)
	USARTDIV = 4.340277 (...)
	Mantissa = 4
	Div = 0.340277 * 16 = 5.44
	*/

    /* TODO: Add floating point cal */
    // int e = 0;
    // uint8_t m = 0;
    // double baudDiv = CLK_RATE / (16 * baud);
    // m = (uint8_t)frexp(baudDiv, &e);

    usart->BRR = (4 << 4) | (5 << 0);

    /* TODO: Add error calculation */
    return OK;
}