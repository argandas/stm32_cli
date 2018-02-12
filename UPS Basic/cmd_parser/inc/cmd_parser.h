/*****************************************************************************//**
 * @file    cmd_parser.h
 * @brief   Command Parser
 * @author  Hugo Arganda
 * @date    May 9, 2017
 * @version 1.0
 *****************************************************************************/

#ifndef _COMMAND_PARSER_H_
#define _COMMAND_PARSER_H_

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "utils.h"

/*****************************************************************************
 * Macros
 *****************************************************************************/

#define CMD_PARSER_BUFF_SIZE (512)

/*****************************************************************************
 * Type and Constant definitions
 *****************************************************************************/

typedef void (*cmd_handler_callback)(uint8_t* cmd_ptr, uint16_t len);

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
void cmd_parser_setup(void);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
void cmd_parser_loop(uint8_t verbose);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
void cmd_parser_callback_register(cmd_handler_callback callback);

#endif /* _COMMAND_PARSER_H_ */
