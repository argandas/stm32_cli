/*****************************************************************************//**
 * @file    command_handlers_basic.c
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

/* System libraries */
#include <command_handler_table.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#include "command_handlers_basic.h"
#include "command_handler_utils.h"
#include "command_handler.h"
#include "console.h"

#include "usb_hid_presenter.h"


/*****************************************************************************
 * Macros
 *****************************************************************************/

/*****************************************************************************
 * Type and Constant Definitions
 *****************************************************************************/

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

uint8_t cmd_handler_start(char* data_ptr, uint16_t length_ptr)
 {
	cmd_response_t ret = CMD_RSP_ERR_UNABLE_TO_PROCESS;
	if (0 < usb_hid_presenter_execute(PPT_BTN_START))
	{
		ret = CMD_RSP_OK;
	}
	return ret;
}

uint8_t cmd_handler_stop(char* data_ptr, uint16_t length_ptr)
 {
	cmd_response_t ret = CMD_RSP_ERR_UNABLE_TO_PROCESS;
	if (0 < usb_hid_presenter_execute(PPT_BTN_STOP))
	{
		ret = CMD_RSP_OK;
	}
	return ret;
}

uint8_t cmd_handler_end(char* data_ptr, uint16_t length_ptr)
 {
	cmd_response_t ret = CMD_RSP_ERR_UNABLE_TO_PROCESS;
	if (0 < usb_hid_presenter_execute(PPT_BTN_END))
	{
		ret = CMD_RSP_OK;
	}
	return ret;
}

uint8_t cmd_handler_prev(char* data_ptr, uint16_t length_ptr)
 {
	cmd_response_t ret = CMD_RSP_ERR_UNABLE_TO_PROCESS;
	if (0 < usb_hid_presenter_execute(PPT_BTN_PREV))
	{
		ret = CMD_RSP_OK;
	}
	return ret;
}

uint8_t cmd_handler_next(char* data_ptr, uint16_t length_ptr)
 {
	cmd_response_t ret = CMD_RSP_ERR_UNABLE_TO_PROCESS;
	if (0 < usb_hid_presenter_execute(PPT_BTN_NEXT))
	{
		ret = CMD_RSP_OK;
	}
	return ret;
}
