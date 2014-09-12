#ifndef __INPUT_DIRECTKEYBOARD_H__
#define __INPUT_DIRECTKEYBOARD_H__

#include "DirectInputDevice.h"
#include "LoggerPool.h"

//Define version to directinput version 8.
//If not defined, it will default to version 8 as well, but we like a sense of security.
#define DIRECTINPUT_VERSION 0x0800

namespace Input
{
	class DirectKeyboard : public DirectInputDevice
	{
	public:
		DirectKeyboard();
		~DirectKeyboard();
		bool Initialize(HWND, LPDIRECTINPUT8);
		bool Update();
		std::map<Input, long>* GetInputValues();

	private:
		long GetStateOf(int p_key);
		char m_KeyBuffer[256];
	};
}
#endif