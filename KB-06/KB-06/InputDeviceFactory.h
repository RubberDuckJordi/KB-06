#ifndef __INPUT_INPUTDEVICEFACTORY_H__
#define __INPUT_INPUTDEVICEFACTORY_H__

#include "InputDevice.h"
#include "LoggerPool.h"
#include "Input.h"
#include "Window.h"

namespace pengine
{
	class InputDeviceFactory
	{
	public:
		InputDeviceFactory();
		~InputDeviceFactory();
		virtual void Initialise(HWND) = 0;
		virtual InputDevice* CreateInputDevice(InputDevice::Type type) = 0;
	protected:
		Logger* logger;
	};
}
#endif