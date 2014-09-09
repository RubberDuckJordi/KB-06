#include "InputDeviceFactory.h"

Input::InputDeviceFactory::InputDeviceFactory()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}
Input::InputDeviceFactory::~InputDeviceFactory()
{
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}