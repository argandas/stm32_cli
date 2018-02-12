/*****************************************************************************//**
 * @file    usart_handler.c
 * @brief   Brief description of the file
 * @author  Hugo Arganda (harganda)
 * @author  Luis Ramirez (lramirez)
 * @date    Feb 23, 2017
 * @version 1.0
 *****************************************************************************/

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "usart_handler.h"
#include "stm32f4xx_hal_uart.h"
#include "freertos.h"
#include <string.h>
#include "console.h"
#include "cmsis_os.h"

/*****************************************************************************
 * Macros
 *****************************************************************************/

#define MAX_PRINT_LEN 512u

/*****************************************************************************
 * Type and Constant Definitions
 *****************************************************************************/

typedef struct {
	UART_HandleTypeDef* last_err_src;
	uint32_t last_err_code;
	uint32_t err_cnt;
} uart_error_handler_t;

/*****************************************************************************
 * Global Declarations
 *****************************************************************************/

volatile uart_error_handler_t error_scratchpad = {NULL, 0, 0};

/*****************************************************************************
 * Static Declarations
 *****************************************************************************/

/*****************************************************************************
 * Private Function Prototypes
 *****************************************************************************/

static void uart_handle_errors(UART_HandleTypeDef *huart);
static uint16_t uart_transmit(UART_HandleTypeDef *huart, uint32_t wait_msec, uint8_t* src, uint16_t len);

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
static void uart_handle_errors(UART_HandleTypeDef *huart)
{
	error_scratchpad.last_err_code = HAL_UART_GetError(huart);;
	error_scratchpad.last_err_src = huart;

	error_scratchpad.err_cnt++;
}

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
static uint16_t uart_transmit(UART_HandleTypeDef *huart, uint32_t timeout, uint8_t* src, uint16_t len)
{
    uint16_t bytes_sent = 0;
    HAL_StatusTypeDef status = HAL_ERROR;
    HAL_UART_StateTypeDef uart_state;
	uint32_t Tickstart = HAL_GetTick();

    if ((NULL != huart) && (NULL != src) && (0 < len))
    {
		uart_state = HAL_UART_GetState(huart);

		if(uart_state != HAL_UART_STATE_RESET)
		{
			/* Truncate to Max Length */
			if (MAX_PRINT_LEN < len)
			{
				len = MAX_PRINT_LEN;
			}

			for(status = HAL_BUSY; HAL_BUSY == status;)
			{
				portDISABLE_INTERRUPTS();
				status = HAL_UART_Transmit_DMA(huart, (uint8_t*)src, len);
				portENABLE_INTERRUPTS();

				if (HAL_OK == status)
				{
					/* DMA was successful, wait for it to finish */
					for(status = HAL_BUSY; (HAL_BUSY == status);)
					{
						/* Check for the timeout */
						uart_state = HAL_UART_GetState(huart);
						if (timeout != HAL_MAX_DELAY)
						{
							if((uart_state != HAL_UART_STATE_BUSY_TX) && (uart_state != HAL_UART_STATE_BUSY_TX_RX))
							{
								bytes_sent = (uint16_t)(huart->TxXferSize - huart->TxXferCount);
								status = HAL_OK;
							}
							else if ((timeout == 0U) || ((HAL_GetTick() - Tickstart) > timeout))
							{
								status = HAL_TIMEOUT;
							}
						}
						osDelay(1);
					}
				}
				/* HAL_BUSY? */
				else if (HAL_BUSY == status)
				{
					if ((timeout == 0U) || ((HAL_GetTick() - Tickstart) > timeout))
					{
						status = HAL_TIMEOUT;
					}
				}
				/* HAL_ERROR or HAL_TIMEOUT */
				else
				{
					bytes_sent = 0;
					/* Do nothing */
				}
			}

		}
    }

    return bytes_sent;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Dummy analysis of sent data, this can be used for asynchronous validation of data sent */

	uint16_t size = huart->TxXferSize;
	uint16_t count = huart->TxXferCount;

	if (size == count)
	{
		// Error
		size = 0;
		return;
	}
}

/*****************************************************************************
 * Public Function Implementations
 *****************************************************************************/

