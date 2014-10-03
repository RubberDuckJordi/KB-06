#ifndef _PENGINE_DIRECTINPUTDEVICEFACTORY_H_
#define _PENGINE_DIRECTINPUTDEVICEFACTORY_H_

#include "DirectKeyboard.h"
#include "DirectMouse.h"
#include "InputDeviceFactory.h"
#include "Input.h"
#include <map>

namespace pengine
{
	class DirectInputDeviceFactory : public InputDeviceFactory
	{
	public:
		DirectInputDeviceFactory();
		~DirectInputDeviceFactory();
		void Initialise(HWND);
		InputDevice* CreateInputDevice(InputDevice::Type type);
	private:
		void CreateActionMapping();
		LPDIRECTINPUT8 dInput;
		std::map<Input, int>* actionMapping;
		HWND hwnd;
	};
}
#endif