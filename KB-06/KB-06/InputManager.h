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
		void Initialise(HWND hwnd);
		std::map<Input, long>* GetCurrentActions();
		void OnWindowCreated(Window::Window* window);
		void OnWindowFocusGained(Window::Window* window);
		void OnWindowFocusLost(Window::Window* window);

	private:
		std::list<InputDevice*> inputDevices;
		Logger::Logger* logger;
		bool initialised;

		InputDeviceFactory* inputDeviceFactory;

	};
}
#endif