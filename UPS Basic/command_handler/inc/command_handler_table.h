/*****************************************************************************//**
 * @file    command_table_common.h
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
 * CHANGE HISTORY:
 * +------------+----------------+--------+-------------------------------------------+
 * |    DATE    |     ISSUE      | Author |          DESCRIPTION OF CHANGE            |
 * +------------+----------------+--------+-------------------------------------------+
 * | 2017-08-19 |       :        |  RPE   | Updated.                                  |
 * +------------+----------------+--------+-------------------------------------------+
 *****************************************************************************/

#ifndef _COMMAND_TABLE_COMMON_H_
#define _COMMAND_TABLE_COMMON_H_

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "command_handler_types.h"
#include "command_handlers_basic.h"

/*****************************************************************************
 * Macros
 *****************************************************************************/

#define CMD_COMMON_DEF_TABLE_X(num, desc, handler, num_params)
#define CMD_COMMON_DEF_TABLE \
    /* ------------------- Identifier, --- "Command", ------ # chars, --- "Description", -------- Handler, ---------- #parameters -- */\
	CMD_COMMON_DEF_TABLE_X(CMD_START,      "PRESN+START",    11,          "Start Presentation",   cmd_handler_start,  0               )\
	CMD_COMMON_DEF_TABLE_X(CMD_END,        "PRESN+END",       9,          "End Presentation",     cmd_handler_end,    0               )\
	CMD_COMMON_DEF_TABLE_X(CMD_NEXT,       "PRESN+NEXT",     10,          "Next Slide",           cmd_handler_next,   0               )\
	CMD_COMMON_DEF_TABLE_X(CMD_PREV,       "PRESN+PREV",     10,          "Previous Slide",       cmd_handler_prev,   0               )\
	CMD_COMMON_DEF_TABLE_X(CMD_WHITE,      "PRESN+WHITE",    11,          "Blank White Slide",    cmd_handler_white,  0               )\
	CMD_COMMON_DEF_TABLE_X(CMD_BLACK,      "PRESN+BLACK",    11,          "Blank Black Slide",    cmd_handler_black,  0               )\
	CMD_COMMON_DEF_TABLE_X(CMD_HELLO,      "PRESN+TXT",       9,          "Hello World!",         cmd_handler_hello,  0               )\

#undef CMD_COMMON_DEF_TABLE_X

#undef CMD_COMMON_DEF_TABLE_X

/*****************************************************************************
 * Type and Constant definitions
 *****************************************************************************/

#define CMD_COMMON_DEF_TABLE_X(num, cmd, len, label, handler, num_params) num,
typedef enum
{
	CMD_COMMON_DEF_TABLE
} tsw_cmd_common_index_t;
#undef CMD_COMMON_DEF_TABLE_X

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
const cmd_handler_t* cmd_handlers_common_table(void);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
uint16_t cmd_handlers_common_table_size(void);

#endif /* _COMMAND_TABLE_COMMON_H_ */
