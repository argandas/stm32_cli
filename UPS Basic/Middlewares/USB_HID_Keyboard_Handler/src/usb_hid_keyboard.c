/*
 * usb_hid_keyboard.c
 *
 *  Created on: 11/02/2018
 *      Author: Argandas
 */

#include "usb_hid_keyboard.h"
#include "usb_device.h"
#include "usbd_hid.h"

usb_hid_keyboard_t usb_hid_keyboard;

uint8_t usb_hid_keyboard_press_key(uint8_t mod, uint8_t key)
{
	uint8_t ret = 0;

	usb_hid_keyboard.report_id = 0x01;
	usb_hid_keyboard.modifier = mod;
	usb_hid_keyboard.key_data[0] = key;
	usb_hid_keyboard.key_data[1] = USB_HID_KEY_NONE;
	usb_hid_keyboard.key_data[2] = USB_HID_KEY_NONE;
	usb_hid_keyboard.key_data[3] = USB_HID_KEY_NONE;
	usb_hid_keyboard.key_data[4] = USB_HID_KEY_NONE;

    if (USBD_OK == USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&usb_hid_keyboard, sizeof(usb_hid_keyboard_t)))
    {
    	ret = 1;
		HAL_Delay(30);
    }

    return ret;
}

uint8_t usb_hid_keyboard_release_key(uint8_t mod, uint8_t key)
{
	uint8_t ret = 0;

	usb_hid_keyboard.report_id = 0x01;
	usb_hid_keyboard.modifier = USB_HID_MOD_NONE;
	usb_hid_keyboard.key_data[0] = USB_HID_KEY_NONE;
	usb_hid_keyboard.key_data[1] = USB_HID_KEY_NONE;
	usb_hid_keyboard.key_data[2] = USB_HID_KEY_NONE;
	usb_hid_keyboard.key_data[3] = USB_HID_KEY_NONE;
	usb_hid_keyboard.key_data[4] = USB_HID_KEY_NONE;

    if (USBD_OK == USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&usb_hid_keyboard, sizeof(usb_hid_keyboard_t)))
    {
    	ret = 1;
		HAL_Delay(30);
    }

    return ret;
}

uint8_t usb_hid_keyboard_press_and_release_key(uint8_t mod, uint8_t key)
{
	uint8_t ret = 0;

	ret = usb_hid_keyboard_press_key(mod, key);
	ret &= usb_hid_keyboard_release_key(mod, key);

    return ret;
}
