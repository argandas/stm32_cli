/*****************************************************************************//**
 * @file    command_handler_types.h
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

#ifndef COMMAND_HANDLER_TYPES_H_
#define COMMAND_HANDLER_TYPES_H_

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "utils.h"

/*****************************************************************************
 * Macros
 *****************************************************************************/

#define RSP_DEF_TABLE_X(code, desc)
#define RSP_DEF_TABLE \
/* ---------------- Response code, ----------------- "Description" ---------------------- */\
    RSP_DEF_TABLE_X(CMD_RSP_INVALID,                 "Invalid response"                    )\
    RSP_DEF_TABLE_X(CMD_RSP_OK,                      "OK"                                  )\
    RSP_DEF_TABLE_X(CMD_RSP_ERR_NULL_PTR,            "NULL pointer"                        )\
    RSP_DEF_TABLE_X(CMD_RSP_ERR_UNKNOWN_CMD,         "Unknown command"                     )\
    RSP_DEF_TABLE_X(CMD_RSP_ERR_INVALID_IDX,         "Invalid index"                       )\
    RSP_DEF_TABLE_X(CMD_RSP_ERR_INVALID_PARAM,       "Invalid parameter"                   )\
    RSP_DEF_TABLE_X(CMD_RSP_ERR_UNABLE_TO_PROCESS,   "Unable to Process"                   )\
    RSP_DEF_TABLE_X(CMD_RSP_ERR_ASCII_TO_NUM_CONV,   "Failed ASCII to number conversion"   )\
    RSP_DEF_TABLE_X(CMD_RSP_ERR_MISMATCHING_PARAMS,  "Parameters count mismatch"           )\
    RSP_DEF_TABLE_X(CMD_RSP_ERR_BUFF_OVF,            "Buffer overflow"                     )\
/* --------------------------- WARNING: Do not modify last response code ---------------- */\
	RSP_DEF_TABLE_X(CMD_RSP_ERR_MAX,                 NULL                                  )\


#undef RSP_DEF_TABLE_X

/*****************************************************************************
 * Type and Constant definitions
 *****************************************************************************/

#define RSP_DEF_TABLE_X(code, desc) code,
typedef enum
{
    RSP_DEF_TABLE
} cmd_response_t;
#undef RSP_DEF_TABLE_X

typedef struct
{
    const char *cmd; /* Command */
    uint8_t cmd_len; /* Command length */
    const char *cmd_desc; /* Command description */
    uint8_t (*callback)(char* data_ptr, uint16_t length_ptr); /* Command handler */
    uint8_t num_params; /* Number of expected parameters */
} cmd_handler_t;

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
const char* get_response_description(cmd_response_t rsp);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
void response_verbose_enable(uint8_t enable);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
void response_print(cmd_response_t rsp);

#endif /* COMMAND_HANDLER_TYPES_H_ */
