/*
 * usb_hid_keyboard_to_ascii.h
 *
 *  Created on: 11/02/2018
 *      Author: Argandas
 */

#ifndef USB_HID_KEYBOARD_TO_ASCII_H_
#define USB_HID_KEYBOARD_TO_ASCII_H_

#include "stm32f4xx_hal.h"
#include "usb_hid_keyboard.h"

typedef struct {
	char ascii;
	uint8_t hid_modifier;
	uint8_t hid_key;
} keyboard_HID2ASCII_t;

void usb_hid_keyboard_send_char(char data);
void usb_hid_keyboard_send_string(char* data);

#endif /* USB_HID_KEYBOARD_TO_ASCII_H_ */
