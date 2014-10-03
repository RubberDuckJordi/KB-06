#include "DirectKeyboard.h"

namespace pengine
{
	DirectKeyboard::DirectKeyboard()
	{
		deviceName = "Keyboard";
	}

	DirectKeyboard::~DirectKeyboard()
	{
		DirectInputDevice::~DirectInputDevice();
	}

	//Create the new DirectInputDevice, add a handler to its window and
	//set the required settings to be able to poll it.
	bool DirectKeyboard::Initialize(LPDIRECTINPUT8 m_dInput, HWND hwnd)
	{
		HRESULT hr = m_dInput->CreateDevice(GUID_SysKeyboard, &dInputDevice, NULL);
		if FAILED(hr)
		{
			ReleaseDevice();
			logger->Log(Logger::WARNING, "InputDevice::Keyboard: Initialisation failed. Unable to create Input Device.");
			return false;
		}

		hr = dInputDevice->SetDataFormat(&c_dfDIKeyboard);
		if FAILED(hr)
		{
			ReleaseDevice();
			logger->Log(Logger::WARNING, "InputDevice::Keyboard: Initialisation failed. Unable to set dataformat.");
			return false;
		}

		// Set the cooperative level of the keyboard to not share with other programs.
		hr = dInputDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(hr))
		{
			ReleaseDevice();
			logger->Log(Logger::WARNING, "InputDevice::Keyboard: Initialisation failed. Could not set cooperative level.");
			return false;
		}

		AcquireDevice();
		logger->Log(Logger::INFO, "InputDevice::Keyboard: Initialisation successful.");

		return true;
	}

	bool DirectKeyboard::Update()
	{
		if (!deviceAcquired){
			return false;
		}

		if (!SUCCEEDED(dInputDevice->Poll()))
		{
			logger->Log(Logger::INFO, "InputManager: Keyboard polling failed");
			return false;
		}

		if (FAILED(dInputDevice->GetDeviceState(sizeof(m_KeyBuffer), (LPVOID)&m_KeyBuffer)))
		{
			return false;
		}
		return true;
	}

	//Returns 100 if given key is being pressed at the moment
	long DirectKeyboard::GetStateOf(int p_key)
	{
		if (!SUCCEEDED(dInputDevice->Poll()))
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

	std::map<Input, long>* DirectKeyboard::GetInputValues()
	{
		std::map<Input, long>* returnMap = new std::map<Input, long>();

		typedef std::map<Input, int>::iterator it_type;
		for (it_type iterator = (*actionMapping).begin(); iterator != (*actionMapping).end(); iterator++)
		{
			int directInputKey = iterator->second;
			// Only process range of keyboard values
			if (directInputKey >= 0x01 && directInputKey <= 0xED){
				long state = GetStateOf(directInputKey);
				if (state != 0){
					returnMap->insert(std::make_pair(iterator->first, state));
				}
			}
		}
		return returnMap;
	}

	void DirectKeyboard::OnWindowFocusLost(Window* window)
	{
		ReleaseDevice();
	}

	void DirectKeyboard::OnWindowFocusGained(Window* window)
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