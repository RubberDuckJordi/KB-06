#ifndef __INPUT_DIRECTINPUTDEVICEFACTORY_H__
#define __INPUT_DIRECTINPUTDEVICEFACTORY_H__

#include "DirectKeyboard.h"
#include "DirectMouse.h"
#include "InputDeviceFactory.h"
#include "Input.h"

#include <map>

namespace Input {
	class DirectInputDeviceFactory : public InputDeviceFactory 
	{
	public:
		DirectInputDeviceFactory();
		~DirectInputDeviceFactory();
		InputDevice* CreateInputDevice(InputDevice::Type type, Window::Window* window);
	private:
		void CreateActionMapping();
		LPDIRECTINPUT8 m_dInput;
	};
}

#endif