/*****************************************************************************//**
 * usart_buffers.c
 * @brief   Brief description of the file
 * @author  Luis Ramirez (lramirez)
 * @author  Hugo Arganda (harganda)
 * @date    May 25, 2017
 * @version 1.0
 *****************************************************************************/

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "circ_buffers.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include <string.h> /* Used for memset() */

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

uint8_t circ_buff_push(circ_buff_t* cir_ptr, uint8_t data)
{
    uint8_t ret = TRUE;
    uint16_t next = 0;

    next = (uint16_t)(cir_ptr->head + 1);
    if(next >= cir_ptr->size)
    {
        next = 0;
    }

    if(next == cir_ptr->tail)
    {
        ret = FALSE;
    }
    else
    {
        cir_ptr->buffer[cir_ptr->head] = data;
        cir_ptr->head = next;
    }
    return ret;
}

uint8_t circ_buff_pop(circ_buff_t* cir_ptr, uint8_t* data)
{
    uint8_t ret = TRUE;
    uint16_t next = 0;
    if(cir_ptr->head == cir_ptr->tail)
    {
        ret = FALSE;
    }
    else
    {
        *data = cir_ptr->buffer[cir_ptr->tail];
        next = (uint16_t)(cir_ptr->tail + 1);
        if(next >= cir_ptr->size)
        {
            next = 0;
        }

        cir_ptr->tail = next;
    }
    return ret;
}

void circ_buff_reset(circ_buff_t* cir_ptr)
{
	memset(cir_ptr->buffer, 0x00, cir_ptr->size);
    cir_ptr->head = 0;
    cir_ptr->tail = 0;
}

uint8_t buff_is_empty(circ_buff_t* cir_ptr)
{
    uint8_t ret = FALSE;

    if(cir_ptr->head == cir_ptr->tail)
    {
        ret = TRUE;
    }
    return ret;
}

uint8_t circ_buff_write(circ_buff_t* cir_ptr, uint8_t* data, uint16_t len)
{
    uint8_t ret = TRUE;
    uint16_t i;

    for(i = 0; ((i < len) && (TRUE == ret)); i++)
    {
        ret = circ_buff_push(cir_ptr,*data);
        data++;
    }

    return ret;
}

uint16_t circ_buff_read(circ_buff_t* cir_ptr, uint8_t* data, uint16_t len, uint32_t timeout)
{
	uint16_t bytes_read = 0;
	uint32_t Tickstart;

    if((NULL != cir_ptr) && (NULL != data))
    {
    	Tickstart = HAL_GetTick();
		for(bytes_read = 0; (bytes_read < len);)
		{
			if(TRUE == circ_buff_pop(cir_ptr, data))
			{
				bytes_read++;
				data++;
			}
			else if (timeout != HAL_MAX_DELAY)
			{
				if ((timeout == 0U) || ((HAL_GetTick() - Tickstart) > timeout))
				{
					break;
				}
				else
				{
					osDelay(10);
				}
			}
		}
    }

    return bytes_read;
}

uint16_t circ_buff_data_length(circ_buff_t* cir_ptr)
{
    uint16_t ret = 0;

    // tail = read head = write
	if (cir_ptr->tail > cir_ptr->head)
	{
		ret = (uint16_t)((cir_ptr->size - cir_ptr->tail) + cir_ptr->head);
	}
	else
	{
		ret = (uint16_t)(cir_ptr->head - cir_ptr->tail);
	}

    return ret;
}
