#ifndef __INPUT_INPUTMANAGER_H__
#define __INPUT_INPUTMANAGER_H__

#include "InputDeviceFactory.h"
#include "Window.h"
#include "WindowListener.h"
#include "LoggerPool.h"
#include "Input.h"
#include <windows.h>
#include <map>
#include <vector>
#include <string>


namespace Input
{
	class InputManager : public Window::WindowListener
	{
	public:
		InputManager(InputDeviceFactory* inputDeviceFactory);
		~InputManager();
		std::map<Input, long> GetCurrentActions(Window::Window*);
		void AddWindow(Window::Window*);
		void RemoveWindow(Window::Window&);
		void RemoveWindows();
		void WindowClosed(Window::Window& p_window);
		void WindowOpened(Window::Window& p_window);

	private:
		std::map<std::pair<InputDevice::Type, int>, Input> m_keyMapping;
		std::map<Window::Window*, std::list<InputDevice*>> m_windowDevices;

		InputDeviceFactory* inputDeviceFactory;

		Logger::Logger* logger;
	};
}
#endif