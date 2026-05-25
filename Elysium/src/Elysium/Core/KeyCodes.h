#pragma once

#define ELY_KEY_INVALID	   0xFF

#define ELY_MOUSE_BUTTON_1			0x100
#define ELY_MOUSE_BUTTON_2			0x101
#define ELY_MOUSE_BUTTON_3			0x102
#define ELY_MOUSE_BUTTON_4			0x103
#define ELY_MOUSE_BUTTON_5			0x104
#define ELY_MOUSE_BUTTON_6			0x105
#define ELY_MOUSE_BUTTON_7			0x106
#define ELY_MOUSE_BUTTON_8			0x107
#define ELY_MOUSE_WHEEL_VERTICAL    0x108
#define ELY_MOUSE_WHEEL_HORIZONTAL  0x109

#define ELY_MOUSE_BUTTON_FIRST		ELY_MOUSE_BUTTON_1
#define ELY_MOUSE_BUTTON_LAST		ELY_MOUSE_BUTTON_8
#define ELY_MOUSE_BUTTON_LEFT		ELY_MOUSE_BUTTON_1
#define ELY_MOUSE_BUTTON_RIGHT		ELY_MOUSE_BUTTON_2
#define ELY_MOUSE_BUTTON_MIDDLE		ELY_MOUSE_BUTTON_3 


#define ELY_KEY_CANCEL		   0x03

/*
 * 0x07 : reserved
 */

#define ELY_KEY_BACK           0x08
#define ELY_KEY_TAB            0x09

 /*
  * 0x0A - 0x0B : reserved
  * 0x0C : unassigned
  */

#define ELY_KEY_RETURN         0x0D

  /*
   * 0x0E - 0x0F : unassigned
   */

#define ELY_KEY_SHIFT          0x10
#define ELY_KEY_CONTROL        0x11
#define ELY_KEY_ALT            0x12
#define ELY_KEY_PAUSE          0x13
#define ELY_KEY_CAPSLOCK       0x14

/*
* 0x15 - 0x1A : unassigned
*/

#define ELY_KEY_ESCAPE		   0x1B

#define ELY_KEY_SPACE          0x20
#define ELY_KEY_PRIOR          0x21
#define ELY_KEY_NEXT           0x22
#define ELY_KEY_END            0x23
#define ELY_KEY_HOME           0x24
#define ELY_KEY_LEFT           0x25
#define ELY_KEY_UP             0x26
#define ELY_KEY_RIGHT          0x27
#define ELY_KEY_DOWN           0x28

/*
* 0x29 - 0x2B : unassigned
*/

#define ELY_KEY_PRINTSCREEN    0x2C
#define ELY_KEY_INSERT         0x2D
#define ELY_KEY_DELETE         0x2E

#define ELY_KEY_0			  0x30
#define ELY_KEY_1			  0x31
#define ELY_KEY_2             0x32
#define ELY_KEY_3			  0x33	
#define ELY_KEY_4             0x34
#define ELY_KEY_5             0x35
#define ELY_KEY_6             0x36
#define ELY_KEY_7             0x37
#define ELY_KEY_8             0x38
#define ELY_KEY_9             0x39
   /*
   * 0x3A - 0x40 : unassigned
   */
#define ELY_KEY_A             0x41
#define ELY_KEY_B             0x42
#define ELY_KEY_C             0x43
#define ELY_KEY_D             0x44
#define ELY_KEY_E             0x45
#define ELY_KEY_F             0x46
#define ELY_KEY_G             0x47
#define ELY_KEY_H             0x48
#define ELY_KEY_I             0x49    
#define ELY_KEY_J             0x4A
#define ELY_KEY_K             0x4B
#define ELY_KEY_L             0x4C
#define ELY_KEY_M             0x4D
#define ELY_KEY_N             0x4E
#define ELY_KEY_O             0x4F
#define ELY_KEY_P             0x50
#define ELY_KEY_Q             0x51
#define ELY_KEY_R             0x52
#define ELY_KEY_S             0x53
#define ELY_KEY_T             0x54
#define ELY_KEY_U             0x55
#define ELY_KEY_V             0x56
#define ELY_KEY_W             0x57
#define ELY_KEY_X             0x58
#define ELY_KEY_Y             0x59 
#define ELY_KEY_Z             0x5A

#define ELY_KEY_LSUPER           0x5B
#define ELY_KEY_RSUPER           0x5C
#define ELY_KEY_APPLICATION		 0x5D

	/*
	 * 0x5E : reserved
	 * 0x5F : unassigned
	 */

