/*****************************************************************************//**
 * @file    console_config.h
 * @brief   Brief description of the file
 * @author  Someone
 * @author  Someone else
 * @date    Feb 9, 2018
 * @version 1.0
 *
 * @note
 * Copyright (C) 2018 The Morey Corporation
 *
 * @par
 * All rights reserved.  This file is the intellectual property of
 * The Morey Corporation; it may not be copied, duplicated or
 * transferred to a third party without prior written permission.
 *
 *****************************************************************************/

#ifndef _CONSOLE_CONFIG_H_
#define _CONSOLE_CONFIG_H_

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "usart.h"
#include "utils.h"

/*****************************************************************************
 * Macros
 *****************************************************************************/

#define CLI_HEADER_LENGTH               (64U)

/* Buffer used for printf calls */
#define CLI_FMT_BUFFER_LEN              (512U)

/* Buffer used for incoming CLI data */
#define CLI_CIRC_BUFFER_LEN             (1024U)

/* Cursor String, to disable this feature just remove or comment this define */
#define CLI_CURSOR_STRING               "cli> "

/* UART Handler, to disable UART usage by the console just remove or comment this define */
#define CLI_UART_HANDLE                 huart2

/* UART Port debug Enable state by default: 0u = Disabled, 1u = Enabled */
#define CLI_UART_DEBUG_DEFAULT_STATE    (TRUE)

/* CLI End-Of-Line string used when println or printfln are used */
#define CLI_EOL_STRING                 "\r\n"

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
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/


#endif /* _CONSOLE_CONFIG_H_ */
