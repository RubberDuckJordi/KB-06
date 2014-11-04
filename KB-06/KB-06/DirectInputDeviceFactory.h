#ifndef _PENGINE_DIRECTINPUTDEVICEFACTORY_H_
#define _PENGINE_DIRECTINPUTDEVICEFACTORY_H_

#include "DirectKeyboard.h"
#include "DirectMouse.h"
#include "InputDeviceFactory.h"
#include "Input.h"
#include <map>

/*
Implementation of InputDeviceFactory
Responsible for creating all DirectInputDevice implementations

This factory initialises the actionMapping (from DirectInput to our Input enum) once
and sets a pointer to the mapping for every created input device.
*/

namespace pengine
{
	class DirectInputDeviceFactory : public InputDeviceFactory
	{
	public:
		DirectInputDeviceFactory();
		~DirectInputDeviceFactory();
		void Initialise(HWND hWnd);
		InputDevice* CreateInputDevice(InputDevice::Type type);
	private:
		void CreateActionMapping();
		LPDIRECTINPUT8 dInput;
		std::map<Input, int>* actionMapping;
		HWND hwnd;
	};
}
#endif