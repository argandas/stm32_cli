/*****************************************************************************//**
 * @file    command_handler.c
 * @brief   Brief description of the file
 * @author  Hugo Arganda
 * @date    Feb 9, 2018
 * @version 1.0
 *****************************************************************************/

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "command_handler.h"
#include "command_handler_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stm32f401xe.h"

#include "utils.h"
#include "console.h"

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

static uint8_t get_command_index(uint16_t* idx, const char* cmd_ptr, uint16_t len);
static uint8_t count_command_params(const char* cmd_ptr, uint16_t len, uint8_t expected);
static uint8_t execute_command_callback(uint16_t idx, const char* cmd_ptr, uint16_t len);

/*****************************************************************************
 * Private Function Implementations
 *****************************************************************************/

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
static uint8_t get_command_index(uint16_t* idx, const char* cmd_ptr, uint16_t len)
{
	cmd_response_t ret = CMD_RSP_INVALID;
    uint16_t index = 0;

#if CMD_HANDLER_SEARCH_BY_INDEX == TRUE
    uint8_t num_chars = 0;
    char* space = NULL;
#endif

	uint16_t common_total = cmd_handlers_common_table_size();

#if CMD_HANDLER_SEARCH_BY_CMD == TRUE
	cmd_handler_t* common_table = (cmd_handler_t*)cmd_handlers_common_table();
#endif

	/* Set invalid index value */
	*idx = 0;

    if ((NULL != cmd_ptr) && (0 < len))
    {
#if CMD_HANDLER_SEARCH_BY_INDEX == TRUE

    	/* Search command match by index number */
        space = strchr(cmd_ptr, ' ');

        /* If space found AND is inside the command */
        if((NULL != space) && (space < (cmd_ptr+len)))
        {
            num_chars = (uint8_t)(space - cmd_ptr);
        }
        /* No space found, command might not have any arguments */
        else
        {
            num_chars = (uint8_t)len;
        }

        if (TRUE == ascii_to_uint16(&index, (char*)cmd_ptr, num_chars, UTIL_DEC_STRING_FORMAT))
        {
        	/* Try first with common commands */
            if((0 < index) && (index <= common_total))
            {
                *idx = (uint16_t)(index - 1);
                ret = CMD_RSP_OK;
            }
            /* Else index is invalid */
			else
			{
				ret = CMD_RSP_ERR_INVALID_IDX;
			}
        }
#endif

#if CMD_HANDLER_SEARCH_BY_CMD == TRUE
        if (CMD_RSP_INVALID == ret)
        {
        	/* Search command match by command string */

        	/* Try first with common commands */
        	for (index = 0; index < common_total; index++)
			{
        		if(common_table[index].cmd_len <= len)
        		{
					if(0 == memcmp(cmd_ptr, common_table[index].cmd, common_table[index].cmd_len))
					{
						*idx = index;
						ret = CMD_RSP_OK;
						break;
					}
        		}
			}
    	}
#endif

		if (CMD_RSP_INVALID == ret)
		{
			ret = CMD_RSP_ERR_UNKNOWN_CMD;
		}
    }
    else
    {
        ret = CMD_RSP_ERR_NULL_PTR;
    }

    return ret;
}


/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
static uint8_t execute_command_callback(uint16_t idx, const char* cmd_ptr, uint16_t len)
{
	cmd_response_t ret = CMD_RSP_INVALID;

	/* Index shall be bigger than zero and lower than cmd_handlers_common_table_size() */
	if((0 <= idx) && (idx < cmd_handlers_common_table_size()))
	{
#if 0
		/* Index is valid, print command name */
		cli_printfln("Command: \"%s\"", cmd_handlers_common_table()[idx].cmd_desc);
#endif
		/* Check for number of parameters */
		ret = count_command_params(cmd_ptr, len, cmd_handlers_common_table()[idx].num_params);
		if(CMD_RSP_OK == ret)
		{
			ret = cmd_handlers_common_table()[idx].callback((char*)cmd_ptr, len);
		}
	}
	else
	{
		ret = CMD_RSP_ERR_INVALID_IDX;
	}

	return ret;
}

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
static uint8_t count_command_params(const char	* cmd_ptr, uint16_t len, uint8_t expected)
{
	cmd_response_t ret = CMD_RSP_INVALID;
    uint8_t num_params = 0;
    char* last_comma = NULL;
    char* next_comma = NULL;

    char* limit = (char*)cmd_ptr + len;

    if ((NULL != cmd_ptr) && (0 < len))
    {
        /* First parameter is located after the space uint8_t ' ' */
        last_comma = strchr((char*)cmd_ptr, ' ');

        /* Look for commas, each parameter is delimited by a comma */
        for (num_params = 0; (NULL != last_comma) && (last_comma < limit); num_params++)
        {
            next_comma = strchr(last_comma+1, ',');
            last_comma = next_comma;
        }

        /* Validate number of parameters */
        if(num_params == expected)
        {
            ret = CMD_RSP_OK;
        }
        else
        {
            ret = CMD_RSP_ERR_MISMATCHING_PARAMS;
        }
    }
    else
    {
        ret = CMD_RSP_ERR_NULL_PTR;
    }

    return ret;
}

/*****************************************************************************
 * Public Function Implementations
 *****************************************************************************/

void handle_complete_command(uint8_t* cmd_ptr, uint16_t len)
{
	cmd_response_t ret = CMD_RSP_INVALID;
    uint16_t idx = 0; /* Initialize index to a known value to avoid issues */

    /* Check if index exists */
	ret = get_command_index(&idx, (char*)cmd_ptr, len);
	if(CMD_RSP_OK == ret)
	{
		/* Execute command */
		ret = execute_command_callback(idx, (char*)cmd_ptr, len);
	}

	response_print(ret);
}
