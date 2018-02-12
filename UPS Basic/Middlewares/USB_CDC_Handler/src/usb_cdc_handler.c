/*****************************************************************************//**
 * @file    usb_cdc_handler.c
 * @brief   Brief description of the file
 * @author  Hugo Arganda
 * @date    Apr 26, 2017
 * @version 1.0
 *****************************************************************************/

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "usb_cdc_handler.h"
#include "usbd_cdc_if.h"
#include "usb_device.h"
#include "freertos.h"
#include "utils.h"
#include "sprintf.h"

/*****************************************************************************
 * Macros
 *****************************************************************************/

#define MAX_PRINT_LEN 512u

/*****************************************************************************
 * Type and Constant Definitions
 *****************************************************************************/

/*****************************************************************************
 * Global Declarations
 *****************************************************************************/

/*****************************************************************************
 * Static Declarations
 *****************************************************************************/

volatile unsigned int usbsem_accept = 0;
volatile unsigned int usbsem_timeout = 0;
volatile unsigned int usbtx_reject1 = 0;
volatile unsigned int usbtx_reject2 = 0;
volatile unsigned int usbtx_nordy = 0;

volatile uint8_t txholdbuf[MAX_PRINT_LEN]; /* this exists so we can exit the routine during HW xfer */

/*****************************************************************************
 * Private Function Prototypes
 *****************************************************************************/

static USBD_StatusTypeDef usb_transmit(uint32_t wait_msec, uint8_t* src, uint16_t len);

/*****************************************************************************
 * Private Function Implementations
 *****************************************************************************/

uint8_t usb_ready(void)
{
	uint8_t ret = FALSE;

    if( (hUsbDeviceFS.dev_address != 0) && (hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED) )
    {
        ret = TRUE;
    }
    else
    {
        usbtx_nordy++;
    }

    return ret;
}

static USBD_StatusTypeDef usb_transmit(uint32_t wait_msec, uint8_t* src, uint16_t len)
{
    USBD_StatusTypeDef status = USBD_BUSY;
    uint8_t retries;

    if ((pdTRUE == usb_ready()) && (NULL != src))
    {
		/* Truncate length */
		if (MAX_PRINT_LEN < len)
		{
			len = MAX_PRINT_LEN;
		}

//		if (osOK == osSemaphoreWait(usbTxSemaphoreHandle, wait_msec))
		{
			/* Set buffer data */
			memcpy((uint8_t*) &txholdbuf[0], src, len);

			for (retries = 0; (retries < 3) && (status == USBD_BUSY); retries++)
			{
				if(0 == ((USBD_CDC_HandleTypeDef*)(hUsbDeviceFS.pClassData))->TxState)
				{
//					taskENTER_CRITICAL();
					status = CDC_Transmit_FS((uint8_t*) &txholdbuf[0], (uint16_t) len);
//					taskEXIT_CRITICAL();

					if (USBD_OK == status)
					{
						usbsem_accept++;
					}
					else
					{
						usbtx_reject1++;
					}
				}
				else
				{
					/* Wait before retry */
					osDelay(1);
				}
			}

			if (USBD_OK != status)
			{
				/* problem with USB! USB should be in sync with mutex */
				usbtx_reject2++;
//				osSemaphoreRelease(usbTxSemaphoreHandle);
			}
		}
//		else
//		{
//			usbsem_timeout++;
//		}
	}

    return status;
}

/*****************************************************************************
 * Public Function Implementations
 *****************************************************************************/

uint16_t usb_cdc_print(uint32_t wait_msec, uint8_t* src)
{
	uint16_t len = 0;
	if(NULL != src)
	{
		len = usb_cdc_write(wait_msec, src, (uint16_t)strlen(src));
	}
	return len;
}

uint16_t usb_cdc_println(uint32_t wait_msec, uint8_t* src)
{
	uint16_t len = 0;
	if(NULL != src)
	{
		len += usb_cdc_write(wait_msec, src, (uint16_t)strlen(src));
	}

	len += usb_cdc_write(wait_msec, "\r\n", 2u);

	return len;
}

uint16_t usb_cdc_printf(uint32_t wait_msec, uint8_t* fmt, ...)
{
    va_list  args;
    char fmt_string[MAX_PRINT_LEN];
    uint16_t len = 0;

    va_start(args, fmt);
    len = (uint16_t)tfp_vsnprintf(fmt_string, MAX_PRINT_LEN, (char*)fmt, args);
    va_end(args);

    if(USBD_OK != usb_transmit(wait_msec, (uint8_t*)fmt_string, len))
    {
        len = 0;
    }

    return len;
}

uint16_t usb_cdc_printfln(uint32_t wait_msec, uint8_t* fmt, ...)
{
    va_list  args;
    char fmt_string[MAX_PRINT_LEN];
    uint16_t len = 0;

    va_start(args, fmt);
    len = (uint16_t)tfp_vsnprintfln(fmt_string, MAX_PRINT_LEN, (char*)fmt, args);
    va_end(args);

    if(USBD_OK != usb_transmit(wait_msec, (uint8_t*)fmt_string, len))
    {
        len = 0;
    }

    return len;
}

uint16_t usb_cdc_write(uint32_t wait_msec, uint8_t* src, uint16_t len)
{
    if(USBD_OK != usb_transmit(wait_msec, (uint8_t*)src, len))
    {
        len = 0;
    }

    return len;
}
