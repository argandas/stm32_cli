/*****************************************************************************//**
 * @file    command_handler_utils.c
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

#include "command_handler_utils.h"
#include <string.h>

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

/*
 * Return length of the parameter
 * At this point all commands shall have passed the index and parameter count filter
 * @param dest: Pointer to pointer to save current parameter location
 * @return: Parameter length
 */
uint8_t get_parameter_by_index(const char* cmd_ptr, uint16_t len, uint8_t index, char** dest)
{
	uint8_t ret = 0;
    uint8_t num_params = 0;
    char* last_comma = NULL;
    char* next_comma = NULL;

    /* By default set pointer to NULL */
    *dest = NULL;

    char* limit = (char*)cmd_ptr + len;

    if ((NULL != cmd_ptr) && (0 < len))
    {
        /* First parameter is located after the space uint8_t ' ' */
        last_comma = strchr((char*)cmd_ptr, ' ');

        /* Look for commas, each parameter is delimited by a comma */
        for (num_params = 0; (NULL != last_comma) && (last_comma < limit); num_params++)
        {
            next_comma = strchr(last_comma+1, ',');
            /* We have found our parameter */
            if(num_params == index)
            {
				/* Calculate parameter length */
            	if(NULL != next_comma)
            	{
            		ret = (uint8_t)(next_comma - last_comma - 1);
            	}
            	else
            	{
            		ret = (uint8_t)(limit - last_comma - 1);
            	}
				*dest = last_comma + 1;
				break;
            }
            last_comma = next_comma;
        }
    }
    return ret;
}

cmd_response_t tsw_enable_cmd_parser(uint8_t* dest, char* data_ptr, uint16_t length_ptr)
{
	cmd_response_t ret = CMD_RSP_INVALID;

	/* Remove case sensitive for enable/disable commands */
	ascii_to_upper_case(data_ptr, (uint8_t)length_ptr);

	if((length_ptr == strlen(CMD_ENABLED_STR)) && (0 == memcmp(data_ptr, CMD_ENABLED_STR, strlen(CMD_ENABLED_STR))))
	{
		*dest = TRUE;
		ret = CMD_RSP_OK;
	}
	else if((length_ptr == strlen(CMD_DISABLED_STR)) && (0 == memcmp(data_ptr, CMD_DISABLED_STR, strlen(CMD_DISABLED_STR))))
	{
		*dest = FALSE;
		ret = CMD_RSP_OK;
	}
	else
	{
		ret = CMD_RSP_ERR_INVALID_PARAM;
	}

	return ret;
}

uint16_t uint8_array_to_hex_string(uint8_t* src, uint16_t len, uint8_t* dest, uint16_t size)
{
	uint16_t used_bytes = 0;
    char* data = NULL;

    uint8_t idx;

    if ((NULL != dest) && (0 < size))
    {
		data = (char*)dest;

		for (idx = 0; idx < len; idx++)
		{
			/* At least have space left for "0xHH" string */
			if (size >= 4)
			{
				/* At least have space left for ",0xHH" string */
				if ((idx != 0) && (size >= 5))
				{
					/* 5 chars will be used */
					size -= 5u;

					*data++ = ',';
				}
				else
				{
					/* 4 chars will be used */
					size -= 4u;
				}

				*data++ = '0';
				*data++ = 'x';
				data = uint8_to_hex_ascii_incremented_ptr(data, *src++);
			}
		}

		*data++ = '\0';

		used_bytes = (uint16_t)((void*)data - (void*)dest);
    }

    return used_bytes;
}
