/*****************************************************************************//**
 * @file    usb_cdc_handler.h
 * @brief   Brief description of the file
 * @author  Hugo Arganda
 * @date    Apr 26, 2017
 * @version 1.0
 *****************************************************************************/

#ifndef _USB_CDC_HANDLER_H_
#define _USB_CDC_HANDLER_H_

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "stm32f4xx_hal.h"

/*****************************************************************************
 * Macros
 *****************************************************************************/

#define USB_TX_MAX_WAIT_MS 5

/*****************************************************************************
 * Type and Constant definitions
 *****************************************************************************/

/*****************************************************************************
 * Global Declarations
 *****************************************************************************/

/*****************************************************************************
 * Public Function Prototypes
 *****************************************************************************/

uint8_t usb_ready(void);

uint16_t usb_cdc_print   (uint32_t wait_msec, uint8_t* src);
uint16_t usb_cdc_println (uint32_t wait_msec, uint8_t* src);
uint16_t usb_cdc_printf  (uint32_t wait_msec, uint8_t* fmt, ...);
uint16_t usb_cdc_printfln(uint32_t wait_msec, uint8_t* fmt, ...);
uint16_t usb_cdc_write   (uint32_t wait_msec, uint8_t *src, uint16_t len);

#endif /* _USB_CDC_HANDLER_H_ */
