/*****************************************************************************//**
 * @file    console.h
 * @brief   Brief description of the file
 * @author  Hugo Arganda
 * @date    May 9, 2017
 * @version 1.0
 *****************************************************************************/

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "console_config.h"

#include "stm32f4xx_hal.h"
#include <stdarg.h>

/*****************************************************************************
 * Macros
 *****************************************************************************/

/*****************************************************************************
 * Type and Constant definitions
 *****************************************************************************/

/*****************************************************************************
 * Global Declarations
 *****************************************************************************/

/*****************************************************************************
 * Public Function Prototypes
 *****************************************************************************/

/*****************************************************************************//**
 * @brief       Does CLI initialization.
 * @return      Nothing.
 *****************************************************************************/
void cli_init(void);

/*****************************************************************************//**
 * @brief       Does CLI initialization.
 * @return      Nothing.
 * @note        Call this function inside HAL_UART_RxCpltCallback.
 *****************************************************************************/
void cli_data_uart_callback(UART_HandleTypeDef *huart);

/*****************************************************************************//**
 * @brief       Put data into the CLI circular buffer.
 * @param       src - Data source
 * @param       len - Data length
 * @return      Nothing.
 * @note        Call this function inside CDC_Receive_HS.
 *****************************************************************************/
void cli_data_enqueue(uint8_t* src, uint16_t len);

/*****************************************************************************//**
 * @brief       Pop data from the CLI circular buffer.
 * @param       dest - Data destination
 * @param       len - Data length
 * @return      Number of bytes received.
 *****************************************************************************/
uint16_t cli_data_dequeue(uint8_t* dest, uint16_t len);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
void cli_echo_enable(uint8_t enable);

/*****************************************************************************//**
 * @brief       Print string.
 * @param       src - String to print (must be NULL terminated)
 * @return      Number of written bytes.
 *****************************************************************************/
uint16_t cli_print(const char* src);

/*****************************************************************************//**
 * @brief       Print string adding EOL at the end.
 * @param       src - String to print (must be NULL terminated)
 * @return      Number of written bytes.
 *****************************************************************************/
uint16_t cli_println(const char* src);

/*****************************************************************************//**
 * @brief       Print formatted string.
 * @param       fmt - Format string
 * @param       ... - Variadic parameters
 * @return      Number of written bytes.
 *****************************************************************************/
uint16_t cli_printf(const char* fmt, ...);

/*****************************************************************************//**
 * @brief       Print formatted string adding EOL at the end.
 * @param       fmt - Format string
 * @param       ... - Variadic parameters
 * @return      Number of written bytes.
 *****************************************************************************/
uint16_t cli_printfln(const char* fmt, ...);

/*****************************************************************************//**
 * @brief       Write buffer to CLI.
 * @param       src - Data source
 * @param       len - Data length
 * @return      Number of bytes written.
 *****************************************************************************/
uint16_t cli_write(const char* src, uint16_t len);

/*****************************************************************************//**
 * @brief       Enable/Debug serial port debug.
 * @param       enable - Enable state: TRUE = Enabled, FALSE = Disabled
 * @return      Nothing.
 *****************************************************************************/
void cli_enable_debug(uint8_t enable);

/*****************************************************************************//**
 * @brief       Get serial port debug status.
 * @return      Enable state: TRUE = Enabled, FALSE = Disabled
 *****************************************************************************/
uint8_t cli_debug_enabled(void);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
void cli_print_cursor(void);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
void cli_print_header(const char* fmt, ...);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
void cli_print_buffer(uint8_t* buff, uint16_t len, char sep, uint8_t row);

#endif /* _CONSOLE_H_ */
