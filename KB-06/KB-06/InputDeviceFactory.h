#ifndef __INPUT_INPUTDEVICEFACTORY_H__
#define __INPUT_INPUTDEVICEFACTORY_H__

#include "InputDevice.h"
#include "LoggerPool.h"
#include "Window.h"

namespace Input {
	class InputDeviceFactory 
	{
	public:
		InputDeviceFactory();
		~InputDeviceFactory();
		virtual InputDevice* CreateInputDevice(InputDevice::Type type, Window::Window* window) = 0;
	protected:
		Logger::Logger* logger;
	};
}

#endif