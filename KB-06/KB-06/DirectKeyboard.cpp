#include "DirectKeyboard.h"

Input::DirectKeyboard::DirectKeyboard()
{
	m_deviceName = "Keyboard";
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}

//Create the new DirectInputDevice, add a handler to its window and
//set the required settings to be able to poll it.
bool Input::DirectKeyboard::Initialize(HWND p_hWnd, LPDIRECTINPUT8 m_dInput)
{
	HRESULT hr = m_dInput->CreateDevice(GUID_SysKeyboard, &m_dInputDevice, NULL);
	if FAILED(hr)
	{
		ReleaseDevice();
		logger->Log(Logger::Logger::WARNING, "InputDevice::Keyboard: Initialisation failed. Unable to create Input Device.");
		return false;
	}

	hr = m_dInputDevice->SetDataFormat(&c_dfDIKeyboard);
	if FAILED(hr)
	{
		ReleaseDevice();
		logger->Log(Logger::Logger::WARNING, "InputDevice::Keyboard: Initialisation failed. Unable to set dataformat.");
		return false;
	}

	hr = m_dInputDevice->SetCooperativeLevel(p_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if FAILED(hr)
	{
		ReleaseDevice();
		logger->Log(Logger::Logger::WARNING, "InputDevice::Keyboard: Initialisation failed. Unable to set Cooperative Level.");
		return false;
	}

	AcquireDevice();
	logger->Log(Logger::Logger::INFO, "InputDevice::Keyboard: Initialisation successful.");

	return true;
}

bool Input::DirectKeyboard::Update()
{
	if (!SUCCEEDED(m_dInputDevice->Poll()))
	{
		if (m_deviceAcquired)
		{
			logger->Log(Logger::Logger::INFO, "InputManager: Keyboard focus lost.");
			m_deviceAcquired = false;
		}
		AcquireDevice();
	}

	if (FAILED(m_dInputDevice->GetDeviceState(sizeof(m_KeyBuffer), (LPVOID)&m_KeyBuffer)))
	{
		return false;
	}

	return true;
}

//Returns 100 if given key is being pressed at the moment
long Input::DirectKeyboard::GetStateOf(int p_key)
{
	if (!SUCCEEDED(m_dInputDevice->Poll()))
	{
		return 0;
	}
	else if (m_KeyBuffer[p_key] & 0x80)
	{
		return 100;
	}
	else
	{
		return 0;
	}
}