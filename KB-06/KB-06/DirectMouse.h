#ifndef __INPUT_DIRECTMOUSE_H__
#define __INPUT_DIRECTMOUSE_H__

#include "DirectInputDevice.h"
#include "LoggerPool.h"

namespace pengine
{
	class DirectMouse : public DirectInputDevice
	{
	public:
		DirectMouse();
		~DirectMouse();
		bool Initialize(LPDIRECTINPUT8, HWND);
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