/*****************************************************************************//**
 * @file    command_handler_utils.h
 * @brief   Brief description of the file
 * @author  Hugo Arganda
 * @date    May 25, 2017
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

#ifndef COMMAND_HANDLER_UTILS_H_
#define COMMAND_HANDLER_UTILS_H_

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "utils.h"
#include "stm32f4xx_hal.h"
#include "command_handler_types.h"

/*****************************************************************************
 * Macros
 *****************************************************************************/

#define CMD_ENABLED_STR  "ENABLE"
#define CMD_DISABLED_STR "DISABLE"

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
 * @brief       Get command parameters index by ID.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
uint8_t get_parameter_by_index(const char* cmd_ptr, uint16_t cmd_len, uint8_t index, char** dest);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
cmd_response_t tsw_enable_cmd_parser(uint8_t* dest, char* data_ptr, uint16_t length_ptr);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
uint16_t uint8_array_to_hex_string(uint8_t* src, uint16_t len, uint8_t* dest, uint16_t size);

#endif /* COMMAND_HANDLER_UTILS_H_ */
