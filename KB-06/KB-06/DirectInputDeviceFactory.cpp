#include "DirectInputDeviceFactory.h"
#include "LoggerPool.h"
#include "Input.h"

Input::DirectInputDeviceFactory::DirectInputDeviceFactory()
{
	m_dInput = NULL;
	if (SUCCEEDED(DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_dInput,
		NULL)))
	{
		logger->Log(Logger::Logger::DEBUG, "DirectInputDeviceFactory: Initialised factory");
	}
	else
	{
		logger->Log(Logger::Logger::ERR, "DirectInputDeviceFactory: Initialisation failed");
	}

	CreateActionMapping();
}
Input::DirectInputDeviceFactory::~DirectInputDeviceFactory()
{
	if (m_dInput != NULL)
	{
		m_dInput->Release();
		m_dInput = NULL;
	}
	InputDeviceFactory::~InputDeviceFactory();
}
Input::InputDevice* Input::DirectInputDeviceFactory::CreateInputDevice(InputDevice::Type type, Window::Window* window)
{
	DirectInputDevice* newDevice = NULL;

	switch (type)
	{
	case InputDevice::KEYBOARD:
		newDevice = new DirectKeyboard();
		logger->Log(Logger::Logger::DEBUG, "DirectInputDeviceFactory: Created keyboard");
		break;
	case InputDevice::MOUSE:
		newDevice = new DirectMouse();
		logger->Log(Logger::Logger::DEBUG, "DirectInputDeviceFactory: Created mouse");
		break;
	default:
		logger->Log(Logger::Logger::ERR, "DirectInputDeviceFactory: Unable to create device, unknown device type");
		return NULL;
	}

	if (newDevice->Initialize(window->GetHWND(), m_dInput))
	{
		newDevice->SetActionMapping(&actionMapping);
		return newDevice;
	}
	else
	{
		logger->Log(Logger::Logger::ERR, "DirectInputDeviceFactory: Unable to create device, initialisation failed");
		delete newDevice;
		return NULL;
	}
}

