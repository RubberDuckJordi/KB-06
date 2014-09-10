#ifndef __INPUT_DIRECTMOUSE_H__
#define __INPUT_DIRECTMOUSE_H__

#include "DirectInputDevice.h"
#include "LoggerPool.h"

namespace Input
{
	class DirectMouse : public DirectInputDevice
	{
	public:
		DirectMouse();
		bool Initialize(HWND, LPDIRECTINPUT8);
		bool Update();
		std::map<Input, long>* GetInputValues();

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