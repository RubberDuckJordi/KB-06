#include "DirectInputDevice.h"

pengine::DirectInputDevice::DirectInputDevice()
{
	dInputDevice = NULL;
	deviceAcquired = false;
}

pengine::DirectInputDevice::~DirectInputDevice()
{
	if (dInputDevice)
	{
		dInputDevice->Unacquire();
		dInputDevice->Release();
		delete dInputDevice;
	}
	InputDevice::~InputDevice();
}

void pengine::DirectInputDevice::ReleaseDevice()
{
	if (dInputDevice)
	{
		dInputDevice->Unacquire();
		//dInputDevice->Release();
		//dInputDevice = NULL;

		deviceAcquired = false;
	}
}

bool pengine::DirectInputDevice::AcquireDevice()
{
	int times = 5;
	for (int i = 0; i < times; i++)
	{
		if (SUCCEEDED(dInputDevice->Acquire()))
		{
			logger->Log(Logger::INFO, "InputManager::InputDevice " + deviceName + " acquired.");

			deviceAcquired = true;

			return true;
		}
	}
	return false;
}

void pengine::DirectInputDevice::SetActionMapping(std::map<Input, int>* p_actionMapping)
{
	actionMapping = p_actionMapping;
}