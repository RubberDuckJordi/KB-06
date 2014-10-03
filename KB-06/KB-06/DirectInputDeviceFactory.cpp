#include "DirectInputDeviceFactory.h"
#include "LoggerPool.h"
#include "Input.h"

namespace pengine
{
	DirectInputDeviceFactory::DirectInputDeviceFactory()
	{
		dInput = NULL;
		if (SUCCEEDED(DirectInput8Create(
			GetModuleHandle(NULL),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&dInput,
			NULL)))
		{
			logger->Log(Logger::DEBUG, "DirectInputDeviceFactory: Initialised factory");
		}
		else
		{
			logger->Log(Logger::ERR, "DirectInputDeviceFactory: Initialisation failed");
		}

		CreateActionMapping();
	}

	void DirectInputDeviceFactory::Initialise(HWND p_hwnd)
	{
		hwnd = p_hwnd;
	}

	DirectInputDeviceFactory::~DirectInputDeviceFactory()
	{
		if (dInput != NULL)
		{
			dInput->Release();
			delete dInput;
		}
		delete actionMapping;

		InputDeviceFactory::~InputDeviceFactory();
	}

	InputDevice* DirectInputDeviceFactory::CreateInputDevice(InputDevice::Type type)
	{
		if (hwnd != NULL)
		{
			DirectInputDevice* newDevice = NULL;

			switch (type)
			{
			case InputDevice::KEYBOARD:
				newDevice = new DirectKeyboard();
				logger->Log(Logger::DEBUG, "DirectInputDeviceFactory: Created keyboard");
				break;
			case InputDevice::MOUSE:
				newDevice = new DirectMouse();
				logger->Log(Logger::DEBUG, "DirectInputDeviceFactory: Created mouse");
				break;
			default:
				logger->Log(Logger::ERR, "DirectInputDeviceFactory: Unable to create device, unknown device type");
				return NULL;
			}

			if (newDevice->Initialize(dInput, hwnd))
			{
				newDevice->SetActionMapping(actionMapping);
				return newDevice;
			}
			else
			{
				logger->Log(Logger::ERR, "DirectInputDeviceFactory: Unable to create device, initialisation failed");
				delete newDevice;
				return NULL;
			}
		}
		else
		{
			logger->Log(Logger::ERR, "Unable to create device, factory is not initialised");
		}
		return NULL;
	}

