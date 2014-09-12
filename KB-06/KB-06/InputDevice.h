#ifndef __INPUT_INPUTDEVICE_H__
#define __INPUT_INPUTDEVICE_H__

#include "LoggerPool.h"
#include "Input.h"
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
		virtual std::map<Input, long>* GetInputValues() = 0;
		
		void SetActionMapping(std::map<Input, int>* actionMapping);

	protected:
		std::map<Input, int>* actionMapping;
		std::string m_deviceName;
		bool m_deviceAcquired;
		Logger::Logger* logger;

	};
}

#endif