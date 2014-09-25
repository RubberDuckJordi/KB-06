#include "InputDevice.h"

Input::InputDevice::InputDevice()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}

Input::InputDevice::~InputDevice()
{
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}