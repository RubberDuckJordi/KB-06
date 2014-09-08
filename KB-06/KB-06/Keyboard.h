#ifndef __INPUT_KEYBOARD_H__
#define __INPUT_KEYBOARD_H__

#include "InputDevice.h"
#include "LoggerPool.h"

namespace Input
{
	class Keyboard : public InputDevice
	{
	public:
		Keyboard();
		bool Initialize(HWND, LPDIRECTINPUT8);
		bool Update();
		long GetStateOf(int);

	private:
		char m_KeyBuffer[256];
		Logger::Logger* logger;
	};
}
#endif