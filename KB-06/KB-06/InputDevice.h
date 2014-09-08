#ifndef __INPUT_INPUTDEVICE_H__
#define __INPUT_INPUTDEVICE_H__

//Define version to directinput version 8.
//If not defined, it will default to version 8 as well, but we like a sense of security.
#define DIRECTINPUT_VERSION 0x0800

#include "LoggerPool.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

namespace Input
{
	class InputDevice
	{
	public:
		InputDevice();
		bool AcquireDevice();
		void ReleaseDevice();
		virtual bool Update() = 0;
		virtual long GetStateOf(int p_key) = 0;

	protected:
		std::string m_deviceName;
		bool m_deviceAcquired;
		LPDIRECTINPUTDEVICE8 m_dInputDevice;
		Logger::Logger* logger;
	};
}

#endif