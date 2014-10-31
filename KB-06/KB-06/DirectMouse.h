#ifndef _PENGINE_DIRECTMOUSE_H_
#define _PENGINE_DIRECTMOUSE_H_

#include "DirectInputDevice.h"
#include "LoggerPool.h"

namespace pengine
{
	class DirectMouse : public DirectInputDevice
	{
	public:
		DirectMouse();
		~DirectMouse();
		// Initialises the input device, returns false in case of failure
		bool Initialise(LPDIRECTINPUT8 directInput, HWND hwnd);
		// Updates the current input actions, returns false in case of failure
		bool Update();
		std::map<Input, long>* GetInputValues();

		void OnWindowFocusLost(Window* window);
		void OnWindowFocusGained(Window* window);

	private:
		DIMOUSESTATE2 dIMouseState;
		long previousXPos;
		long previousYPos;
		long previousZPos;

		long GetDeltaXPosition();
		long GetDeltaYPosition();
		long GetDeltaZPosition();
	};
}
#endif