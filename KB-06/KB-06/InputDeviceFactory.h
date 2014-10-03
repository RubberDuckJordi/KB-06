#ifndef _PENGINE_INPUTDEVICEFACTORY_H_
#define _PENGINE_INPUTDEVICEFACTORY_H_

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