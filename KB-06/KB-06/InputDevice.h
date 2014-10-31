#ifndef _PENGINE_INPUTDEVICE_H_
#define _PENGINE_INPUTDEVICE_H_

#include "LoggerPool.h"
#include "Window.h"
#include "Input.h"
#include <windows.h>

/*
The InputDevice interface must be implemented by every input device
The InputManager will manage the interfaces, not the actual implementation.
As a result, the InputManager can remain completely independent of the implementations
of the inputdevices.
*/
namespace pengine
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

		// Should be called when OnWindowFocusGained is called, allows the input device to receive input
		virtual bool AcquireDevice() = 0;
		// Should be called when OnWindowFocusLost is called, makes sure the input device does not receive input anymore
		virtual void ReleaseDevice() = 0;
		// Updates the input actions of the tick, must make sure that GetInputValues contains the last input changes.
		virtual bool Update() = 0;
		// Returns a map of all input changes in the last tick
		virtual std::map<Input, long>* GetInputValues() = 0;
		// This method will be called from InputManager when a window lost focus
		virtual void OnWindowFocusLost(Window* window) = 0;
		// This method will be called from InputManager when a gains focus
		virtual void OnWindowFocusGained(Window* window) = 0;

	protected:
		// Used for logging purposes, provides a readable device name
		std::string deviceName;
		// Keeps track about device state
		bool deviceAcquired;
		Logger* logger;
	};
}
#endif