#ifndef __INPUT_INPUTMANAGER_H__
#define __INPUT_INPUTMANAGER_H__

#include "InputDeviceFactory.h"
#include "Window.h"
#include "WindowListener.h"
#include "LoggerPool.h"
#include <windows.h>
#include <map>
#include <vector>
#include <string>


namespace Input
{
	class InputManager : public Window::WindowListener
	{
	public:
		enum Action
		{
			UP,
			DOWN,
			LEFT,
			RIGHT,
			FORWARD,
			BACKWARD,
			TOWARD,
			AWAY,
			CURSOR_X,
			CURSOR_Y,
			CURSOR_Z,
			JUMP,
			CAMERA_NEXT,
			CAMERA_PREVIOUS,
			CAMERA_FIRST,
			CAMERA_LAST,
			WINDOW_EXIT
		};

		InputManager(InputDeviceFactory* inputDeviceFactory);
		~InputManager();
		std::map<Action, long> GetCurrentActions(Window::Window*);
		void AddWindow(Window::Window*);
		void RemoveWindow(Window::Window&);
		void RemoveWindows();
		void WindowClosed(Window::Window& p_window);
		void WindowOpened(Window::Window& p_window);

	private:
		std::map<std::pair<InputDevice::Type, int>, Action> m_keyMapping;
		std::map<Window::Window*, std::map<InputDevice::Type, InputDevice*>> m_windowDevices;

		InputDeviceFactory* inputDeviceFactory;

		void Initialize();
		void LoadKeyMapping();
		Logger::Logger* logger;
	};
}
#endif