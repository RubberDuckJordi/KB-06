#include "DirectInputDevice.h"

Input::DirectInputDevice::DirectInputDevice()
{
	dInputDevice = NULL;
	deviceAcquired = false;
}

Input::DirectInputDevice::~DirectInputDevice()
{
	if (dInputDevice)
	{
		dInputDevice->Unacquire();
		dInputDevice->Release();
		delete dInputDevice;
	}
	InputDevice::~InputDevice();
}

void Input::DirectInputDevice::ReleaseDevice()
{
	if (dInputDevice)
	{
		dInputDevice->Unacquire();
		//dInputDevice->Release();
		//dInputDevice = NULL;

		deviceAcquired = false;
	}
}

bool Input::DirectInputDevice::AcquireDevice()
{
	int times = 5;

	for (int i = 0; i < times; i++)
	{
		if (SUCCEEDED(dInputDevice->Acquire()))
		{
			logger->Log(Logger::Logger::INFO, "InputManager::InputDevice " + deviceName + " acquired.");

			deviceAcquired = true;

			return true;
		}
	}

	return false;

}

void Input::DirectInputDevice::SetActionMapping(std::map<Input, int>* p_actionMapping)
{
	actionMapping = p_actionMapping;
}