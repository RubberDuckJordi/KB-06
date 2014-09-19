#include "DirectKeyboard.h"

Input::DirectKeyboard::DirectKeyboard()
{
	deviceName = "Keyboard";
}

Input::DirectKeyboard::~DirectKeyboard()
{
	DirectInputDevice::~DirectInputDevice();
}

//Create the new DirectInputDevice, add a handler to its window and
//set the required settings to be able to poll it.
bool Input::DirectKeyboard::Initialize(LPDIRECTINPUT8 m_dInput)
{
	HRESULT hr = m_dInput->CreateDevice(GUID_SysKeyboard, &dInputDevice, NULL);
	if FAILED(hr)
	{
		ReleaseDevice();
		logger->Log(Logger::Logger::WARNING, "InputDevice::Keyboard: Initialisation failed. Unable to create Input Device.");
		return false;
	}

	hr = dInputDevice->SetDataFormat(&c_dfDIKeyboard);
	if FAILED(hr)
	{
		ReleaseDevice();
		logger->Log(Logger::Logger::WARNING, "InputDevice::Keyboard: Initialisation failed. Unable to set dataformat.");
		return false;
	}

	AcquireDevice();
	logger->Log(Logger::Logger::INFO, "InputDevice::Keyboard: Initialisation successful.");

	return true;
}

bool Input::DirectKeyboard::Update()
{
	if (activeWindow != NULL)
	{
		if (!SUCCEEDED(dInputDevice->Poll()))
		{
			if (deviceAcquired)
			{
				logger->Log(Logger::Logger::INFO, "InputManager: Keyboard focus lost.");
				deviceAcquired = false;
			}
			AcquireDevice();
		}

		if (FAILED(dInputDevice->GetDeviceState(sizeof(m_KeyBuffer), (LPVOID)&m_KeyBuffer)))
		{
			return false;
		}
	}
	

	return true;
}

//Returns 100 if given key is being pressed at the moment
long Input::DirectKeyboard::GetStateOf(int p_key)
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

std::map<Input::Input, long>* Input::DirectKeyboard::GetInputValues()
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

bool Input::DirectKeyboard::SetActiveWindow(Window::Window* window)
{
	activeWindow = window;
	return true;
}

void Input::DirectKeyboard::SetWindowInactive(Window::Window* window)
{
	activeWindow = NULL;
}