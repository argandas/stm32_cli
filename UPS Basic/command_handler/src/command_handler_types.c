/*****************************************************************************//**
 * @file    command_handler_types.c
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

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "command_handler_types.h"

/*****************************************************************************
 * Macros
 *****************************************************************************/

/*****************************************************************************
 * Type and Constant Definitions
 *****************************************************************************/

#define RSP_DEF_TABLE_X(code, desc) desc,
const char* rsp_descriptions[] = {
    RSP_DEF_TABLE
};
#undef RSP_DEF_TABLE_X

/*****************************************************************************
 * Global Declarations
 *****************************************************************************/

/*****************************************************************************
 * Static Declarations
 *****************************************************************************/

static uint8_t response_verbose_enabled = TRUE;

/*****************************************************************************
 * Private Function Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Private Function Implementations
 *****************************************************************************/

/*****************************************************************************
 * Public Function Implementations
 *****************************************************************************/

const char* get_response_description(cmd_response_t rsp)
{
	char* description = NULL;
	if ((CMD_RSP_ERR_MAX > rsp) && (CMD_RSP_INVALID <= rsp))
	{
		description = (char*)rsp_descriptions[rsp];
	}
    return description;
}

void response_verbose_enable(uint8_t enable)
{
	response_verbose_enabled = enable;
}

void response_print(cmd_response_t rsp)
{
	if (CMD_RSP_OK == rsp)
	{
		cli_println(get_response_description(CMD_RSP_OK));
	}
	else if (TRUE == response_verbose_enabled)
	{
		/* Print error code and description */
		cli_printfln("ERROR: %u - %s", rsp, get_response_description(rsp));
	}
	else
	{
		/* Print error code only */
		cli_printfln("ERROR: %u", rsp, get_response_description(rsp));
	}
}
