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
		void AttachWindow(Window::Window*);
		void DetachWindow(Window::Window&);
		void DetachAllWindows();
		void WindowClosed(Window::Window& p_window);
		void WindowOpened(Window::Window& p_window);

	private:
		std::map<Window::Window*, std::list<InputDevice*>> windowDevices;

		InputDeviceFactory* inputDeviceFactory;

	};
}
#endif