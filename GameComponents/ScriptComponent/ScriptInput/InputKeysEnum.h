#ifndef __KeysEnum__
#define __KeysEnum__

#include "Linker.h"

namespace InputKeysEnum
{
	enum class KeyCode : int {
		KEY_START    = 0,

		VK_LBUTTON   = 0x01,
		VK_RBUTTON   = 0x02,
		VK_MBUTTON   = 0x04,
		VK_XBUTTON1  = 0x05,
		VK_XBUTTON2  = 0x06,

		VK_SPACE     = 0x20,
		VK_PRIOR     = 0x21,
		VK_NEXT      = 0x22,
		VK_END       = 0x23,
		VK_HOME      = 0x24,
		VK_LEFT      = 0x25,
		VK_UP        = 0x26,
		VK_RIGHT     = 0x27,
		VK_DOWN      = 0x28,
		VK_SELECT    = 0x29,
		VK_PRINT     = 0x2A,
		VK_EXECUTE   = 0x2B,
		VK_SNAPSHOT  = 0x2C,
		VK_INSERT    = 0x2D,
		VK_DELETE    = 0x2E,
		VK_HELP      = 0x2F,


		VK_NUMPAD0   = 0x60,
		VK_NUMPAD1   = 0x61,
		VK_NUMPAD2   = 0x62,
		VK_NUMPAD3   = 0x63,
		VK_NUMPAD4   = 0x64,
		VK_NUMPAD5   = 0x65,
		VK_NUMPAD6   = 0x66,
		VK_NUMPAD7   = 0x67,
		VK_NUMPAD8   = 0x68,
		VK_NUMPAD9   = 0x69,
		VK_MULTIPLY  = 0x6A,
		VK_ADD       = 0x6B,
		VK_SEPARATOR = 0x6C,
		VK_SUBTRACT  = 0x6D,
		VK_DECIMAL   = 0x6E,
		VK_DIVIDE    = 0x6F,
		VK_F1        = 0x70,
		VK_F2        = 0x71,
		VK_F3        = 0x72,
		VK_F4        = 0x73,
		VK_F5        = 0x74,
		VK_F6        = 0x75,
		VK_F7        = 0x76,
		VK_F8        = 0x77,
		VK_F9        = 0x78,
		VK_F10       = 0x79,
		VK_F11       = 0x7A,
		VK_F12       = 0x7B,

		VK_ESCAPE    = 0x1B,
		VK_LSHIFT    = 0xA0,
		VK_RSHIFT    = 0xA1,
		VK_TAB       = 0x09,
		VK_LCONTROL  = 0xA2,
		VK_RCONTROL  = 0xA3,
		VK_SHIFT     = 0x10,
		VK_CONTROL   = 0x11,
		VK_MENU      = 0x12,

		VK_KEY_0     = 0x30,
		VK_KEY_1     = 0x31,
		VK_KEY_2     = 0x32,
		VK_KEY_3     = 0x33,
		VK_KEY_4     = 0x34,
		VK_KEY_5     = 0x35,
		VK_KEY_6     = 0x36,
		VK_KEY_7     = 0x37,
		VK_KEY_8     = 0x38,
		VK_KEY_9     = 0x39,
		VK_KEY_A     = 0x41,
		VK_KEY_B     = 0x42,
		VK_KEY_C     = 0x43,
		VK_KEY_D     = 0x44,
		VK_KEY_E     = 0x45,
		VK_KEY_F     = 0x46,
		VK_KEY_G     = 0x47,
		VK_KEY_H     = 0x48,
		VK_KEY_I     = 0x49,
		VK_KEY_J     = 0x4A,
		VK_KEY_K     = 0x4B,
		VK_KEY_L     = 0x4C,
		VK_KEY_M     = 0x4D,
		VK_KEY_N     = 0x4E,
		VK_KEY_O     = 0x4F,
		VK_KEY_P     = 0x50,
		VK_KEY_Q     = 0x51,
		VK_KEY_R     = 0x52,
		VK_KEY_S     = 0x53,
		VK_KEY_T     = 0x54,
		VK_KEY_U     = 0x55,
		VK_KEY_V     = 0x56,
		VK_KEY_W     = 0x57,
		VK_KEY_X     = 0x58,
		VK_KEY_Y     = 0x59,
		VK_KEY_Z     = 0x5A,

		KEY_LAST
	};// Key codes

	enum class KeyStatus
	{
		KeyUp = 0,
		KeyDown = 1,
		Unknown = 2
	};
}

#endif //__KeysEnum__
