#pragma once

#include "Core.h"
#include "KeyCodes.h"

#include <GLFW/glfw3.h>

namespace Elysium {
	inline int TranslateToGLFWKey(int keycode) {
		switch (keycode)
		{
        case ELY_KEY_INVALID: return -1;
        case ELY_KEY_BACK: return GLFW_KEY_BACKSPACE;
        case ELY_KEY_TAB: return GLFW_KEY_TAB;
        case ELY_KEY_RETURN: return GLFW_KEY_ENTER;
        case ELY_KEY_PAUSE: return GLFW_KEY_PAUSE;
        case ELY_KEY_CAPSLOCK: return GLFW_KEY_CAPS_LOCK;
        case ELY_KEY_ESCAPE: return GLFW_KEY_ESCAPE;
        case ELY_KEY_SPACE: return GLFW_KEY_SPACE;
        case ELY_KEY_END: return GLFW_KEY_END;
        case ELY_KEY_HOME: return GLFW_KEY_HOME;
        case ELY_KEY_LEFT: return GLFW_KEY_LEFT;
        case ELY_KEY_UP: return GLFW_KEY_UP;
        case ELY_KEY_RIGHT: return GLFW_KEY_RIGHT;
        case ELY_KEY_DOWN: return GLFW_KEY_DOWN;
        case ELY_KEY_PRINTSCREEN: return GLFW_KEY_PRINT_SCREEN;
        case ELY_KEY_INSERT: return GLFW_KEY_INSERT;
        case ELY_KEY_DELETE: return GLFW_KEY_DELETE;
        case ELY_KEY_0: return GLFW_KEY_0;
        case ELY_KEY_1: return GLFW_KEY_1;
        case ELY_KEY_2: return GLFW_KEY_2;
        case ELY_KEY_3: return GLFW_KEY_3;
        case ELY_KEY_4: return GLFW_KEY_4;
        case ELY_KEY_5: return GLFW_KEY_5;
        case ELY_KEY_6: return GLFW_KEY_6;
        case ELY_KEY_7: return GLFW_KEY_7;
        case ELY_KEY_8: return GLFW_KEY_8;
        case ELY_KEY_9: return GLFW_KEY_9;
        case ELY_KEY_A: return GLFW_KEY_A;
        case ELY_KEY_B: return GLFW_KEY_B;
        case ELY_KEY_C: return GLFW_KEY_C;
        case ELY_KEY_D: return GLFW_KEY_D;
        case ELY_KEY_E: return GLFW_KEY_E;
        case ELY_KEY_F: return GLFW_KEY_F;
        case ELY_KEY_G: return GLFW_KEY_G;
        case ELY_KEY_H: return GLFW_KEY_H;
        case ELY_KEY_I: return GLFW_KEY_I;
        case ELY_KEY_J: return GLFW_KEY_J;
        case ELY_KEY_K: return GLFW_KEY_K;
        case ELY_KEY_L: return GLFW_KEY_L;
        case ELY_KEY_M: return GLFW_KEY_M;
        case ELY_KEY_N: return GLFW_KEY_N;
        case ELY_KEY_O: return GLFW_KEY_O;
        case ELY_KEY_P: return GLFW_KEY_P;
        case ELY_KEY_Q: return GLFW_KEY_Q;
        case ELY_KEY_R: return GLFW_KEY_R;
        case ELY_KEY_S: return GLFW_KEY_S;
        case ELY_KEY_T: return GLFW_KEY_T;
        case ELY_KEY_U: return GLFW_KEY_U;
        case ELY_KEY_V: return GLFW_KEY_V;
        case ELY_KEY_W: return GLFW_KEY_W;
        case ELY_KEY_X: return GLFW_KEY_X;
        case ELY_KEY_Y: return GLFW_KEY_Y;
        case ELY_KEY_Z: return GLFW_KEY_Z;
        case ELY_KEY_LSUPER: return GLFW_KEY_LEFT_SUPER;
        case ELY_KEY_RSUPER: return GLFW_KEY_RIGHT_SUPER;
        case ELY_KEY_NUMPAD0: return GLFW_KEY_KP_0;
        case ELY_KEY_NUMPAD1: return GLFW_KEY_KP_1;
        case ELY_KEY_NUMPAD2: return GLFW_KEY_KP_2;
        case ELY_KEY_NUMPAD3: return GLFW_KEY_KP_3;
        case ELY_KEY_NUMPAD4: return GLFW_KEY_KP_4;
        case ELY_KEY_NUMPAD5: return GLFW_KEY_KP_5;
        case ELY_KEY_NUMPAD6: return GLFW_KEY_KP_6;
        case ELY_KEY_NUMPAD7: return GLFW_KEY_KP_7;
        case ELY_KEY_NUMPAD8: return GLFW_KEY_KP_8;
        case ELY_KEY_NUMPAD9: return GLFW_KEY_KP_9;
        case ELY_KEY_MULTIPLY: return GLFW_KEY_KP_MULTIPLY;
        case ELY_KEY_ADD: return GLFW_KEY_KP_ADD;
        case ELY_KEY_SUBTRACT: return GLFW_KEY_KP_SUBTRACT;
        case ELY_KEY_DECIMAL: return GLFW_KEY_KP_DECIMAL;
        case ELY_KEY_DIVIDE: return GLFW_KEY_KP_DIVIDE;
        case ELY_KEY_F1: return GLFW_KEY_F1;
        case ELY_KEY_F2: return GLFW_KEY_F2;
        case ELY_KEY_F3: return GLFW_KEY_F3;
        case ELY_KEY_F4: return GLFW_KEY_F4;
        case ELY_KEY_F5: return GLFW_KEY_F5;
        case ELY_KEY_F6: return GLFW_KEY_F6;
        case ELY_KEY_F7: return GLFW_KEY_F7;
        case ELY_KEY_F8: return GLFW_KEY_F8;
        case ELY_KEY_F9: return GLFW_KEY_F9;
        case ELY_KEY_F10: return GLFW_KEY_F10;
        case ELY_KEY_F11: return GLFW_KEY_F11;
        case ELY_KEY_F12: return GLFW_KEY_F12;
        case ELY_KEY_F13: return GLFW_KEY_F13;
        case ELY_KEY_F14: return GLFW_KEY_F14;
        case ELY_KEY_F15: return GLFW_KEY_F15;
        case ELY_KEY_F16: return GLFW_KEY_F16;
        case ELY_KEY_F17: return GLFW_KEY_F17;
        case ELY_KEY_F18: return GLFW_KEY_F18;
        case ELY_KEY_F19: return GLFW_KEY_F19;
        case ELY_KEY_F20: return GLFW_KEY_F20;
        case ELY_KEY_F21: return GLFW_KEY_F21;
        case ELY_KEY_F22: return GLFW_KEY_F22;
        case ELY_KEY_F23: return GLFW_KEY_F23;
        case ELY_KEY_F24: return GLFW_KEY_F24;
        case ELY_KEY_NUMLOCK: return GLFW_KEY_NUM_LOCK;
        case ELY_KEY_SCROLL: return GLFW_KEY_SCROLL_LOCK;
        case ELY_KEY_LSHIFT: return GLFW_KEY_LEFT_SHIFT;
        case ELY_KEY_RSHIFT: return GLFW_KEY_RIGHT_SHIFT;
        case ELY_KEY_LCONTROL: return GLFW_KEY_LEFT_CONTROL;
        case ELY_KEY_RCONTROL: return GLFW_KEY_RIGHT_CONTROL;
        case ELY_KEY_LALT: return GLFW_KEY_LEFT_ALT;
        case ELY_KEY_RALT: return GLFW_KEY_RIGHT_ALT;
        default: return ELY_KEY_INVALID;
		}

		ELY_CORE_ASSERT(ELY_KEY_INVALID, "Unknown keycode!");
		return -1;
	}

