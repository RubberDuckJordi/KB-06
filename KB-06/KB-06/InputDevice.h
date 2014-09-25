#ifndef __INPUT_INPUTDEVICE_H__
#define __INPUT_INPUTDEVICE_H__

#include "LoggerPool.h"
#include "Window.h"
#include "Input.h"
#include <windows.h>

namespace Input
{
	class InputDevice
	{
	public:
		enum Type
		{
			KEYBOARD,
			MOUSE,
			JOYSTICK
		};

		InputDevice();
		~InputDevice();

		virtual bool AcquireDevice() = 0;
		virtual void ReleaseDevice() = 0;
		virtual bool Update() = 0;
		virtual std::map<Input, long>* GetInputValues() = 0;
		virtual void OnWindowFocusLost(Window::Window* window) = 0;
		virtual void OnWindowFocusGained(Window::Window* window) = 0;

	protected:
		std::string deviceName;
		bool deviceAcquired;
		Logger::Logger* logger;
	};
}
#endif