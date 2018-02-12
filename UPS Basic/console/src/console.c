/*****************************************************************************//**
 * @file    console.c
 * @brief   Brief description of the file
 * @author  Hugo Arganda
 * @date    May 9, 2017
 * @version 1.0
 *****************************************************************************/

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "console.h"

#include <stdint.h>
#include <string.h>

#include "cmsis_os.h"
#include "stm32f4xx_hal_def.h"

#include "usart_handler.h"
#include "usb_cdc_handler.h"

#include "sprintf.h"
#include "circ_buffers.h"

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

static uint8_t cli_uart_debug_enable = CLI_UART_DEBUG_DEFAULT_STATE;

static uint8_t cli_echo_enabled = TRUE;

char cli_fmt_buffer[CLI_FMT_BUFFER_LEN];

uint8_t cli_cir_buffer_space[CLI_CIRC_BUFFER_LEN];

static circ_buff_t cli_circ_buffer = {
		cli_cir_buffer_space,
		0,
		0,
		0,
		CLI_CIRC_BUFFER_LEN
};

/*****************************************************************************
 * Private Function Prototypes
 *****************************************************************************/

static uint16_t cli_varg_printf(const char* fmt, va_list args);

/*****************************************************************************
 * Private Function Implementations
 *****************************************************************************/

static uint16_t cli_varg_printf(const char* fmt, va_list args)
{
    uint16_t len = 0;
    if (NULL != fmt)
    {
		len = (uint16_t) tfp_vsnprintf(&cli_fmt_buffer[0], CLI_FMT_BUFFER_LEN, fmt, args);
    }
    return cli_write(&cli_fmt_buffer[0], len);
}

/*****************************************************************************
 * Public Function Implementations
 *****************************************************************************/

void cli_init(void)
{
	/* Enable UART Rx ISR */
	if (TRUE != uart_init(&CLI_UART_HANDLE, &cli_circ_buffer.__buff, 1))
	{
		/* Error */
	}

	circ_buff_reset(&cli_circ_buffer);
}

void cli_data_uart_callback(UART_HandleTypeDef *huart)
{
    if(&CLI_UART_HANDLE == huart)
    {
        /* Send received data to the parser */
    	cli_data_enqueue((uint8_t*)(huart->pRxBuffPtr - huart->RxXferSize), huart->RxXferSize);

		/* Enable ISR for UART */
		uart_receive_it(&CLI_UART_HANDLE, &cli_circ_buffer.__buff, 1);
    }
}

void cli_data_enqueue(uint8_t* src, uint16_t len)
{
    if ((NULL != src) && (0 < len))
    {
        /* Copy data to circular buffer */
    	circ_buff_write(&cli_circ_buffer, src, len);
    }
}

uint16_t cli_data_dequeue(uint8_t* dest, uint16_t len)
{
	uint16_t total = 0;
	uint8_t temp;

	for (; 0 < len; len--)
	{
		if (TRUE == circ_buff_pop(&cli_circ_buffer, &temp))
		{
			*dest++ = temp;
			total++;
		}
		else
		{
			/* No more data in the buffer */
			break;
		}
	}

	return total;
}

void cli_echo_enable(uint8_t enable)
{
	cli_echo_enabled = enable;
}

void cli_print_header(const char* fmt, ...)
{
    va_list  args;
    uint8_t len = 0;
    uint8_t spaces_before = 0;
    uint8_t spaces_after = 0;

	if(NULL != fmt)
	{
		cli_println(NULL);

		memset(&cli_fmt_buffer[0], '=', CLI_HEADER_LENGTH);
		cli_write(&cli_fmt_buffer[0], CLI_HEADER_LENGTH);

		cli_println(NULL);

		/* Format string */
		va_start(args, fmt);
		len = (uint8_t) tfp_vsnprintf(&cli_fmt_buffer[0], CLI_FMT_BUFFER_LEN, fmt, args);
		va_end(args);

		/* Calculate spaces */
		spaces_before = (uint8_t)((CLI_HEADER_LENGTH - (uint16_t)len - 2) / 2);
		spaces_after = (uint8_t)(CLI_HEADER_LENGTH - len - 2 - spaces_before);

		for(; 0 < spaces_before; spaces_before--)
		{
			cli_print("=");
		}

		cli_print(" ");
		cli_write(&cli_fmt_buffer[0], len);
		cli_print(" ");

		for(; 0 < spaces_after; spaces_after--)
		{
			cli_print("=");
		}

		cli_println(NULL);

		memset(&cli_fmt_buffer[0], '=', CLI_HEADER_LENGTH);
		cli_write(&cli_fmt_buffer[0], CLI_HEADER_LENGTH);

		cli_println(NULL);
	}
}


void cli_print_cursor(void)
{
#ifdef CLI_CURSOR_STRING
	cli_print(CLI_CURSOR_STRING);
#endif
}

void cli_print_buffer(uint8_t* buff, uint16_t len, char sep, uint8_t row)
{
	uint8_t print_sep = FALSE;

	if(NULL != buff)
	{
        uint16_t idx;

        for(idx = 0; idx < len; idx++)
        {
        	print_sep = TRUE;

    		cli_printf("%02X", *buff++);

        	if (0 < row)
        	{
				if(((idx + 1) % row) == 0)
				{
					print_sep = FALSE;
					cli_println(NULL);
				}
        	}

        	/* if index is last element, or just finished row, do not print separator */
    		if (((idx + 1) < len) && (TRUE == print_sep))
    		{
    			cli_write(&sep, 1);
    		}
        }
        cli_println(NULL);
    }
}

void cli_enable_debug(uint8_t enable)
{
	cli_uart_debug_enable = enable;
}

uint8_t cli_debug_enabled(void)
{
	return cli_uart_debug_enable;
}

uint16_t cli_print(const char* src)
{
	uint16_t len = 0;

	if(NULL != src)
	{
		len = cli_write(src, (uint16_t)strlen(src));
	}

	return len;
}

uint16_t cli_println(const char* src)
{
	uint16_t len = 0;

	len = cli_print(src);
	len = (uint16_t)(len + cli_print(CLI_EOL_STRING));

	return len;
}

uint16_t cli_printf(const char* fmt, ...)
{
    va_list  args;
    uint16_t len = 0;

    va_start(args, fmt);
    len = cli_varg_printf(fmt, args);
    va_end(args);

    return len;
}

uint16_t cli_printfln(const char* fmt, ...)
{
    va_list  args;
    uint16_t len = 0;

    va_start(args, fmt);
    len = cli_varg_printf(fmt, args);
    va_end(args);

	len = (uint16_t)(len + cli_print(CLI_EOL_STRING));

    return len;
}

uint16_t cli_write(const char* src, uint16_t len)
{
	uint16_t sent = 0;
#ifdef CLI_UART_HANDLE
	if (TRUE == cli_debug_enabled())
	{
		sent = uart_write(&CLI_UART_HANDLE, UART_TX_MAX_WAIT_MS, (uint8_t*)src, len);
	}
#endif

#if 0
	usb_cdc_write(USB_TX_MAX_WAIT_MS, (uint8_t*)src, len);
#endif
	return sent;
}
