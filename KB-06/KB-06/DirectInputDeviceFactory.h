#ifndef __INPUT_DIRECTINPUTDEVICEFACTORY_H__
#define __INPUT_DIRECTINPUTDEVICEFACTORY_H__

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