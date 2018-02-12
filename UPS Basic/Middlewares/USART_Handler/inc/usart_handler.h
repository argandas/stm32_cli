/*****************************************************************************//**
 * @file    usart_handler.h
 * @brief   Brief description of the file
 * @author  Hugo Arganda (harganda)
 * @author  Luis Ramirez (lramirez)
 * @date    Apr 26, 2017
 * @version 1.0
 *****************************************************************************/

#ifndef _USART_HANDLER_H_
#define _USART_HANDLER_H_

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "utils.h"
#include "usart.h"

/*****************************************************************************
 * Macros
 *****************************************************************************/

#define UART_TX_MAX_WAIT_MS  (100u)

/*****************************************************************************
 * Type and Constant definitions
 *****************************************************************************/

/*****************************************************************************
 * Global Declarations
 *****************************************************************************/

/*****************************************************************************
 * Public Function Prototypes
 *****************************************************************************/

uint8_t  uart_init      (UART_HandleTypeDef *huart, uint8_t* dest, uint16_t size);
uint8_t  uart_deinit    (UART_HandleTypeDef *huart);
uint16_t uart_print     (UART_HandleTypeDef *huart, uint32_t wait_msec, uint8_t* src);
uint16_t uart_println   (UART_HandleTypeDef *huart, uint32_t wait_msec, uint8_t* src);
uint16_t uart_printf    (UART_HandleTypeDef *huart, uint32_t wait_msec, uint8_t* fmt, ...);
uint16_t uart_printfln  (UART_HandleTypeDef *huart, uint32_t wait_msec, uint8_t* fmt, ...);
uint16_t uart_write     (UART_HandleTypeDef *huart, uint32_t wait_msec, uint8_t* src, uint16_t len);
uint8_t  uart_receive_it(UART_HandleTypeDef *huart, uint8_t* dest, uint16_t size);

#endif /* _USART_HANDLER_H_ */
