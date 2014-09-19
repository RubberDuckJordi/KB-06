#ifndef __INPUT_INPUTMANAGER_H__
#define __INPUT_INPUTMANAGER_H__

#include "InputDeviceFactory.h"
#include "Window.h"
#include "WindowListener.h"
#include "LoggerPool.h"
#include "Input.h"
#include <windows.h>
#include <vector>
#include <string>
#include  "Logger.h"

namespace Input
{
	class InputManager : public Window::WindowListener
	{
	public:
		InputManager(InputDeviceFactory* inputDeviceFactory);
		~InputManager();
		std::map<Input, long>* GetCurrentActions();
		void OnWindowFocusGained(Window::Window* p_window);
		void OnWindowFocusLost(Window::Window* p_window);

	private:
		std::list<InputDevice*> inputDevices;
		Logger::Logger* logger;

		InputDeviceFactory* inputDeviceFactory;

	};
}
#endif