	void DirectInputDeviceFactory::CreateActionMapping()
	{
		actionMapping = new std::map<Input, int>();
		// Map defines to int values, we can't create a pointer to preprocessor values
		(*actionMapping)[Input::KEY_ESCAPE] = DIK_ESCAPE;
		(*actionMapping)[Input::KEY_1] = DIK_1;
		(*actionMapping)[Input::KEY_2] = DIK_2;
		(*actionMapping)[Input::KEY_3] = DIK_3;
		(*actionMapping)[Input::KEY_4] = DIK_4;
		(*actionMapping)[Input::KEY_5] = DIK_5;
		(*actionMapping)[Input::KEY_6] = DIK_6;
		(*actionMapping)[Input::KEY_7] = DIK_7;
		(*actionMapping)[Input::KEY_8] = DIK_8;
		(*actionMapping)[Input::KEY_9] = DIK_9;
		(*actionMapping)[Input::KEY_0] = DIK_0;
		(*actionMapping)[Input::KEY_MINUS] = DIK_MINUS;
		(*actionMapping)[Input::KEY_EQUALS] = DIK_EQUALS;
		(*actionMapping)[Input::KEY_BACK] = DIK_BACK;
		(*actionMapping)[Input::KEY_TAB] = DIK_TAB;
		(*actionMapping)[Input::KEY_Q] = DIK_Q;
		(*actionMapping)[Input::KEY_W] = DIK_W;
		(*actionMapping)[Input::KEY_E] = DIK_E;
		(*actionMapping)[Input::KEY_R] = DIK_R;
		(*actionMapping)[Input::KEY_T] = DIK_T;
		(*actionMapping)[Input::KEY_Y] = DIK_Y;
		(*actionMapping)[Input::KEY_U] = DIK_U;
		(*actionMapping)[Input::KEY_I] = DIK_I;
		(*actionMapping)[Input::KEY_O] = DIK_O;
		(*actionMapping)[Input::KEY_P] = DIK_P;
		(*actionMapping)[Input::KEY_LBRACKET] = DIK_LBRACKET;
		(*actionMapping)[Input::KEY_RBRACKET] = DIK_RBRACKET;
		(*actionMapping)[Input::KEY_RETURN] = DIK_RETURN;
		(*actionMapping)[Input::KEY_LCONTROL] = DIK_LCONTROL;
		(*actionMapping)[Input::KEY_A] = DIK_A;
		(*actionMapping)[Input::KEY_S] = DIK_S;
		(*actionMapping)[Input::KEY_D] = DIK_D;
		(*actionMapping)[Input::KEY_F] = DIK_F;
		(*actionMapping)[Input::KEY_G] = DIK_G;
		(*actionMapping)[Input::KEY_H] = DIK_H;
		(*actionMapping)[Input::KEY_J] = DIK_J;
		(*actionMapping)[Input::KEY_K] = DIK_K;
		(*actionMapping)[Input::KEY_L] = DIK_L;
		(*actionMapping)[Input::KEY_SEMICOLON] = DIK_SEMICOLON;
		(*actionMapping)[Input::KEY_APOSTROPHE] = DIK_APOSTROPHE;
		(*actionMapping)[Input::KEY_GRAVE] = DIK_GRAVE;
		(*actionMapping)[Input::KEY_LSHIFT] = DIK_LSHIFT;
		(*actionMapping)[Input::KEY_BACKSLASH] = DIK_BACKSLASH;
		(*actionMapping)[Input::KEY_Z] = DIK_Z;
		(*actionMapping)[Input::KEY_X] = DIK_X;
		(*actionMapping)[Input::KEY_C] = DIK_C;
		(*actionMapping)[Input::KEY_V] = DIK_V;
		(*actionMapping)[Input::KEY_B] = DIK_B;
		(*actionMapping)[Input::KEY_N] = DIK_N;
		(*actionMapping)[Input::KEY_M] = DIK_M;
		(*actionMapping)[Input::KEY_COMMA] = DIK_COMMA;
		(*actionMapping)[Input::KEY_PERIOD] = DIK_PERIOD;
		(*actionMapping)[Input::KEY_SLASH] = DIK_SLASH;
		(*actionMapping)[Input::KEY_RSHIFT] = DIK_RSHIFT;
		(*actionMapping)[Input::KEY_MULTIPLY] = DIK_MULTIPLY;
		(*actionMapping)[Input::KEY_LMENU] = DIK_LMENU;
		(*actionMapping)[Input::KEY_SPACE] = DIK_SPACE;
		(*actionMapping)[Input::KEY_CAPITAL] = DIK_CAPITAL;
		(*actionMapping)[Input::KEY_F1] = DIK_F1;
		(*actionMapping)[Input::KEY_F2] = DIK_F2;
		(*actionMapping)[Input::KEY_F3] = DIK_F3;
		(*actionMapping)[Input::KEY_F4] = DIK_F4;
		(*actionMapping)[Input::KEY_F5] = DIK_F5;
		(*actionMapping)[Input::KEY_F6] = DIK_F6;
		(*actionMapping)[Input::KEY_F7] = DIK_F7;
		(*actionMapping)[Input::KEY_F8] = DIK_F8;
		(*actionMapping)[Input::KEY_F9] = DIK_F9;
		(*actionMapping)[Input::KEY_F10] = DIK_F10;
		(*actionMapping)[Input::KEY_NUMLOCK] = DIK_NUMLOCK;
		(*actionMapping)[Input::KEY_SCROLL] = DIK_SCROLL;
		(*actionMapping)[Input::KEY_NUMPAD7] = DIK_NUMPAD7;
		(*actionMapping)[Input::KEY_NUMPAD8] = DIK_NUMPAD8;
		(*actionMapping)[Input::KEY_NUMPAD9] = DIK_NUMPAD9;
		(*actionMapping)[Input::KEY_SUBTRACT] = DIK_SUBTRACT;
		(*actionMapping)[Input::KEY_NUMPAD4] = DIK_NUMPAD4;
		(*actionMapping)[Input::KEY_NUMPAD5] = DIK_NUMPAD5;
		(*actionMapping)[Input::KEY_NUMPAD6] = DIK_NUMPAD6;
		(*actionMapping)[Input::KEY_ADD] = DIK_ADD;
		(*actionMapping)[Input::KEY_NUMPAD1] = DIK_NUMPAD1;
		(*actionMapping)[Input::KEY_NUMPAD2] = DIK_NUMPAD2;
		(*actionMapping)[Input::KEY_NUMPAD3] = DIK_NUMPAD3;
		(*actionMapping)[Input::KEY_NUMPAD0] = DIK_NUMPAD0;
		(*actionMapping)[Input::KEY_DECIMAL] = DIK_DECIMAL;
		(*actionMapping)[Input::KEY_OEM_102] = DIK_OEM_102;
		(*actionMapping)[Input::KEY_F11] = DIK_F11;
		(*actionMapping)[Input::KEY_F12] = DIK_F12;
		(*actionMapping)[Input::KEY_F13] = DIK_F13;
		(*actionMapping)[Input::KEY_F14] = DIK_F14;
		(*actionMapping)[Input::KEY_F15] = DIK_F15;
		(*actionMapping)[Input::KEY_KANA] = DIK_KANA;
		(*actionMapping)[Input::KEY_ABNT_C1] = DIK_ABNT_C1;
		(*actionMapping)[Input::KEY_CONVERT] = DIK_CONVERT;
		(*actionMapping)[Input::KEY_NOCONVERT] = DIK_NOCONVERT;
		(*actionMapping)[Input::KEY_YEN] = DIK_YEN;
		(*actionMapping)[Input::KEY_ABNT_C2] = DIK_ABNT_C2;
		(*actionMapping)[Input::KEY_NUMPADEQUALS] = DIK_NUMPADEQUALS;
		(*actionMapping)[Input::KEY_PREVTRACK] = DIK_PREVTRACK;
		(*actionMapping)[Input::KEY_AT] = DIK_AT;
		(*actionMapping)[Input::KEY_COLON] = DIK_COLON;
		(*actionMapping)[Input::KEY_UNDERLINE] = DIK_UNDERLINE;
		(*actionMapping)[Input::KEY_KANJI] = DIK_KANJI;
		(*actionMapping)[Input::KEY_STOP] = DIK_STOP;
		(*actionMapping)[Input::KEY_AX] = DIK_AX;
		(*actionMapping)[Input::KEY_UNLABELED] = DIK_UNLABELED;
		(*actionMapping)[Input::KEY_NEXTTRACK] = DIK_NEXTTRACK;
		(*actionMapping)[Input::KEY_NUMPADENTER] = DIK_NUMPADENTER;
		(*actionMapping)[Input::KEY_RCONTROL] = DIK_RCONTROL;
		(*actionMapping)[Input::KEY_MUTE] = DIK_MUTE;
		(*actionMapping)[Input::KEY_CALCULATOR] = DIK_CALCULATOR;
		(*actionMapping)[Input::KEY_PLAYPAUSE] = DIK_PLAYPAUSE;
		(*actionMapping)[Input::KEY_MEDIASTOP] = DIK_MEDIASTOP;
		(*actionMapping)[Input::KEY_VOLUMEDOWN] = DIK_VOLUMEDOWN;
		(*actionMapping)[Input::KEY_VOLUMEUP] = DIK_VOLUMEUP;
		(*actionMapping)[Input::KEY_WEBHOME] = DIK_WEBHOME;
		(*actionMapping)[Input::KEY_NUMPADCOMMA] = DIK_NUMPADCOMMA;
		(*actionMapping)[Input::KEY_DIVIDE] = DIK_DIVIDE;
		(*actionMapping)[Input::KEY_SYSRQ] = DIK_SYSRQ;
		(*actionMapping)[Input::KEY_RMENU] = DIK_RMENU;
		(*actionMapping)[Input::KEY_PAUSE] = DIK_PAUSE;
		(*actionMapping)[Input::KEY_HOME] = DIK_HOME;
		(*actionMapping)[Input::KEY_UP] = DIK_UP;
		(*actionMapping)[Input::KEY_PRIOR] = DIK_PRIOR;
		(*actionMapping)[Input::KEY_LEFT] = DIK_LEFT;
		(*actionMapping)[Input::KEY_RIGHT] = DIK_RIGHT;
		(*actionMapping)[Input::KEY_END] = DIK_END;
		(*actionMapping)[Input::KEY_DOWN] = DIK_DOWN;
		(*actionMapping)[Input::KEY_NEXT] = DIK_NEXT;
		(*actionMapping)[Input::KEY_INSERT] = DIK_INSERT;
		(*actionMapping)[Input::KEY_DELETE] = DIK_DELETE;
		(*actionMapping)[Input::KEY_LWIN] = DIK_LWIN;
		(*actionMapping)[Input::KEY_RWIN] = DIK_RWIN;
		(*actionMapping)[Input::KEY_APPS] = DIK_APPS;
		(*actionMapping)[Input::KEY_POWER] = DIK_POWER;
		(*actionMapping)[Input::KEY_SLEEP] = DIK_SLEEP;
		(*actionMapping)[Input::KEY_WAKE] = DIK_WAKE;
		(*actionMapping)[Input::KEY_WEBSEARCH] = DIK_WEBSEARCH;
		(*actionMapping)[Input::KEY_WEBFAVORITES] = DIK_WEBFAVORITES;
		(*actionMapping)[Input::KEY_WEBREFRESH] = DIK_WEBREFRESH;
		(*actionMapping)[Input::KEY_WEBSTOP] = DIK_WEBSTOP;
		(*actionMapping)[Input::KEY_WEBFORWARD] = DIK_WEBFORWARD;
		(*actionMapping)[Input::KEY_WEBBACK] = DIK_WEBBACK;
		(*actionMapping)[Input::KEY_MYCOMPUTER] = DIK_MYCOMPUTER;
		(*actionMapping)[Input::KEY_MAIL] = DIK_MAIL;
		(*actionMapping)[Input::KEY_MEDIASELECT] = DIK_MEDIASELECT;
		(*actionMapping)[Input::MOUSE_X] = DIMOFS_X;
		(*actionMapping)[Input::MOUSE_Y] = DIMOFS_Y;
		(*actionMapping)[Input::MOUSE_Z] = DIMOFS_Z;
		(*actionMapping)[Input::MOUSE_BUTTON0] = DIMOFS_BUTTON0;
		(*actionMapping)[Input::MOUSE_BUTTON1] = DIMOFS_BUTTON1;
		(*actionMapping)[Input::MOUSE_BUTTON2] = DIMOFS_BUTTON2;
		(*actionMapping)[Input::MOUSE_BUTTON3] = DIMOFS_BUTTON3;
		(*actionMapping)[Input::MOUSE_BUTTON4] = DIMOFS_BUTTON4;
		(*actionMapping)[Input::MOUSE_BUTTON5] = DIMOFS_BUTTON5;
		(*actionMapping)[Input::MOUSE_BUTTON6] = DIMOFS_BUTTON6;
		(*actionMapping)[Input::MOUSE_BUTTON7] = DIMOFS_BUTTON7;
	}
}