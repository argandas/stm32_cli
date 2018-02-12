/*
 * usb_hid_keyboard_keys.h
 *
 *  Created on: 11/02/2018
 *      Author: Argandas
 */

#ifndef USB_HID_KEYBOARD_KEYS_H_
#define USB_HID_KEYBOARD_KEYS_H_

/* USB HID Keyboard - Void */
#define USB_HID_KEY_NONE 0x00
#define USB_HID_MOD_NONE 0x00

/* USB HID Keyboard - Modifiers */
#define USB_HID_MOD_LEFT_CTRL   0x01
#define USB_HID_MOD_LEFT_SHIFT  0x02
#define USB_HID_MOD_LEFT_ALT    0x04
#define USB_HID_MOD_LEFT_GUI    0x08 // (Win/Apple/Meta)
#define USB_HID_MOD_RIGHT_CTRL  0x10
#define USB_HID_MOD_RIGHT_SHIFT 0x20
#define USB_HID_MOD_RIGHT_ALT   0x40
#define USB_HID_MOD_RIGHT_GUI   0x80

/* USB HID Keyboard - Letters */
#define USB_HID_KEY_A  0x04
#define USB_HID_KEY_B  0x05
#define USB_HID_KEY_C  0x06
#define USB_HID_KEY_D  0x07
#define USB_HID_KEY_E  0x08
#define USB_HID_KEY_F  0x09
#define USB_HID_KEY_G  0x0A
#define USB_HID_KEY_H  0x0B
#define USB_HID_KEY_I  0x0C
#define USB_HID_KEY_J  0x0D
#define USB_HID_KEY_K  0x0E
#define USB_HID_KEY_L  0x0F
#define USB_HID_KEY_M  0x10
#define USB_HID_KEY_N  0x11
#define USB_HID_KEY_O  0x12
#define USB_HID_KEY_P  0x13
#define USB_HID_KEY_Q  0x14
#define USB_HID_KEY_R  0x15
#define USB_HID_KEY_S  0x16
#define USB_HID_KEY_T  0x17
#define USB_HID_KEY_U  0x18
#define USB_HID_KEY_V  0x19
#define USB_HID_KEY_W  0x1A
#define USB_HID_KEY_X  0x1B
#define USB_HID_KEY_Y  0x1C
#define USB_HID_KEY_Z  0x1D

/* USB HID Keyboard - Numbers */
#define USB_HID_KEY_1  0x1E
#define USB_HID_KEY_2  0x1F
#define USB_HID_KEY_3  0x20
#define USB_HID_KEY_4  0x21
#define USB_HID_KEY_5  0x22
#define USB_HID_KEY_6  0x23
#define USB_HID_KEY_7  0x24
#define USB_HID_KEY_8  0x25
#define USB_HID_KEY_9  0x26
#define USB_HID_KEY_0  0x27

/* USB HID Keyboard - Control Pad (CP) */
#define USB_HID_KEY_CP_INS    0x49
#define USB_HID_KEY_CP_HOME   0x4A
#define USB_HID_KEY_CP_PGUP   0x4B
#define USB_HID_KEY_CP_DEL    0x4C
#define USB_HID_KEY_CP_END    0x4D
#define USB_HID_KEY_CP_PGDN   0x4E
#define USB_HID_KEY_CP_RIGHT  0x4F
#define USB_HID_KEY_CP_LEFT   0x50
#define USB_HID_KEY_CP_DOWN   0x51
#define USB_HID_KEY_CP_UP     0x52

/* USB HID Keyboard - Key Pad (KP) */
#define USB_HID_KEY_KP_DIV      0x54
#define USB_HID_KEY_KP_MULT     0x55
#define USB_HID_KEY_KP_REST     0x56
#define USB_HID_KEY_KP_SUM      0x57
#define USB_HID_KEY_KP_ENTER    0x58
#define USB_HID_KEY_KP_1_END    0x59
#define USB_HID_KEY_KP_2_DOWN   0x5A
#define USB_HID_KEY_KP_3_PGDN   0x5B
#define USB_HID_KEY_KP_4_LEFT   0x5C
#define USB_HID_KEY_KP_5        0x5D
#define USB_HID_KEY_KP_6_RIGHT  0x5E
#define USB_HID_KEY_KP_7_HOME   0x5F
#define USB_HID_KEY_KP_8_UP     0x60
#define USB_HID_KEY_KP_9_PGUP   0x61
#define USB_HID_KEY_KP_0_INS    0x62
#define USB_HID_KEY_KP_DEL      0x63

/* USB HID Keyboard - Special */
#define USB_HID_KEY_ENTER       0x28
#define USB_HID_KEY_ESC         0x29
#define USB_HID_KEY_BACKSPACE   0x2A
#define USB_HID_KEY_TAB         0x2B
#define USB_HID_KEY_SPACE       0x2C
#define USB_HID_KEY_SCORE       0x2D
#define USB_HID_KEY_COMMA       0x36
#define USB_HID_KEY_PERIOD      0x37
#define USB_HID_KEY_CAPS_LOCK   0x39
#define USB_HID_KEY_PTR_SCR     0x46
#define USB_HID_KEY_SCROLL_LOCK 0x47
#define USB_HID_KEY_PAUSE_BREAK 0x48
#define USB_HID_KEY_NUM_LOCK    0x53
#define USB_HID_KEY_WIN_MENU    0x65
#define USB_HID_KEY_HELP        0x75
#define USB_HID_KEY_UNDO        0x7A
#define USB_HID_KEY_CUT         0x7B
#define USB_HID_KEY_COPY        0x7C
#define USB_HID_KEY_PASTE       0x7D

/* USB HID Keyboard - Function Keys */
#define USB_HID_KEY_F1    0x3A
#define USB_HID_KEY_F2    0x3B
#define USB_HID_KEY_F3    0x3C
#define USB_HID_KEY_F4    0x3D
#define USB_HID_KEY_F5    0x3E
#define USB_HID_KEY_F6    0x3F
#define USB_HID_KEY_F7    0x40
#define USB_HID_KEY_F8    0x41
#define USB_HID_KEY_F9    0x42
#define USB_HID_KEY_F10   0x43
#define USB_HID_KEY_F11   0x44
#define USB_HID_KEY_F12   0x45
#define USB_HID_KEY_F13   0x68
#define USB_HID_KEY_F14   0x69
#define USB_HID_KEY_F15   0x6A
#define USB_HID_KEY_F16   0x6B
#define USB_HID_KEY_F17   0x6C
#define USB_HID_KEY_F18   0x6D
#define USB_HID_KEY_F19   0x6E
#define USB_HID_KEY_F20   0x6F
#define USB_HID_KEY_F21   0x70
#define USB_HID_KEY_F22   0x71
#define USB_HID_KEY_F23   0x72
#define USB_HID_KEY_F24   0x73

#endif /* USB_HID_KEYBOARD_KEYS_H_ */
