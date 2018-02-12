/*****************************************************************************//**
 * @file    command_table_common.c
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

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include <command_handler_table.h>

/*****************************************************************************
 * Macros
 *****************************************************************************/

/*****************************************************************************
 * Type and Constant Definitions
 *****************************************************************************/

#define CMD_COMMON_DEF_TABLE_X(num, cmd, len, label, handler, num_params) {cmd, len, label, handler, num_params},
static const cmd_handler_t cmd_handlers_common[] = {
		CMD_COMMON_DEF_TABLE
};
#undef CMD_COMMON_DEF_TABLE_X

/*****************************************************************************
 * Global Declarations
 *****************************************************************************/

/*****************************************************************************
 * Static Declarations
 *****************************************************************************/

/*****************************************************************************
 * Private Function Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Private Function Implementations
 *****************************************************************************/

/*****************************************************************************
 * Public Function Implementations
 *****************************************************************************/

const cmd_handler_t* cmd_handlers_common_table(void)
{
    return &cmd_handlers_common[0];
}

uint16_t cmd_handlers_common_table_size(void)
{
    return ARRAYSIZE(cmd_handlers_common);
}





