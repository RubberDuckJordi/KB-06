#ifndef _PENGINE_DIRECTKEYBOARD_H_
#define _PENGINE_DIRECTKEYBOARD_H_

#include "DirectInputDevice.h"
#include "LoggerPool.h"

//Define version to directinput version 8.
//If not defined, it will default to version 8 as well, but we like a sense of security.
#define DIRECTINPUT_VERSION 0x0800

namespace pengine
{
	class DirectKeyboard : public DirectInputDevice
	{
	public:
		DirectKeyboard();
		~DirectKeyboard();
		bool Initialize(LPDIRECTINPUT8, HWND hwnd);
		bool Update();
		std::map<Input, long>* GetInputValues();
		void OnWindowFocusLost(Window* window);
		void OnWindowFocusGained(Window* window);

	private:
		long GetStateOf(int p_key);
		char m_KeyBuffer[256];
	};
}
#endif