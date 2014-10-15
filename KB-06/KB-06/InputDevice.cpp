#include "InputDevice.h"

namespace pengine
{
	InputDevice::InputDevice()
	{
		logger = LoggerPool::GetInstance().GetLogger();
	}

	InputDevice::~InputDevice()
	{
	}
}