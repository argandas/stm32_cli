/*****************************************************************************//**
 * @file    command_handler.h
 * @brief   Brief description of the file
 * @author  Hugo Arganda
 * @date    May 9, 2017
 * @version 1.0
 *****************************************************************************/

#ifndef _COMMAND_HANDLER_H_
#define _COMMAND_HANDLER_H_

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include <command_handler_table.h>

/*****************************************************************************
 * Macros
 *****************************************************************************/

#define CMD_HANDLER_SEARCH_BY_INDEX (FALSE)
#define CMD_HANDLER_SEARCH_BY_CMD   (TRUE)

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
void handle_complete_command(uint8_t* cmd_ptr, uint16_t len);

#endif /* _COMMAND_HANDLER_H_ */
