#include "InputDevice.h"

pengine::InputDevice::InputDevice()
{
	logger = LoggerPool::GetInstance().GetLogger();
}

pengine::InputDevice::~InputDevice()
{
	LoggerPool::GetInstance().ReturnLogger(logger);
}