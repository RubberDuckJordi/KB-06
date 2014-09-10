#ifndef __INPUT_INPUTDEVICE_H__
#define __INPUT_INPUTDEVICE_H__

#include "LoggerPool.h"
#include <windows.h>

namespace Input
{
	class InputDevice
	{
	public:
		InputDevice();
		~InputDevice();
		enum Type
		{
			KEYBOARD,
			MOUSE,
			JOYSTICK
		};

		virtual bool AcquireDevice() = 0;
		virtual void ReleaseDevice() = 0;
		virtual bool Update() = 0;
		virtual long GetStateOf(int p_key) = 0;

	protected:
		std::string m_deviceName;
		bool m_deviceAcquired;
		Logger::Logger* logger;
	};
}

#endif