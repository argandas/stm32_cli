/*
 * usb_hid_keyboard_to_ascii.c
 *
 *  Created on: 11/02/2018
 *      Author: Argandas
 */

#include "usb_hid_keyboard_keys.h"
#include "usb_hid_keyboard_to_ascii.h"

static const keyboard_HID2ASCII_t usb_hid_keyboard_to_ascii_table [] = {
		{'a', USB_HID_MOD_NONE,           USB_HID_KEY_A},
		{'b', USB_HID_MOD_NONE,           USB_HID_KEY_B},
		{'c', USB_HID_MOD_NONE,           USB_HID_KEY_C},
		{'d', USB_HID_MOD_NONE,           USB_HID_KEY_D},
		{'e', USB_HID_MOD_NONE,           USB_HID_KEY_E},
		{'f', USB_HID_MOD_NONE,           USB_HID_KEY_F},
		{'g', USB_HID_MOD_NONE,           USB_HID_KEY_G},
		{'h', USB_HID_MOD_NONE,           USB_HID_KEY_H},
		{'i', USB_HID_MOD_NONE,           USB_HID_KEY_I},
		{'j', USB_HID_MOD_NONE,           USB_HID_KEY_J},
		{'k', USB_HID_MOD_NONE,           USB_HID_KEY_K},
		{'l', USB_HID_MOD_NONE,           USB_HID_KEY_L},
		{'m', USB_HID_MOD_NONE,           USB_HID_KEY_M},
		{'n', USB_HID_MOD_NONE,           USB_HID_KEY_N},
		{'o', USB_HID_MOD_NONE,           USB_HID_KEY_O},
		{'p', USB_HID_MOD_NONE,           USB_HID_KEY_P},
		{'q', USB_HID_MOD_NONE,           USB_HID_KEY_Q},
		{'r', USB_HID_MOD_NONE,           USB_HID_KEY_R},
		{'s', USB_HID_MOD_NONE,           USB_HID_KEY_S},
		{'t', USB_HID_MOD_NONE,           USB_HID_KEY_T},
		{'u', USB_HID_MOD_NONE,           USB_HID_KEY_U},
		{'v', USB_HID_MOD_NONE,           USB_HID_KEY_V},
		{'w', USB_HID_MOD_NONE,           USB_HID_KEY_W},
		{'x', USB_HID_MOD_NONE,           USB_HID_KEY_X},
		{'y', USB_HID_MOD_NONE,           USB_HID_KEY_Y},
		{'z', USB_HID_MOD_NONE,           USB_HID_KEY_Z},
		{'A', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_A},
		{'B', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_B},
		{'C', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_C},
		{'D', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_D},
		{'E', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_E},
		{'F', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_F},
		{'G', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_G},
		{'H', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_H},
		{'I', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_I},
		{'J', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_J},
		{'K', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_K},
		{'L', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_L},
		{'M', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_M},
		{'N', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_N},
		{'O', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_O},
		{'P', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_P},
		{'Q', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_Q},
		{'R', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_R},
		{'S', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_S},
		{'T', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_T},
		{'U', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_U},
		{'V', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_V},
		{'W', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_W},
		{'X', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_X},
		{'Y', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_Y},
		{'Z', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_Z},
		{'1', USB_HID_MOD_NONE,           USB_HID_KEY_1},
		{'2', USB_HID_MOD_NONE,           USB_HID_KEY_2},
		{'3', USB_HID_MOD_NONE,           USB_HID_KEY_3},
		{'4', USB_HID_MOD_NONE,           USB_HID_KEY_4},
		{'5', USB_HID_MOD_NONE,           USB_HID_KEY_5},
		{'6', USB_HID_MOD_NONE,           USB_HID_KEY_6},
		{'7', USB_HID_MOD_NONE,           USB_HID_KEY_7},
		{'8', USB_HID_MOD_NONE,           USB_HID_KEY_8},
		{'9', USB_HID_MOD_NONE,           USB_HID_KEY_9},
		{'0', USB_HID_MOD_NONE,           USB_HID_KEY_0},
		{'!', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_1},
		{'@', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_2},
		{'#', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_3},
		{'$', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_4},
		{'%', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_5},
		{'^', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_6},
		{'&', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_7},
		{'*', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_8},
		{'(', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_9},
		{')', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_0},
		{' ', USB_HID_MOD_NONE,           USB_HID_KEY_SPACE},
		{'\r', USB_HID_MOD_NONE,          USB_HID_KEY_ENTER},
		{'-', USB_HID_MOD_NONE,           USB_HID_KEY_SCORE},
		{'_', USB_HID_MOD_RIGHT_SHIFT,    USB_HID_KEY_SCORE},
};

void usb_hid_keyboard_send_char(char data)
{
	uint8_t idx;
	uint8_t found = 0;
	uint8_t len = sizeof(usb_hid_keyboard_to_ascii_table)/sizeof(usb_hid_keyboard_to_ascii_table[0]);

	uint8_t key;
	uint8_t mod;

	for (idx = 0; idx < len; idx++)
	{
		if (data == usb_hid_keyboard_to_ascii_table[idx].ascii)
		{
			found = 1;
			key = usb_hid_keyboard_to_ascii_table[idx].hid_key;
			mod = usb_hid_keyboard_to_ascii_table[idx].hid_modifier;
			break;
		}
	}

	if (1 == found)
	{
		usb_hid_keyboard_press_and_release_key(mod, key);
	}
	else
	{
		/* Send '*' for unknown characters */
		usb_hid_keyboard_press_and_release_key(USB_HID_MOD_RIGHT_SHIFT, USB_HID_KEY_8);
	}

}

void usb_hid_keyboard_send_string(char* data)
{
	uint8_t idx;
	uint8_t len = strlen(data);

	for(idx = 0; idx < len; idx++, data++)
	{
		usb_hid_keyboard_send_char(*data);
	}
}