    inline int TranslateFromGLFWKey(int glfwKeyCode) {
        switch (glfwKeyCode)
        {
        case GLFW_KEY_BACKSPACE: return ELY_KEY_BACK;
        case GLFW_KEY_TAB: return ELY_KEY_TAB;
        case GLFW_KEY_ENTER: return ELY_KEY_RETURN;
        case GLFW_KEY_PAUSE: return ELY_KEY_PAUSE;
        case GLFW_KEY_CAPS_LOCK: return ELY_KEY_CAPSLOCK;
        case GLFW_KEY_ESCAPE: return ELY_KEY_ESCAPE;
        case GLFW_KEY_SPACE: return ELY_KEY_SPACE;
        case GLFW_KEY_END: return ELY_KEY_END;
        case GLFW_KEY_HOME: return ELY_KEY_HOME;
        case GLFW_KEY_LEFT: return ELY_KEY_LEFT;
        case GLFW_KEY_UP: return ELY_KEY_UP;
        case GLFW_KEY_RIGHT: return ELY_KEY_RIGHT;
        case GLFW_KEY_DOWN: return ELY_KEY_DOWN;
        case GLFW_KEY_PRINT_SCREEN: return ELY_KEY_PRINTSCREEN;
        case GLFW_KEY_INSERT: return ELY_KEY_INSERT;
        case GLFW_KEY_DELETE: return ELY_KEY_DELETE;
        case GLFW_KEY_0: return ELY_KEY_0;
        case GLFW_KEY_1: return ELY_KEY_1;
        case GLFW_KEY_2: return ELY_KEY_2;
        case GLFW_KEY_3: return ELY_KEY_3;
        case GLFW_KEY_4: return ELY_KEY_4;
        case GLFW_KEY_5: return ELY_KEY_5;
        case GLFW_KEY_6: return ELY_KEY_6;
        case GLFW_KEY_7: return ELY_KEY_7;
        case GLFW_KEY_8: return ELY_KEY_8;
        case GLFW_KEY_9: return ELY_KEY_9;
        case GLFW_KEY_A: return ELY_KEY_A;
        case GLFW_KEY_B: return ELY_KEY_B;
        case GLFW_KEY_C: return ELY_KEY_C;
        case GLFW_KEY_D: return ELY_KEY_D;
        case GLFW_KEY_E: return ELY_KEY_E;
        case GLFW_KEY_F: return ELY_KEY_F;
        case GLFW_KEY_G: return ELY_KEY_G;
        case GLFW_KEY_H: return ELY_KEY_H;
        case GLFW_KEY_I: return ELY_KEY_I;
        case GLFW_KEY_J: return ELY_KEY_J;
        case GLFW_KEY_K: return ELY_KEY_K;
        case GLFW_KEY_L: return ELY_KEY_L;
        case GLFW_KEY_M: return ELY_KEY_M;
        case GLFW_KEY_N: return ELY_KEY_N;
        case GLFW_KEY_O: return ELY_KEY_O;
        case GLFW_KEY_P: return ELY_KEY_P;
        case GLFW_KEY_Q: return ELY_KEY_Q;
        case GLFW_KEY_R: return ELY_KEY_R;
        case GLFW_KEY_S: return ELY_KEY_S;
        case GLFW_KEY_T: return ELY_KEY_T;
        case GLFW_KEY_U: return ELY_KEY_U;
        case GLFW_KEY_V: return ELY_KEY_V;
        case GLFW_KEY_W: return ELY_KEY_W;
        case GLFW_KEY_X: return ELY_KEY_X;
        case GLFW_KEY_Y: return ELY_KEY_Y;
        case GLFW_KEY_Z: return ELY_KEY_Z;
        case GLFW_KEY_LEFT_SUPER: return ELY_KEY_LSUPER;
        case GLFW_KEY_RIGHT_SUPER: return ELY_KEY_RSUPER;
        case GLFW_KEY_KP_0: return ELY_KEY_NUMPAD0;
        case GLFW_KEY_KP_1: return ELY_KEY_NUMPAD1;
        case GLFW_KEY_KP_2: return ELY_KEY_NUMPAD2;
        case GLFW_KEY_KP_3: return ELY_KEY_NUMPAD3;
        case GLFW_KEY_KP_4: return ELY_KEY_NUMPAD4;
        case GLFW_KEY_KP_5: return ELY_KEY_NUMPAD5;
        case GLFW_KEY_KP_6: return ELY_KEY_NUMPAD6;
        case GLFW_KEY_KP_7: return ELY_KEY_NUMPAD7;
        case GLFW_KEY_KP_8: return ELY_KEY_NUMPAD8;
        case GLFW_KEY_KP_9: return ELY_KEY_NUMPAD9;
        case GLFW_KEY_KP_MULTIPLY: return ELY_KEY_MULTIPLY;
        case GLFW_KEY_KP_ADD: return ELY_KEY_ADD;
        case GLFW_KEY_KP_SUBTRACT: return ELY_KEY_SUBTRACT;
        case GLFW_KEY_KP_DECIMAL: return ELY_KEY_DECIMAL;
        case GLFW_KEY_KP_DIVIDE: return ELY_KEY_DIVIDE;
        case GLFW_KEY_F1: return ELY_KEY_F1;
        case GLFW_KEY_F2: return ELY_KEY_F2;
        case GLFW_KEY_F3: return ELY_KEY_F3;
        case GLFW_KEY_F4: return ELY_KEY_F4;
        case GLFW_KEY_F5: return ELY_KEY_F5;
        case GLFW_KEY_F6: return ELY_KEY_F6;
        case GLFW_KEY_F7: return ELY_KEY_F7;
        case GLFW_KEY_F8: return ELY_KEY_F8;
        case GLFW_KEY_F9: return ELY_KEY_F9;
        case GLFW_KEY_F10: return ELY_KEY_F10;
        case GLFW_KEY_F11: return ELY_KEY_F11;
        case GLFW_KEY_F12: return ELY_KEY_F12;
        case GLFW_KEY_F13: return ELY_KEY_F13;
        case GLFW_KEY_F14: return ELY_KEY_F14;
        case GLFW_KEY_F15: return ELY_KEY_F15;
        case GLFW_KEY_F16: return ELY_KEY_F16;
        case GLFW_KEY_F17: return ELY_KEY_F17;
        case GLFW_KEY_F18: return ELY_KEY_F18;
        case GLFW_KEY_F19: return ELY_KEY_F19;
        case GLFW_KEY_F20: return ELY_KEY_F20;
        case GLFW_KEY_F21: return ELY_KEY_F21;
        case GLFW_KEY_F22: return ELY_KEY_F22;
        case GLFW_KEY_F23: return ELY_KEY_F23;
        case GLFW_KEY_F24: return ELY_KEY_F24;
        case GLFW_KEY_NUM_LOCK: return ELY_KEY_NUMLOCK;
        case GLFW_KEY_SCROLL_LOCK: return ELY_KEY_SCROLL;
        case GLFW_KEY_LEFT_SHIFT: return ELY_KEY_LSHIFT;
        case GLFW_KEY_RIGHT_SHIFT: return ELY_KEY_RSHIFT;
        case GLFW_KEY_LEFT_CONTROL: return ELY_KEY_LCONTROL;
        case GLFW_KEY_RIGHT_CONTROL: return ELY_KEY_RCONTROL;
        case GLFW_KEY_LEFT_ALT: return ELY_KEY_LALT;
        case GLFW_KEY_RIGHT_ALT: return ELY_KEY_RALT;
        default: return ELY_KEY_INVALID;
        }
    }
}