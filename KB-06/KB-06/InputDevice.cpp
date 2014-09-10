#include "InputDevice.h"

Input::InputDevice::InputDevice()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}
Input::InputDevice::~InputDevice()
{
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}

void Input::InputDevice::SetActionMapping(std::map<Input, void*>* p_actionMapping)
{
	actionMapping = p_actionMapping;
}