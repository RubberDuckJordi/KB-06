#include "InputDeviceFactory.h"

Input::InputDeviceFactory::InputDeviceFactory()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}

Input::InputDeviceFactory::~InputDeviceFactory()
{
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}

std::map<Input::Input, void*>* Input::InputDeviceFactory::GetActionMapping(){
	return &actionMapping;
}