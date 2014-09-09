#include "DirectInputDeviceFactory.h"
#include "LoggerPool.h"

Input::DirectInputDeviceFactory::DirectInputDeviceFactory()
{
	m_dInput = NULL;
	if (SUCCEEDED(DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_dInput,
		NULL)))
	{
		logger->Log(Logger::Logger::DEBUG, "DirectInputDeviceFactory: Initialised factory");
	}
	else
	{
		logger->Log(Logger::Logger::ERR, "DirectInputDeviceFactory: Initialisation failed");

	}
}
Input::DirectInputDeviceFactory::~DirectInputDeviceFactory()
{
	if (m_dInput != NULL)
	{
		m_dInput->Release();
		m_dInput = NULL;
	}
	InputDeviceFactory::~InputDeviceFactory();
}
Input::InputDevice* Input::DirectInputDeviceFactory::CreateInputDevice(InputDevice::Type type, Window::Window* window)
{
	DirectInputDevice* newDevice = NULL;

	switch (type)
	{
	case InputDevice::KEYBOARD:
		newDevice = new DirectKeyboard();
		logger->Log(Logger::Logger::DEBUG, "DirectInputDeviceFactory: Created keyboard");
		break;
	case InputDevice::MOUSE:
		newDevice = new DirectMouse();
		logger->Log(Logger::Logger::DEBUG, "DirectInputDeviceFactory: Created mouse");
		break;
	default:
		logger->Log(Logger::Logger::ERR, "DirectInputDeviceFactory: Unable to create device, unknown device type");
		return NULL;
	}

	if (newDevice->Initialize(window->GetHWND(), m_dInput))
	{
		return newDevice;
	}
	else
	{
		logger->Log(Logger::Logger::ERR, "DirectInputDeviceFactory: Unable to create device, initialisation failed");
		delete newDevice;
		return NULL;
	}
}