uint8_t uart_init (UART_HandleTypeDef *huart, uint8_t* dest, uint16_t size)
{
	uint8_t ret1 = FALSE;
	uint8_t ret2 = FALSE;

	HAL_UART_StateTypeDef uart_status;

	if((NULL != huart) && (NULL != dest))
	{
		/* Enable UART */

		uart_status = HAL_UART_GetState(huart);

		/* UART HAL is not initialized */
		if (HAL_UART_STATE_RESET == uart_status)
		{
			if (HAL_OK == HAL_UART_Init(huart))
			{
				/* UART was initialized */
				ret1 = TRUE;
			}
		}
		/* UART HAL was already initialized, and no errors present */
		else if ((HAL_UART_STATE_TIMEOUT != uart_status) && (HAL_UART_STATE_ERROR != uart_status))
		{
			ret1 = TRUE;
		}

		/* Enable UART Rx ISR */
		if (TRUE == uart_receive_it(huart, dest, size))
		{
			/* UART Rx ISR was initialized */
			ret2 = TRUE;
		}
	}

    return (ret1 && ret2);
}

uint8_t uart_deinit (UART_HandleTypeDef *huart)
{
	if (HAL_UART_STATE_RESET != HAL_UART_GetState(huart))
	{
		HAL_UART_AbortReceive_IT(huart);
		HAL_UART_DeInit(huart);
	}
	return TRUE;
}

uint16_t uart_print(UART_HandleTypeDef *huart, uint32_t wait_msec, uint8_t* src)
{
	return uart_write(huart, wait_msec, src, (uint16_t)strlen((char*)src));
}

uint16_t uart_println(UART_HandleTypeDef *huart, uint32_t wait_msec, uint8_t* src)
{
	uint16_t len = 0;
	len = uart_write(huart, wait_msec, src, (uint16_t)strlen((char*)src));
	len = (uint16_t)(len + uart_write(huart, wait_msec, "\r\n", 2));
	return len;
}

uint16_t uart_printf(UART_HandleTypeDef *huart, uint32_t wait_msec, uint8_t* fmt, ...)
{
    va_list  args;
    char fmt_string[MAX_PRINT_LEN];
    uint16_t len = 0;

	va_start(args, fmt);
	len = (uint16_t)tfp_vsnprintf(fmt_string, MAX_PRINT_LEN, (char*)fmt, args);
	va_end(args);

    return uart_transmit(huart, wait_msec, (uint8_t*)fmt_string, len);
}

uint16_t uart_printfln(UART_HandleTypeDef *huart, uint32_t wait_msec, uint8_t* fmt, ...)
{
    va_list  args;
    char fmt_string[MAX_PRINT_LEN];
    uint16_t len = 0;

	va_start(args, fmt);
	len = (uint16_t)tfp_vsnprintfln(fmt_string, MAX_PRINT_LEN, (char*)fmt, args);
	va_end(args);

    return uart_transmit(huart, wait_msec, (uint8_t*)fmt_string, len);
}

uint16_t uart_write(UART_HandleTypeDef *huart, uint32_t wait_msec, uint8_t* src, uint16_t len)
{
	return uart_transmit(huart, wait_msec, src, len);
}

uint8_t uart_receive_it(UART_HandleTypeDef *huart, uint8_t* dest, uint16_t size)
{
	uint8_t ret = TRUE;

	/* If IT is not already enabled */
	if((huart->RxState != HAL_UART_STATE_BUSY_RX) && (huart->RxState != HAL_UART_STATE_BUSY_TX_RX))
	{
		/* Be sure IRQ is enabled for Modem */
		if (HAL_OK != HAL_UART_Receive_IT(huart, dest, size))
		{
			ret = FALSE;
		}
	}

	return ret;
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	uint32_t err_code = HAL_UART_GetError(huart);

	uart_handle_errors(huart);

	/* Check for errors */
	if (HAL_UART_ERROR_NONE != err_code)
	{
		/* Handle errors */
		if(0 < (err_code & HAL_UART_ERROR_PE))
		{
			__HAL_UART_CLEAR_PEFLAG(huart);
		}
		else if(0 < (err_code & HAL_UART_ERROR_NE))
		{
			__HAL_UART_CLEAR_NEFLAG(huart);
		}
		else if(0 < (err_code & HAL_UART_ERROR_FE))
		{
			__HAL_UART_CLEAR_FEFLAG(huart);
		}
		else if(0 < (err_code & HAL_UART_ERROR_ORE))
		{
			__HAL_UART_CLEAR_OREFLAG(huart);
		}
		else if(0 < (err_code & HAL_UART_ERROR_DMA))
		{
			/* TBD */
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (HAL_UART_ERROR_NONE != HAL_UART_GetError(huart))
    {
        uart_handle_errors(huart);
    }

    cli_data_uart_callback(huart);
}
