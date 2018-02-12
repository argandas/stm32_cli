/*
 * usb_hid_presenter.h
 *
 *  Created on: 11/02/2018
 *      Author: Argandas
 */

#ifndef USB_HID_PRESENTER_H_
#define USB_HID_PRESENTER_H_

#include "usb_hid_keyboard.h"

#define USB_HID_PRESENTER_ACTIONS_X(id, desc, mod, key)
#define USB_HID_PRESENTER_ACTIONS_TABLE \
    /* ------------------------ Identifier, ------- "Description", ------ Modifier, --------------- Key, -------------- */\
	USB_HID_PRESENTER_ACTIONS_X(PPT_BTN_START,      "Start presentation", USB_HID_MOD_NONE,         USB_HID_KEY_F5       )\
	USB_HID_PRESENTER_ACTIONS_X(PPT_BTN_END ,       "End presentation",   USB_HID_MOD_NONE,         USB_HID_KEY_ESC      )\
	USB_HID_PRESENTER_ACTIONS_X(PPT_BTN_PREV,       "Previous Slide",     USB_HID_MOD_NONE,         USB_HID_KEY_CP_PGUP  )\
	USB_HID_PRESENTER_ACTIONS_X(PPT_BTN_NEXT,       "Next Slide",         USB_HID_MOD_NONE,         USB_HID_KEY_CP_PGDN  )\
	USB_HID_PRESENTER_ACTIONS_X(PPT_BTN_ALT_TAB,    "Alt + Tab",          USB_HID_MOD_LEFT_ALT,     USB_HID_KEY_TAB      )\
	USB_HID_PRESENTER_ACTIONS_X(PPT_BTN_BLK_SCR,    "Blank Black Slide",  USB_HID_MOD_NONE,         USB_HID_KEY_PERIOD   )\
	USB_HID_PRESENTER_ACTIONS_X(PPT_BTN_WHT_SCR,    "Blank White Slide",  USB_HID_MOD_NONE,         USB_HID_KEY_COMMA    )\
	USB_HID_PRESENTER_ACTIONS_X(PPT_BTN_MAX,        NULL,                 USB_HID_MOD_NONE,         USB_HID_KEY_NONE     )\

#undef USB_HID_PRESENTER_ACTIONS_X

#define USB_HID_PRESENTER_ACTIONS_X(id, desc, mod, key) id,
typedef enum {
	USB_HID_PRESENTER_ACTIONS_TABLE
} usb_hid_presenter_action_e;
#undef USB_HID_PRESENTER_ACTIONS_X

uint8_t usb_hid_presenter_execute(usb_hid_presenter_action_e action);
char* usb_hid_presenter_action_string(usb_hid_presenter_action_e action);

#endif /* USB_HID_PRESENTER_H_ */
