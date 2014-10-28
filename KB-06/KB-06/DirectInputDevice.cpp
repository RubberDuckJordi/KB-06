#include "DirectInputDevice.h"

namespace pengine
{
	DirectInputDevice::DirectInputDevice()
	{
		dInputDevice = NULL;
		deviceAcquired = false;
	}

	DirectInputDevice::~DirectInputDevice()
	{
		if (dInputDevice)
		{
			dInputDevice->Unacquire();
			dInputDevice->Release();
			delete dInputDevice;
		}
		InputDevice::~InputDevice();

		delete actionMapping;
	}

	void DirectInputDevice::ReleaseDevice()
	{
		if (dInputDevice)
		{
			dInputDevice->Unacquire();
			//dInputDevice->Release();
			//dInputDevice = NULL;

			deviceAcquired = false;
		}
	}

	bool DirectInputDevice::AcquireDevice()
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

	void DirectInputDevice::SetActionMapping(std::map<Input, int>* p_actionMapping)
	{
		actionMapping = p_actionMapping;
	}
}