/* UART Header File */

/* 
 * File: uart.h
 * Purpose: UART hardware abstraction layer
 */


#ifndef UART_H
#define UART_H

/* Includes */
#include <stdio.h>
#include <stm32f1xx.h>
#include "clock.h"
#include "app.h"
#include <math.h>

/* Macros */

/* Type Definitions */
typedef enum
{
    USART_DRV_1 = 1,
    USART_DRV_2,
    USART_DRV_3,
} usartDrvNum_t;

/* Function Declarations */

extern STATUS uartDrvInit (usartDrvNum_t usartNum, uint32_t baud);
extern STATUS uartDrvEnable (usartDrvNum_t usartNum);
extern STATUS uartDrvStop (usartDrvNum_t usartNum);

#endif /* UART_H */