#ifndef _PENGINE_INPUTMANAGER_H_
#define _PENGINE_INPUTMANAGER_H_

#include "InputDeviceFactory.h"
#include "Window.h"
#include "WindowListener.h"
#include "LoggerPool.h"
#include "Input.h"
#include <windows.h>
#include <vector>
#include <string>
#include  "Logger.h"

/*
This manager is responsible for instantiating, updating and managing
all input functionality.
*/
namespace pengine
{
	class InputManager : public WindowListener
	{
	public:
		// inputDeviceFactory must be passed so that the input manager can create input devices without knowing about the implementation
		InputManager(InputDeviceFactory* inputDeviceFactory);
		~InputManager();
		// Must be called after creating. Some frameworks require a HWND to initialise the input devices
		void Initialise(HWND hwnd);
		// Returns all input actions of the last tick
		std::map<Input, long>* GetCurrentActions();
		// See WindowListener
		void OnWindowCreated(Window* window);
		void OnWindowFocusGained(Window* window);
		void OnWindowFocusLost(Window* window);

	private:
		std::list<InputDevice*> inputDevices;
		Logger* logger;
		bool initialised;

		InputDeviceFactory* inputDeviceFactory;
	};
}
#endif