/*****************************************************************************//**
 * @file    command_handlers_basic.h
 * @brief   Brief description of the file
 * @author  Hugo Arganda
 * @date    May 9, 2017
 * @version 1.0
 *
 * @note
 * Copyright (C) 2017 The Morey Corporation
 *
 * @par
 * All rights reserved.  This file is the intellectual property of
 * The Morey Corporation; it may not be copied, duplicated or
 * transferred to a third party without prior written permission.
 *
 *****************************************************************************/

#ifndef _COMMAND_HANDLERS_BASIC_H_
#define _COMMAND_HANDLERS_BASIC_H_

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "command_handler_types.h"

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
 * @brief       Display dummy function name.
 * @param       data_ptr - Pointer to command data
 * @param       length_ptr - Length of incoming data
 * @return      return CMD_RSP_OK if success.
 *****************************************************************************/
uint8_t cmd_handler_start(char* data_ptr, uint16_t length_ptr);

/*****************************************************************************//**
 * @brief       Display dummy function name.
 * @param       data_ptr - Pointer to command data
 * @param       length_ptr - Length of incoming data
 * @return      return CMD_RSP_OK if success.
 *****************************************************************************/
uint8_t cmd_handler_stop(char* data_ptr, uint16_t length_ptr);

/*****************************************************************************//**
 * @brief       Display dummy function name.
 * @param       data_ptr - Pointer to command data
 * @param       length_ptr - Length of incoming data
 * @return      return CMD_RSP_OK if success.
 *****************************************************************************/
uint8_t cmd_handler_end(char* data_ptr, uint16_t length_ptr);

/*****************************************************************************//**
 * @brief       Display dummy function name.
 * @param       data_ptr - Pointer to command data
 * @param       length_ptr - Length of incoming data
 * @return      return CMD_RSP_OK if success.
 *****************************************************************************/
uint8_t cmd_handler_next(char* data_ptr, uint16_t length_ptr);

/*****************************************************************************//**
 * @brief       Display dummy function name.
 * @param       data_ptr - Pointer to command data
 * @param       length_ptr - Length of incoming data
 * @return      return CMD_RSP_OK if success.
 *****************************************************************************/
uint8_t cmd_handler_white(char* data_ptr, uint16_t length_ptr);

/*****************************************************************************//**
 * @brief       Display dummy function name.
 * @param       data_ptr - Pointer to command data
 * @param       length_ptr - Length of incoming data
 * @return      return CMD_RSP_OK if success.
 *****************************************************************************/
uint8_t cmd_handler_black(char* data_ptr, uint16_t length_ptr);

/*****************************************************************************//**
 * @brief       Display dummy function name.
 * @param       data_ptr - Pointer to command data
 * @param       length_ptr - Length of incoming data
 * @return      return CMD_RSP_OK if success.
 *****************************************************************************/
uint8_t cmd_handler_prev(char* data_ptr, uint16_t length_ptr);

/*****************************************************************************//**
 * @brief       Display dummy function name.
 * @param       data_ptr - Pointer to command data
 * @param       length_ptr - Length of incoming data
 * @return      return CMD_RSP_OK if success.
 *****************************************************************************/
uint8_t cmd_handler_hello(char* data_ptr, uint16_t length_ptr);

#endif /* _COMMAND_HANDLERS_BASIC_H_ */

