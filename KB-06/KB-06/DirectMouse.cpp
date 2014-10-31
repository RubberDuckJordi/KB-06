#include "DirectMouse.h"
#include "LoggerPool.h"

namespace pengine
{
	DirectMouse::DirectMouse()
	{
		deviceName = "Mouse";
	}

	DirectMouse::~DirectMouse()
	{
		DirectInputDevice::~DirectInputDevice();
	}

	//Create the new DirectInputDevice, add a handler to its window and
	//set the required settings to be able to poll it.
	bool DirectMouse::Initialise(LPDIRECTINPUT8 p_dInput, HWND hwnd)
	{
		HRESULT hr = p_dInput->CreateDevice(GUID_SysMouse, &dInputDevice, NULL);
		if (FAILED(hr))
		{
			ReleaseDevice();
			logger->Log(Logger::WARNING, "InputDevice::Mouse: Initialisation failed. Unable to create Input Device.");
			return false;
		}

		hr = dInputDevice->SetDataFormat(&c_dfDIMouse2);
		if (FAILED(hr))
		{
			ReleaseDevice();
			logger->Log(Logger::WARNING, "InputDevice::Mouse: Initialisation failed. Unable to set dataformat.");
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

		hr = dInputDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
		if (FAILED(hr))
		{
			ReleaseDevice();
			logger->Log(Logger::WARNING, "InputDevice::Mouse: Initialisation failed. Unable to set property Axismode.");

			return false;
		}

		// Set the cooperative level of the keyboard to not share with other programs.
		hr = dInputDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(hr))
		{
			ReleaseDevice();
			logger->Log(Logger::WARNING, "InputDevice::Mouse: Initialisation failed. Could not set cooperative level.");
			return false;
		}

		DirectInputDevice::AcquireDevice();
		logger->Log(Logger::INFO, "InputDevice::Mouse: Initialisation successful.");

		return true;
	}

	//Update the directinputstate only if it can be acquired and polled.
	bool DirectMouse::Update()
	{
		bool result = false;
		if (!deviceAcquired)
		{
			result = DirectInputDevice::AcquireDevice();
		}
		else if (!SUCCEEDED(dInputDevice->Poll()))
		{
			logger->Log(Logger::INFO, "InputManager: Mouse polling failed");
			return false;
		}

		if (FAILED(dInputDevice->GetDeviceState(sizeof(DIMOUSESTATE2), (LPVOID)&dIMouseState)))
		{
			result = false;
		}

		if (result == true)
		{
			previousXPos = dIMouseState.lX;
			previousYPos = dIMouseState.lY;
			previousZPos = dIMouseState.lZ;
		}
		return deviceAcquired;
	}

	std::map<Input, long>* DirectMouse::GetInputValues()
	{
		std::map<Input, long>* returnMap = new std::map<Input, long>();

		long deltaXPosition = GetDeltaXPosition();
		long deltaYPosition = GetDeltaYPosition();
		long deltaZPosition = GetDeltaZPosition();

		if (deltaXPosition != 0)
		{
			returnMap->insert(std::make_pair(Input::MOUSE_X, deltaXPosition));
		}
		if (deltaYPosition != 0)
		{
			returnMap->insert(std::make_pair(Input::MOUSE_Y, deltaYPosition));
		}
		if (deltaZPosition != 0)
		{
			returnMap->insert(std::make_pair(Input::MOUSE_Z, deltaZPosition));
		}

		if (dIMouseState.rgbButtons[0] & 0x80)
		{
			returnMap->insert(std::make_pair(Input::MOUSE_BUTTON0, 100));
		}
		if (dIMouseState.rgbButtons[1] & 0x80)
		{
			returnMap->insert(std::make_pair(Input::MOUSE_BUTTON1, 100));
		}
		if (dIMouseState.rgbButtons[2] & 0x80)
		{
			returnMap->insert(std::make_pair(Input::MOUSE_BUTTON2, 100));
		}
		if (dIMouseState.rgbButtons[3] & 0x80)
		{
			returnMap->insert(std::make_pair(Input::MOUSE_BUTTON3, 100));
		}
		if (dIMouseState.rgbButtons[4] & 0x80)
		{
			returnMap->insert(std::make_pair(Input::MOUSE_BUTTON4, 100));
		}
		if (dIMouseState.rgbButtons[5] & 0x80)
		{
			returnMap->insert(std::make_pair(Input::MOUSE_BUTTON5, 100));
		}
		if (dIMouseState.rgbButtons[6] & 0x80)
		{
			returnMap->insert(std::make_pair(Input::MOUSE_BUTTON6, 100));
		}
		if (dIMouseState.rgbButtons[7] & 0x80)
		{
			returnMap->insert(std::make_pair(Input::MOUSE_BUTTON7, 100));
		}
		return returnMap;
	}


	//Returns the position compared to the previous position of the X axis.
	long DirectMouse::GetDeltaXPosition()
	{
		long delta = dIMouseState.lX - previousXPos;
		previousXPos = dIMouseState.lX;
		if (delta > 10000 || delta < -10000)
		{
			delta = 0;
		}
		return delta;
	}

	//Returns the position compared to the previous position of the Y axis.
	long DirectMouse::GetDeltaYPosition()
	{
		long delta = dIMouseState.lY - previousYPos;
		previousYPos = dIMouseState.lY;
		if (delta > 10000 || delta < -10000)
		{
			delta = 0;
		}
		return delta;
	}

	//Returns the position compared to the previous position of the Z axis.
	//The Z axis is the scrollweel. Every movement stands for 120 delta or less
	//or more depending on the mouse.
	long DirectMouse::GetDeltaZPosition()
	{
		long delta = dIMouseState.lZ - previousZPos;
		previousZPos = dIMouseState.lZ;
		if (delta > 10000 || delta < -10000)
		{
			delta = 0;
		}
		return delta;
	}

	void DirectMouse::OnWindowFocusLost(Window* window)
	{
		ReleaseDevice();
		ShowCursor(true);
	}

	void DirectMouse::OnWindowFocusGained(Window* window)
	{
		HRESULT hr = dInputDevice->SetCooperativeLevel(window->GetHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(hr))
		{
			ReleaseDevice();
			logger->Log(Logger::WARNING, "InputDevice::Keyboard: Could not set cooperative level.");
		}
		AcquireDevice();
	}
}