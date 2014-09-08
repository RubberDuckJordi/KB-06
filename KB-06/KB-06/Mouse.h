#ifndef __INPUT_MOUSE_H__
#define __INPUT_MOUSE_H__

#include "InputDevice.h"
#include "LoggerPool.h"

namespace Input
{
	class Mouse : public InputDevice
	{
	public:
		Mouse();
		bool Initialize(HWND, LPDIRECTINPUT8);
		bool Update();
		long GetStateOf(int);

	private:
		DIMOUSESTATE2 m_dIMouseState;
		long m_previousXPos;
		long m_previousYPos;
		long m_previousZPos;

		long GetDeltaXPosition();
		long GetDeltaYPosition();
		long GetDeltaZPosition();

		Logger::Logger* logger;
	};
}
#endif