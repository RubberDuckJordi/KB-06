#include "DirectMouse.h"
#include "LoggerPool.h"

Input::DirectMouse::DirectMouse()
{
	m_deviceName = "Mouse";
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}

//Create the new DirectInputDevice, add a handler to its window and
//set the required settings to be able to poll it.
bool Input::DirectMouse::Initialize(HWND p_hWnd, LPDIRECTINPUT8 p_dInput)
{
	HRESULT hr = p_dInput->CreateDevice(GUID_SysMouse, &m_dInputDevice, NULL);
	if (FAILED(hr))
	{
		ReleaseDevice();
		logger->Log(Logger::Logger::WARNING, "InputDevice::Mouse: Initialisation failed. Unable to create Input Device.");
		return false;
	}

	hr = m_dInputDevice->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr))
	{
		ReleaseDevice();
		logger->Log(Logger::Logger::WARNING, "InputDevice::Mouse: Initialisation failed. Unable to set dataformat.");
		return false;
	}

	//The coorperative level has to be Exclusive and foreground to manage
	//focussing for this device.
	hr = m_dInputDevice->SetCooperativeLevel(p_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		ReleaseDevice();
		logger->Log(Logger::Logger::WARNING, "InputDevice::Mouse: Initialisation failed. Unable to set Cooperative Level.");
		return false;
	}

	//Make a new property to get absolute mousepositions instead of default
	//relative positions. Relative positions only show up when asked at the
	//right moment. Since we use a framebased status polling, we need the
	//changed value.
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_ABS;

	hr = m_dInputDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
	if (FAILED(hr))
	{
		ReleaseDevice();
		logger->Log(Logger::Logger::WARNING, "InputDevice::Mouse: Initialisation failed. Unable to set property Axismode.");

		return false;
	}

	DirectInputDevice::AcquireDevice();
	logger->Log(Logger::Logger::INFO, "InputDevice::Mouse: Initialisation successful.");

	return true;
}

//Update the directinputstate only if it can be acquired and polled.
bool Input::DirectMouse::Update()
{
	bool result = false;
	if (!m_deviceAcquired)
	{
		result = DirectInputDevice::AcquireDevice();
	}
	else if (!SUCCEEDED(m_dInputDevice->Poll()))
	{
		if (m_deviceAcquired)
		{
			m_deviceAcquired = false;
			logger->Log(Logger::Logger::INFO, "InputManager: Mouse focus lost");
			ShowCursor(true);
		}
		result = DirectInputDevice::AcquireDevice();
	}

	if (FAILED(m_dInputDevice->GetDeviceState(sizeof(DIMOUSESTATE2), (LPVOID)&m_dIMouseState)))
	{
		result = false;
	}

	if (result == true)
	{
		m_previousXPos = m_dIMouseState.lX;
		m_previousYPos = m_dIMouseState.lY;
		m_previousZPos = m_dIMouseState.lZ;
	}

	return m_deviceAcquired;
}

//Returns the state of a mouseproperty (like a button or axis. Returns 0 if
//value hasn't changed or button isn't pressed. Otherwise returns the value
//of the property or 100 at a buttonpress. 100 because in the future we can
//work with percentages.
//p_mouseProperty should be a defined value in dinput.h beginning with:
//"DIMOFS_"
long Input::DirectMouse::GetStateOf(int p_mouseProperty)
{
	Update();
	long state = 0;
	switch (p_mouseProperty)
	{
	case DIMOFS_X:
		state = GetDeltaXPosition();
		break;
	case DIMOFS_Y:
		state = GetDeltaYPosition();
		break;
	case DIMOFS_Z:
		state = GetDeltaZPosition();
		break;
	case DIMOFS_BUTTON0:
		if (m_dIMouseState.rgbButtons[0] & 0x80)
		{
			state = 100;
		}
		break;
	case DIMOFS_BUTTON1:
		if (m_dIMouseState.rgbButtons[1] & 0x80)
		{
			state = 100;
		}
		break;
	case DIMOFS_BUTTON2:
		if (m_dIMouseState.rgbButtons[2] & 0x80)
		{
			state = 100;
		}
		break;
	case DIMOFS_BUTTON3:
		if (m_dIMouseState.rgbButtons[3] & 0x80)
		{
			state = 100;
		}
		break;
	case DIMOFS_BUTTON4:
		if (m_dIMouseState.rgbButtons[4] & 0x80)
		{
			state = 100;
		}
		break;
	case DIMOFS_BUTTON5:
		if (m_dIMouseState.rgbButtons[5] & 0x80)
		{
			state = 100;
		}
		break;
	case DIMOFS_BUTTON6:
		if (m_dIMouseState.rgbButtons[6] & 0x80)
		{
			state = 100;
		}
		break;
	case DIMOFS_BUTTON7:
		if (m_dIMouseState.rgbButtons[7] & 0x80)
		{
			state = 100;
		}
		break;
	}
	return state;
}

//Returns the position compared to the previous position of the X axis.
long Input::DirectMouse::GetDeltaXPosition()
{
	long delta = m_dIMouseState.lX - m_previousXPos;
	m_previousXPos = m_dIMouseState.lX;
	if (delta > 10000 && delta < -10000)
	{
		delta = 0;
	}
	return delta;
}

//Returns the position compared to the previous position of the Y axis.
long Input::DirectMouse::GetDeltaYPosition()
{
	long delta = m_dIMouseState.lY - m_previousYPos;
	m_previousYPos = m_dIMouseState.lY;
	if (delta > 10000 && delta < -10000)
	{
		delta = 0;
	}
	return delta;
}

//Returns the position compared to the previous position of the Z axis.
//The Z axis is the scrollweel. Every movement stands for 120 delta or less
//or more depending on the mouse.
long Input::DirectMouse::GetDeltaZPosition()
{
	long delta = m_dIMouseState.lZ - m_previousZPos;
	m_previousZPos = m_dIMouseState.lZ;
	if (delta > 10000 && delta < -10000)
	{
		delta = 0;
	}
	return delta;
}