#define ELY_KEY_NUMPAD0        0x60
#define ELY_KEY_NUMPAD1        0x61
#define ELY_KEY_NUMPAD2        0x62
#define ELY_KEY_NUMPAD3        0x63
#define ELY_KEY_NUMPAD4        0x64
#define ELY_KEY_NUMPAD5        0x65
#define ELY_KEY_NUMPAD6        0x66
#define ELY_KEY_NUMPAD7        0x67
#define ELY_KEY_NUMPAD8        0x68
#define ELY_KEY_NUMPAD9        0x69
#define ELY_KEY_MULTIPLY       0x6A
#define ELY_KEY_ADD            0x6B
#define ELY_KEY_SEPARATOR      0x6C
#define ELY_KEY_SUBTRACT       0x6D
#define ELY_KEY_DECIMAL        0x6E
#define ELY_KEY_DIVIDE         0x6F
#define ELY_KEY_F1             0x70
#define ELY_KEY_F2             0x71
#define ELY_KEY_F3             0x72
#define ELY_KEY_F4             0x73
#define ELY_KEY_F5             0x74
#define ELY_KEY_F6             0x75
#define ELY_KEY_F7             0x76
#define ELY_KEY_F8             0x77
#define ELY_KEY_F9             0x78
#define ELY_KEY_F10            0x79
#define ELY_KEY_F11            0x7A
#define ELY_KEY_F12            0x7B
#define ELY_KEY_F13            0x7C
#define ELY_KEY_F14            0x7D
#define ELY_KEY_F15            0x7E
#define ELY_KEY_F16            0x7F
#define ELY_KEY_F17            0x80
#define ELY_KEY_F18            0x81
#define ELY_KEY_F19            0x82
#define ELY_KEY_F20            0x83
#define ELY_KEY_F21            0x84
#define ELY_KEY_F22            0x85
#define ELY_KEY_F23            0x86
#define ELY_KEY_F24            0x87

/*
* 0x88 - 0x8F : unassigned
*/

#define ELY_KEY_NUMLOCK        0x90
#define ELY_KEY_SCROLL         0x91

/*
* 0x92 - 0x9F : unassigned
*/


/*
* ELY_L* & ELY_R* - left and right Alt, Ctrl and Shift virtual keys.
* Used only as parameters to GetAsyncKeyState() and GetKeyState().
* No other API or message will distinguish left and right keys in this way.
*/
#define ELY_KEY_LSHIFT         0xA0
#define ELY_KEY_RSHIFT         0xA1
#define ELY_KEY_LCONTROL       0xA2
#define ELY_KEY_RCONTROL       0xA3
#define ELY_KEY_LALT           0xA4
#define ELY_KEY_RALT           0xA5

/*
* 0xAD - 0xB3 : Media Keys 
*/

#define ELY_KEY_VOLUME_MUTE			0xAD
#define ELY_KEY_VOLUME_DOWN			0xAE
#define ELY_KEY_VOLUME_UP			0xAF
#define ELY_KEY_MEDIA_NEXT			0xB0
#define ELY_KEY_MEDIA_PREV			0xB1
#define ELY_KEY_MEDIA_STOP			0xB2
#define ELY_KEY_MEDIA_PLAY_PAUSE	0xB3

/*
* 0xB8 - 0xB9 : reserved
*/

#define ELY_KEY_OEM_1          0xBA   // ';:' for US
#define ELY_KEY_OEM_PLUS       0xBB   // '+' any country
#define ELY_KEY_OEM_COMMA      0xBC   // ',' any country
#define ELY_KEY_OEM_MINUS      0xBD   // '-' any country
#define ELY_KEY_OEM_PERIOD     0xBE   // '.' any country
#define ELY_KEY_OEM_2          0xBF   // '/?' for US
#define ELY_KEY_OEM_3          0xC0   // '`~' for US
#define ELY_KEY_OEM_4          0xDB  //  '[{' for US
#define ELY_KEY_OEM_5          0xDC  //  '\|' for US
#define ELY_KEY_OEM_6          0xDD  //  ']}' for US
#define ELY_KEY_OEM_7          0xDE  //  ''"' for US

/*
* 0xC1 - 0xC2 : reserved
*/


/*
* 0xC3 - 0xDA : Gamepad input (XInput/SDL_GameController)
*/

#define ELY_GAMEPAD_A                         0xC3 
#define ELY_GAMEPAD_B                         0xC4 
#define ELY_GAMEPAD_X                         0xC5 
#define ELY_GAMEPAD_Y                         0xC6 
#define ELY_GAMEPAD_RIGHT_SHOULDER            0xC7 
#define ELY_GAMEPAD_LEFT_SHOULDER             0xC8 
#define ELY_GAMEPAD_LEFT_TRIGGER              0xC9 
#define ELY_GAMEPAD_RIGHT_TRIGGER             0xCA 
#define ELY_GAMEPAD_DPAD_UP                   0xCB 
#define ELY_GAMEPAD_DPAD_DOWN                 0xCC 
#define ELY_GAMEPAD_DPAD_LEFT                 0xCD 
#define ELY_GAMEPAD_DPAD_RIGHT                0xCE 
#define ELY_GAMEPAD_MENU                      0xCF 
#define ELY_GAMEPAD_VIEW                      0xD0 
#define ELY_GAMEPAD_LEFT_THUMBSTICK_BUTTON    0xD1 
#define ELY_GAMEPAD_RIGHT_THUMBSTICK_BUTTON   0xD2 
