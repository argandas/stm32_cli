/*****************************************************************************//**
 * @file    cmd_parser.c
 * @brief   Command Parser
 * @author  Hugo Arganda
 * @date    May 9, 2017
 * @version 1.0
 *****************************************************************************/

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "cmd_parser.h"

#include "string.h"
#include "console.h"

#include "usb_cdc_handler.h"

/*****************************************************************************
 * Macros
 *****************************************************************************/

/*****************************************************************************
 * Type and Constant Definitions
 *****************************************************************************/

typedef enum
{
    CMD_PARSER_EXPECTING_LEAD_CR = 0,
    CMD_PARSER_EXPECTING_PAYLOAD,
} cmd_parser_state_enum_t;

typedef struct
{
	uint8_t buff[CMD_PARSER_BUFF_SIZE];
	uint16_t len;
	cmd_handler_callback handler_callback;
} scratchpad_cmd_parser_t;

/*****************************************************************************
 * Global Declarations
 *****************************************************************************/

extern void start_cmd_parser_task(void const * argument);

/*****************************************************************************
 * Static Declarations
 *****************************************************************************/

static scratchpad_cmd_parser_t cmd_parser_scratchpad;

/*****************************************************************************
 * Private Function Prototypes
 *****************************************************************************/

static void cmd_parser_reset(void);
static void echo_command(uint8_t* cmd_ptr, uint16_t len);

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
static void cmd_parser_reset(void)
{
	/* Reset parser buffer */
	memset(&cmd_parser_scratchpad.buff[0], 0, sizeof(cmd_parser_scratchpad.buff));
	cmd_parser_scratchpad.len = 0;
}

static void echo_command(uint8_t* cmd_ptr, uint16_t len)
{
	cli_printfln("Received: %s", cmd_ptr);
}

/*****************************************************************************
 * Public Function Implementations
 *****************************************************************************/

void cmd_parser_setup(void)
{
	uint32_t Tickstart = HAL_GetTick();

	for(;(usb_ready() != TRUE) && ((HAL_GetTick() - Tickstart) < 1000);)
	{
		/* Wait for USB driver */
		osDelay(10);
	}

	cli_println(NULL);
    cli_print_header("Command Parser Example");
	cli_print_cursor();

//	cmd_parser_callback_register(handle_complete_command);
	cmd_parser_callback_register(echo_command);

	cmd_parser_reset();
}

void cmd_parser_callback_register(cmd_handler_callback callback)
{
	cmd_parser_scratchpad.handler_callback = callback;
}

void cmd_parser_loop(uint8_t verbose)
{
    uint8_t curr_char = '\0';

    /* Get data from buffer */
    if (1 == cli_data_dequeue(&curr_char, 1))
    {
    	/* Handle backspace character */
    	if (('\b' == curr_char) && (0 < cmd_parser_scratchpad.len))
    	{
			/* Delete previous character */
			cmd_parser_scratchpad.len--;
			cmd_parser_scratchpad.buff[cmd_parser_scratchpad.len] = 0;

			/* Print backspace character */
			cli_printf("\b \b");
		}
    	/* Handle EOL character */
    	else if ('\r' == curr_char)
		{
    		/* String received, break to process it next */
			cli_println(NULL);
		}
		else if ('\n' == curr_char)
		{
			/* Ignore LF character */
		}
    	/* Handle payload, allow only printable characters */
		else if ((curr_char >= ' ') && (curr_char <= '~'))
		{
			/* Echo received character */
			cli_write((char*)&curr_char, 1);
	
			/* Validate buffer boundaries */
			if (cmd_parser_scratchpad.len < (sizeof(cmd_parser_scratchpad.buff) - 1))
			{
				/* Put received character at the end of the buffer */
				cmd_parser_scratchpad.buff[cmd_parser_scratchpad.len++] = curr_char;
			}
			else
			{
				/* Buffer overflow ocurred */
				/* Reset parser to avoid conflicts */
				cmd_parser_reset();
			}
		}
		else
		{
			/* Ignore received character */
		}

    	/* If data was received and CR was the latest character, process the data */
		if (('\r' == curr_char) && (0 < cmd_parser_scratchpad.len))
		{
			/* NULL terminate buffer */
			cmd_parser_scratchpad.buff[cmd_parser_scratchpad.len] = '\0';

			if (NULL != cmd_parser_scratchpad.handler_callback)
			{
				cmd_parser_scratchpad.handler_callback(&cmd_parser_scratchpad.buff[0], cmd_parser_scratchpad.len);
			}

			/* Print an extra line to improve readability */
			cli_println(NULL);

			/* Command complete --> Reset buffer */
			cmd_parser_reset();
		}

		/* Command complete OR empty, print cursor */
		if ('\r' == curr_char)
		{
			cli_print_cursor();
		}
    }
}

/* start_cmd_parser_task function */
void start_cmd_parser_task(void const * argument)
{
  cli_init();

  cmd_parser_setup();

	/* Infinite loop */
	for (;;)
	{
		/* Execute parser */
		cmd_parser_loop(TRUE);
		osDelay(1);
	}
}
