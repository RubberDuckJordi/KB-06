#include "InputDeviceFactory.h"

pengine::InputDeviceFactory::InputDeviceFactory()
{
	logger = LoggerPool::GetInstance().GetLogger();
}

pengine::InputDeviceFactory::~InputDeviceFactory()
{
	LoggerPool::GetInstance().ReturnLogger(logger);
}