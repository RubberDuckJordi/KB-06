#include "InputDevice.h"

Input::InputDevice::InputDevice()
{
	m_dInputDevice = NULL;
	m_deviceAcquired = false;
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}

void Input::InputDevice::ReleaseDevice()
{
	if (m_dInputDevice)
	{
		m_dInputDevice->Unacquire();
		m_dInputDevice->Release();
		m_dInputDevice = NULL;

		m_deviceAcquired = false;
	}
}

bool Input::InputDevice::AcquireDevice()
{
	int times = 5;

	for (int i = 0; i < times; i++)
	{
		if (SUCCEEDED(m_dInputDevice->Acquire()))
		{
			logger->Log(Logger::Logger::INFO, "InputManager::InputDevice " + m_deviceName + " acquired.");

			m_deviceAcquired = true;

			return true;
		}
	}

	return false;

}