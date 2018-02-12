/*
 * usb_hid_presenter.c
 *
 *  Created on: 11/02/2018
 *      Author: Argandas
 */

#include "usb_hid_presenter.h"

typedef struct {
	char* description;
	uint8_t mod;
	uint8_t key;
} usb_hid_presenter_action_t;

#define USB_HID_PRESENTER_ACTIONS_X(id, desc, mod, key) {desc, mod, key},
usb_hid_presenter_action_t ppt_action_tables[] = {
	USB_HID_PRESENTER_ACTIONS_TABLE
};
#undef USB_HID_PRESENTER_ACTIONS_X

uint8_t usb_hid_presenter_execute(usb_hid_presenter_action_e action)
{
	uint8_t ret = 0;

	if ((0 < action) && (PPT_BTN_MAX > action))
	{
		if (0 < usb_hid_keyboard_press_and_release_key(ppt_action_tables[action].mod, ppt_action_tables[action].key))
		{
			ret = 1U;
		}
	}

	return ret;
}

char* usb_hid_presenter_action_string(usb_hid_presenter_action_e action)
{
	char* str = NULL;

	if ((0 < action) && (PPT_BTN_MAX > action))
	{
		str = ppt_action_tables[action].description;
	}

	return str;
}