void Input::DirectInputDeviceFactory::CreateActionMapping()
{
	// Map defines to int values, we can't create a pointer to preprocessor values
	actionMapping[Input::KEY_ESCAPE] = new int(DIK_ESCAPE);
	actionMapping[Input::KEY_1] = new int(DIK_1);
	actionMapping[Input::KEY_2] = new int(DIK_2);
	actionMapping[Input::KEY_3] = new int(DIK_3);
	actionMapping[Input::KEY_4] = new int(DIK_4);
	actionMapping[Input::KEY_5] = new int(DIK_5);
	actionMapping[Input::KEY_6] = new int(DIK_6);
	actionMapping[Input::KEY_7] = new int(DIK_7);
	actionMapping[Input::KEY_8] = new int(DIK_8);
	actionMapping[Input::KEY_9] = new int(DIK_9);
	actionMapping[Input::KEY_0] = new int(DIK_0);
	actionMapping[Input::KEY_MINUS] = new int(DIK_MINUS);
	actionMapping[Input::KEY_EQUALS] = new int(DIK_EQUALS);
	actionMapping[Input::KEY_BACK] = new int(DIK_BACK);
	actionMapping[Input::KEY_TAB] = new int(DIK_TAB);
	actionMapping[Input::KEY_Q] = new int(DIK_Q);
	actionMapping[Input::KEY_W] = new int(DIK_W);
	actionMapping[Input::KEY_E] = new int(DIK_E);
	actionMapping[Input::KEY_R] = new int(DIK_R);
	actionMapping[Input::KEY_T] = new int(DIK_T);
	actionMapping[Input::KEY_Y] = new int(DIK_Y);
	actionMapping[Input::KEY_U] = new int(DIK_U);
	actionMapping[Input::KEY_I] = new int(DIK_I);
	actionMapping[Input::KEY_O] = new int(DIK_O);
	actionMapping[Input::KEY_P] = new int(DIK_P);
	actionMapping[Input::KEY_LBRACKET] = new int(DIK_LBRACKET);
	actionMapping[Input::KEY_RBRACKET] = new int(DIK_RBRACKET);
	actionMapping[Input::KEY_RETURN] = new int(DIK_RETURN);
	actionMapping[Input::KEY_LCONTROL] = new int(DIK_LCONTROL);
	actionMapping[Input::KEY_A] = new int(DIK_A);
	actionMapping[Input::KEY_S] = new int(DIK_S);
	actionMapping[Input::KEY_D] = new int(DIK_D);
	actionMapping[Input::KEY_F] = new int(DIK_F);
	actionMapping[Input::KEY_G] = new int(DIK_G);
	actionMapping[Input::KEY_H] = new int(DIK_H);
	actionMapping[Input::KEY_J] = new int(DIK_J);
	actionMapping[Input::KEY_K] = new int(DIK_K);
	actionMapping[Input::KEY_L] = new int(DIK_L);
	actionMapping[Input::KEY_SEMICOLON] = new int(DIK_SEMICOLON);
	actionMapping[Input::KEY_APOSTROPHE] = new int(DIK_APOSTROPHE);
	actionMapping[Input::KEY_GRAVE] = new int(DIK_GRAVE);
	actionMapping[Input::KEY_LSHIFT] = new int(DIK_LSHIFT);
	actionMapping[Input::KEY_BACKSLASH] = new int(DIK_BACKSLASH);
	actionMapping[Input::KEY_Z] = new int(DIK_Z);
	actionMapping[Input::KEY_X] = new int(DIK_X);
	actionMapping[Input::KEY_C] = new int(DIK_C);
	actionMapping[Input::KEY_V] = new int(DIK_V);
	actionMapping[Input::KEY_B] = new int(DIK_B);
	actionMapping[Input::KEY_N] = new int(DIK_N);
	actionMapping[Input::KEY_M] = new int(DIK_M);
	actionMapping[Input::KEY_COMMA] = new int(DIK_COMMA);
	actionMapping[Input::KEY_PERIOD] = new int(DIK_PERIOD);
	actionMapping[Input::KEY_SLASH] = new int(DIK_SLASH);
	actionMapping[Input::KEY_RSHIFT] = new int(DIK_RSHIFT);
	actionMapping[Input::KEY_MULTIPLY] = new int(DIK_MULTIPLY);
	actionMapping[Input::KEY_LMENU] = new int(DIK_LMENU);
	actionMapping[Input::KEY_SPACE] = new int(DIK_SPACE);
	actionMapping[Input::KEY_CAPITAL] = new int(DIK_CAPITAL);
	actionMapping[Input::KEY_F1] = new int(DIK_F1);
	actionMapping[Input::KEY_F2] = new int(DIK_F2);
	actionMapping[Input::KEY_F3] = new int(DIK_F3);
	actionMapping[Input::KEY_F4] = new int(DIK_F4);
	actionMapping[Input::KEY_F5] = new int(DIK_F5);
	actionMapping[Input::KEY_F6] = new int(DIK_F6);
	actionMapping[Input::KEY_F7] = new int(DIK_F7);
	actionMapping[Input::KEY_F8] = new int(DIK_F8);
	actionMapping[Input::KEY_F9] = new int(DIK_F9);
	actionMapping[Input::KEY_F10] = new int(DIK_F10);
	actionMapping[Input::KEY_NUMLOCK] = new int(DIK_NUMLOCK);
	actionMapping[Input::KEY_SCROLL] = new int(DIK_SCROLL);
	actionMapping[Input::KEY_NUMPAD7] = new int(DIK_NUMPAD7);
	actionMapping[Input::KEY_NUMPAD8] = new int(DIK_NUMPAD8);
	actionMapping[Input::KEY_NUMPAD9] = new int(DIK_NUMPAD9);
	actionMapping[Input::KEY_SUBTRACT] = new int(DIK_SUBTRACT);
	actionMapping[Input::KEY_NUMPAD4] = new int(DIK_NUMPAD4);
	actionMapping[Input::KEY_NUMPAD5] = new int(DIK_NUMPAD5);
	actionMapping[Input::KEY_NUMPAD6] = new int(DIK_NUMPAD6);
	actionMapping[Input::KEY_ADD] = new int(DIK_ADD);
	actionMapping[Input::KEY_NUMPAD1] = new int(DIK_NUMPAD1);
	actionMapping[Input::KEY_NUMPAD2] = new int(DIK_NUMPAD2);
	actionMapping[Input::KEY_NUMPAD3] = new int(DIK_NUMPAD3);
	actionMapping[Input::KEY_NUMPAD0] = new int(DIK_NUMPAD0);
	actionMapping[Input::KEY_DECIMAL] = new int(DIK_DECIMAL);
	actionMapping[Input::KEY_OEM_102] = new int(DIK_OEM_102);
	actionMapping[Input::KEY_F11] = new int(DIK_F11);
	actionMapping[Input::KEY_F12] = new int(DIK_F12);
	actionMapping[Input::KEY_F13] = new int(DIK_F13);
	actionMapping[Input::KEY_F14] = new int(DIK_F14);
	actionMapping[Input::KEY_F15] = new int(DIK_F15);
	actionMapping[Input::KEY_KANA] = new int(DIK_KANA);
	actionMapping[Input::KEY_ABNT_C1] = new int(DIK_ABNT_C1);
	actionMapping[Input::KEY_CONVERT] = new int(DIK_CONVERT);
	actionMapping[Input::KEY_NOCONVERT] = new int(DIK_NOCONVERT);
	actionMapping[Input::KEY_YEN] = new int(DIK_YEN);
	actionMapping[Input::KEY_ABNT_C2] = new int(DIK_ABNT_C2);
	actionMapping[Input::KEY_NUMPADEQUALS] = new int(DIK_NUMPADEQUALS);
	actionMapping[Input::KEY_PREVTRACK] = new int(DIK_PREVTRACK);
	actionMapping[Input::KEY_AT] = new int(DIK_AT);
	actionMapping[Input::KEY_COLON] = new int(DIK_COLON);
	actionMapping[Input::KEY_UNDERLINE] = new int(DIK_UNDERLINE);
	actionMapping[Input::KEY_KANJI] = new int(DIK_KANJI);
	actionMapping[Input::KEY_STOP] = new int(DIK_STOP);
	actionMapping[Input::KEY_AX] = new int(DIK_AX);
	actionMapping[Input::KEY_UNLABELED] = new int(DIK_UNLABELED);
	actionMapping[Input::KEY_NEXTTRACK] = new int(DIK_NEXTTRACK);
	actionMapping[Input::KEY_NUMPADENTER] = new int(DIK_NUMPADENTER);
	actionMapping[Input::KEY_RCONTROL] = new int(DIK_RCONTROL);
	actionMapping[Input::KEY_MUTE] = new int(DIK_MUTE);
	actionMapping[Input::KEY_CALCULATOR] = new int(DIK_CALCULATOR);
	actionMapping[Input::KEY_PLAYPAUSE] = new int(DIK_PLAYPAUSE);
	actionMapping[Input::KEY_MEDIASTOP] = new int(DIK_MEDIASTOP);
	actionMapping[Input::KEY_VOLUMEDOWN] = new int(DIK_VOLUMEDOWN);
	actionMapping[Input::KEY_VOLUMEUP] = new int(DIK_VOLUMEUP);
	actionMapping[Input::KEY_WEBHOME] = new int(DIK_WEBHOME);
	actionMapping[Input::KEY_NUMPADCOMMA] = new int(DIK_NUMPADCOMMA);
	actionMapping[Input::KEY_DIVIDE] = new int(DIK_DIVIDE);
	actionMapping[Input::KEY_SYSRQ] = new int(DIK_SYSRQ);
	actionMapping[Input::KEY_RMENU] = new int(DIK_RMENU);
	actionMapping[Input::KEY_PAUSE] = new int(DIK_PAUSE);
	actionMapping[Input::KEY_HOME] = new int(DIK_HOME);
	actionMapping[Input::KEY_UP] = new int(DIK_UP);
	actionMapping[Input::KEY_PRIOR] = new int(DIK_PRIOR);
	actionMapping[Input::KEY_LEFT] = new int(DIK_LEFT);
	actionMapping[Input::KEY_RIGHT] = new int(DIK_RIGHT);
	actionMapping[Input::KEY_END] = new int(DIK_END);
	actionMapping[Input::KEY_DOWN] = new int(DIK_DOWN);
	actionMapping[Input::KEY_NEXT] = new int(DIK_NEXT);
	actionMapping[Input::KEY_INSERT] = new int(DIK_INSERT);
	actionMapping[Input::KEY_DELETE] = new int(DIK_DELETE);
	actionMapping[Input::KEY_LWIN] = new int(DIK_LWIN);
	actionMapping[Input::KEY_RWIN] = new int(DIK_RWIN);
	actionMapping[Input::KEY_APPS] = new int(DIK_APPS);
	actionMapping[Input::KEY_POWER] = new int(DIK_POWER);
	actionMapping[Input::KEY_SLEEP] = new int(DIK_SLEEP);
	actionMapping[Input::KEY_WAKE] = new int(DIK_WAKE);
	actionMapping[Input::KEY_WEBSEARCH] = new int(DIK_WEBSEARCH);
	actionMapping[Input::KEY_WEBFAVORITES] = new int(DIK_WEBFAVORITES);
	actionMapping[Input::KEY_WEBREFRESH] = new int(DIK_WEBREFRESH);
	actionMapping[Input::KEY_WEBSTOP] = new int(DIK_WEBSTOP);
	actionMapping[Input::KEY_WEBFORWARD] = new int(DIK_WEBFORWARD);
	actionMapping[Input::KEY_WEBBACK] = new int(DIK_WEBBACK);
	actionMapping[Input::KEY_MYCOMPUTER] = new int(DIK_MYCOMPUTER);
	actionMapping[Input::KEY_MAIL] = new int(DIK_MAIL);
	actionMapping[Input::KEY_MEDIASELECT] = new int(DIK_MEDIASELECT);
	actionMapping[Input::MOUSE_X] = new int(DIMOFS_X);
	actionMapping[Input::MOUSE_Y] = new int(DIMOFS_Y);
	actionMapping[Input::MOUSE_Z] = new int(DIMOFS_Z);
	actionMapping[Input::MOUSE_BUTTON0] = new int(DIMOFS_BUTTON0);
	actionMapping[Input::MOUSE_BUTTON1] = new int(DIMOFS_BUTTON1);
	actionMapping[Input::MOUSE_BUTTON2] = new int(DIMOFS_BUTTON2);
	actionMapping[Input::MOUSE_BUTTON3] = new int(DIMOFS_BUTTON3);
	actionMapping[Input::MOUSE_BUTTON4] = new int(DIMOFS_BUTTON4);
	actionMapping[Input::MOUSE_BUTTON5] = new int(DIMOFS_BUTTON5);
	actionMapping[Input::MOUSE_BUTTON6] = new int(DIMOFS_BUTTON6);
	actionMapping[Input::MOUSE_BUTTON7] = new int(DIMOFS_BUTTON7);

}