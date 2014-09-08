#ifndef __INPUT_INPUTMANAGER_H__
#define __INPUT_INPUTMANAGER_H__

//Define version to directinput version 8.
//If not defined, it will default to version 8 as well, but we like a sense of security.
#define DIRECTINPUT_VERSION 0x0800 

#include "InputDevice.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Window.h"
#include "WindowListener.h"
#include "LoggerPool.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <vector>
#include <string>
#include <dinput.h>

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

		enum InputDeviceType
		{
			KEYBOARD,
			MOUSE,
			JOYSTICK
		};


		InputManager();
		~InputManager();
		std::map<Action, long> GetCurrentActions(Window::Window*);
		void AddWindow(Window::Window*);
		void RemoveWindow(Window::Window&);
		void RemoveWindows();
		void WindowClosed(Window::Window& p_window);
		void WindowOpened(Window::Window& p_window);

	private:
		LPDIRECTINPUT8 m_dInput;
		std::map<std::pair<InputDeviceType, int>, Action> m_keyMapping;
		std::map<Window::Window*, std::map<InputDeviceType, InputDevice*>> m_windowDevices;

		void Initialize();
		void LoadKeyMapping();
		Logger::Logger* logger;
	};
}
#endif