#ifndef _PENGINE_INPUTDEVICEFACTORY_H_
#define _PENGINE_INPUTDEVICEFACTORY_H_

#include "InputDevice.h"
#include "LoggerPool.h"
#include "Input.h"
#include "Window.h"

/*
Every input framework implementation must implement this factory.
This factory creates an InputDevice implementation, based on the Type parameter.
The factory can be passed to the InputManager. The InputManager creates the correct
input devices.

As a result, the inputmanager is not aware of the input implementation, it only knows
that it creates an implementation of InputDevice and it's type.
*/
namespace pengine
{
	class InputDeviceFactory
	{
	public:
		InputDeviceFactory();
		~InputDeviceFactory();
		// Initialise will be called after InputManager is initialised. Some frameworks require a HWND for input devices to be created.
		virtual void Initialise(HWND hWnd) = 0;
		// Must create an inputDevice implementation
		virtual InputDevice* CreateInputDevice(InputDevice::Type type) = 0;
	protected:
		Logger* logger;
	};
}
#endif