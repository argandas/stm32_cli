/*
 * usb_hid_keyboard.h
 *
 *  Created on: 11/02/2018
 *      Author: Argandas
 */

#ifndef USB_HID_KEYBOARD_H_
#define USB_HID_KEYBOARD_H_

#include "stm32l4xx_hal.h"
#include "usb_hid_keyboard_keys.h"

typedef struct {
	uint8_t report_id;
	uint8_t modifier;
	uint8_t OEM;
	uint8_t key_data[5];
} usb_hid_keyboard_t;

uint8_t usb_hid_keyboard_press_key(uint8_t mod, uint8_t key);
uint8_t usb_hid_keyboard_release_key(uint8_t mod, uint8_t key);
uint8_t usb_hid_keyboard_press_and_release_key(uint8_t mod, uint8_t key);

// 1. Replace content for HID_MOUSE_ReportDesc
// 2. Change inside USBD_HID_CfgDesc nInterfaceProtocol to Keyboard (1)

//__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE]  __ALIGN_END =
//{
//		0x05 ,//bSize: 0x01, bType: Global, bTag: Usage Page
//		0x01 ,//Usage Page(Generic Desktop Controls )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x06 ,//Usage(Keyboard)
//		0xA1 ,//bSize: 0x01, bType: Main, bTag: Collection
//		0x01 ,//Collection(Application )
//		0x85 ,//bSize: 0x01, bType: Global, bTag: Report ID
//		0x01 ,//Report ID(0x1 )
//		0x05 ,//bSize: 0x01, bType: Global, bTag: Usage Page
//		0x07 ,//Usage Page(Keyboard/Keypad )
//		0x19 ,//bSize: 0x01, bType: Local, bTag: Usage Minimum
//		0xE0 ,//Usage Minimum(0xE0 )
//		0x29 ,//bSize: 0x01, bType: Local, bTag: Usage Maximum
//		0xE7 ,//Usage Maximum(0xE7 )
//		0x15 ,//bSize: 0x01, bType: Global, bTag: Logical Minimum
//		0x00 ,//Logical Minimum(0x0 )
//		0x25 ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
//		0x01 ,//Logical Maximum(0x1 )
//		0x75 ,//bSize: 0x01, bType: Global, bTag: Report Size
//		0x01 ,//Report Size(0x1 )
//		0x95 ,//bSize: 0x01, bType: Global, bTag: Report Count
//		0x08 ,//Report Count(0x8 )
//		0x81 ,//bSize: 0x01, bType: Main, bTag: Input
//		0x02 ,//Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
//		0x75 ,//bSize: 0x01, bType: Global, bTag: Report Size
//		0x08 ,//Report Size(0x8 )
//		0x95 ,//bSize: 0x01, bType: Global, bTag: Report Count
//		0x01 ,//Report Count(0x1 )
//		0x81 ,//bSize: 0x01, bType: Main, bTag: Input
//		0x01 ,//Input(Constant, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
//		0x05 ,//bSize: 0x01, bType: Global, bTag: Usage Page
//		0x07 ,//Usage Page(Keyboard/Keypad )
//		0x19 ,//bSize: 0x01, bType: Local, bTag: Usage Minimum
//		0x00 ,//Usage Minimum(0x0 )
//		0x29 ,//bSize: 0x01, bType: Local, bTag: Usage Maximum
//		0x65 ,//Usage Maximum(0x65 )
//		0x15 ,//bSize: 0x01, bType: Global, bTag: Logical Minimum
//		0x00 ,//Logical Minimum(0x0 )
//		0x25 ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
//		0x65 ,//Logical Maximum(0x65 )
//		0x75 ,//bSize: 0x01, bType: Global, bTag: Report Size
//		0x08 ,//Report Size(0x8 )
//		0x95 ,//bSize: 0x01, bType: Global, bTag: Report Count
//		0x05 ,//Report Count(0x5 )
//		0x81 ,//bSize: 0x01, bType: Main, bTag: Input
//		0x00 ,//Input(Data, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
//		0xC0 ,//bSize: 0x00, bType: Main, bTag: End Collection
//		0x05 ,//bSize: 0x01, bType: Global, bTag: Usage Page
//		0x0C ,//Usage Page(Consumer )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x01 ,//Usage(Consumer Control)
//		0xA1 ,//bSize: 0x01, bType: Main, bTag: Collection
//		0x01 ,//Collection(Application )
//		0x85 ,//bSize: 0x01, bType: Global, bTag: Report ID
//		0x02 ,//Report ID(0x2 )
//		0x19 ,//bSize: 0x01, bType: Local, bTag: Usage Minimum
//		0x00 ,//Usage Minimum(0x0 )
//		0x2A ,//bSize: 0x02, bType: Local, bTag: Usage Maximum
//		0x3C,
//		0x02,//3C ,//Usage Maximum(0x23C )
//		0x15 ,//bSize: 0x01, bType: Global, bTag: Logical Minimum
//		0x00 ,//Logical Minimum(0x0 )
//		0x26 ,//bSize: 0x02, bType: Global, bTag: Logical Maximum
//		0x3C,
//		0x02,//3C ,//Logical Maximum(0x23C )
//		0x95 ,//bSize: 0x01, bType: Global, bTag: Report Count
//		0x01 ,//Report Count(0x1 )
//		0x75 ,//bSize: 0x01, bType: Global, bTag: Report Size
//		0x10 ,//Report Size(0x10 )
//		0x81 ,//bSize: 0x01, bType: Main, bTag: Input
//		0x00 ,//Input(Data, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
//		0xC0 ,//bSize: 0x00, bType: Main, bTag: End Collection
//		0x05 ,//bSize: 0x01, bType: Global, bTag: Usage Page
//		0x01 ,//Usage Page(Generic Desktop Controls )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x80 ,//Usage(System Control)
//		0xA1 ,//bSize: 0x01, bType: Main, bTag: Collection
//		0x01 ,//Collection(Application )
//		0x85 ,//bSize: 0x01, bType: Global, bTag: Report ID
//		0x03 ,//Report ID(0x3 )
//		0x19 ,//bSize: 0x01, bType: Local, bTag: Usage Minimum
//		0x81 ,//Usage Minimum(0x81 )
//		0x29 ,//bSize: 0x01, bType: Local, bTag: Usage Maximum
//		0x83 ,//Usage Maximum(0x83 )
//		0x15 ,//bSize: 0x01, bType: Global, bTag: Logical Minimum
//		0x00 ,//Logical Minimum(0x0 )
//		0x25 ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
//		0x01 ,//Logical Maximum(0x1 )
//		0x75 ,//bSize: 0x01, bType: Global, bTag: Report Size
//		0x01 ,//Report Size(0x1 )
//		0x95 ,//bSize: 0x01, bType: Global, bTag: Report Count
//		0x03 ,//Report Count(0x3 )
//		0x81 ,//bSize: 0x01, bType: Main, bTag: Input
//		0x02 ,//Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
//		0x95 ,//bSize: 0x01, bType: Global, bTag: Report Count
//		0x05 ,//Report Count(0x5 )
//		0x81 ,//bSize: 0x01, bType: Main, bTag: Input
//		0x01 ,//Input(Constant, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field)
//		0xC0 ,//bSize: 0x00, bType: Main, bTag: End Collection
//		0x06 ,//bSize: 0x02, bType: Global, bTag: Usage Page
//		0x01,
//		0xFF, //01 ,//Usage Page(Undefined )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x01 ,//Usage(1)
//		0xA1 ,//bSize: 0x01, bType: Main, bTag: Collection
//		0x01 ,//Collection(Application )
//		0x85 ,//bSize: 0x01, bType: Global, bTag: Report ID
//		0x04 ,//Report ID(0x4 )
//		0x95 ,//bSize: 0x01, bType: Global, bTag: Report Count
//		0x01 ,//Report Count(0x1 )
//		0x75 ,//bSize: 0x01, bType: Global, bTag: Report Size
//		0x08 ,//Report Size(0x8 )
//		0x15 ,//bSize: 0x01, bType: Global, bTag: Logical Minimum
//		0x01 ,//Logical Minimum(0x1 )
//		0x25 ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
//		0x0A ,//Logical Maximum(0xA )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x20 ,//Usage(32)
//		0xB1 ,//bSize: 0x01, bType: Main, bTag: Feature
//		0x03 ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x23 ,//Usage(35)
//		0xB1 ,//bSize: 0x01, bType: Main, bTag: Feature
//		0x03 ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
//		0x25 ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
//		0x4F ,//Logical Maximum(0x4F )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x21 ,//Usage(33)
//		0xB1 ,//bSize: 0x01, bType: Main, bTag: Feature
//		0x03 ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
//		0x25 ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
//		0x30 ,//Logical Maximum(0x30 )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x22 ,//Usage(34)
//		0xB1 ,//bSize: 0x01, bType: Main, bTag: Feature
//		0x03 ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
//		0x95 ,//bSize: 0x01, bType: Global, bTag: Report Count
//		0x03 ,//Report Count(0x3 )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x24 ,//Usage(36)
//		0xB1 ,//bSize: 0x01, bType: Main, bTag: Feature
//		0x03 ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
//		0xC0 ,//bSize: 0x00, bType: Main, bTag: End Collection
//		0x06 ,//bSize: 0x02, bType: Global, bTag: Usage Page
//		0x01,
//		0xFF,//01 ,//Usage Page(Undefined )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x01 ,//Usage(1)
//		0xA1 ,//bSize: 0x01, bType: Main, bTag: Collection
//		0x01 ,//Collection(Application )
//		0x85 ,//bSize: 0x01, bType: Global, bTag: Report ID
//		0x05 ,//Report ID(0x5 )
//		0x95 ,//bSize: 0x01, bType: Global, bTag: Report Count
//		0x01 ,//Report Count(0x1 )
//		0x75 ,//bSize: 0x01, bType: Global, bTag: Report Size
//		0x08 ,//Report Size(0x8 )
//		0x15 ,//bSize: 0x01, bType: Global, bTag: Logical Minimum
//		0x01 ,//Logical Minimum(0x1 )
//		0x25 ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
//		0x0A ,//Logical Maximum(0xA )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x20 ,//Usage(32)
//		0xB1 ,//bSize: 0x01, bType: Main, bTag: Feature
//		0x03 ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x23 ,//Usage(35)
//		0xB1 ,//bSize: 0x01, bType: Main, bTag: Feature
//		0x03 ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
//		0x25 ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
//		0x4F ,//Logical Maximum(0x4F )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x21 ,//Usage(33)
//		0xB1 ,//bSize: 0x01, bType: Main, bTag: Feature
//		0x03 ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
//		0x25 ,//bSize: 0x01, bType: Global, bTag: Logical Maximum
//		0x30 ,//Logical Maximum(0x30 )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x22 ,//Usage(34)
//		0xB1 ,//bSize: 0x01, bType: Main, bTag: Feature
//		0x03 ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
//		0x95 ,//bSize: 0x01, bType: Global, bTag: Report Count
//		0x03 ,//Report Count(0x3 )
//		0x09 ,//bSize: 0x01, bType: Local, bTag: Usage
//		0x24 ,//Usage(36)
//		0xB1 ,//bSize: 0x01, bType: Main, bTag: Feature
//		0x03 ,//Feature(Constant, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field)
//		0xC0 ,//bSize: 0x00, bType: Main, bTag: End Collection
//};

#endif /* USB_HID_KEYBOARD_H_ */
