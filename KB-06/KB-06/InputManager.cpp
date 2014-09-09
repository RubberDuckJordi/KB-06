#include "InputManager.h"
#include <iostream>

#include "DirectInputDeviceFactory.h" // WEGHALEN!!! >:(

Input::InputManager::InputManager(InputDeviceFactory* p_inputDeviceFactory)
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
	inputDeviceFactory = p_inputDeviceFactory;
	Initialize();
}

Input::InputManager::~InputManager()
{
	RemoveWindows();
	delete inputDeviceFactory;
}

//Initializes Key Mapping and the Direct Input object
void Input::InputManager::Initialize()
{
	LoadKeyMapping();
}

/*
Load the actions bound to what key/button from which device. Currently
defined below, in the future this should be read out of a configuration
file with custom actions from the user of the engine.
*/
void Input::InputManager::LoadKeyMapping()
{
	//TODO: read config and get the properbindings
	m_keyMapping[std::make_pair(InputDevice::KEYBOARD, DIK_Q)] = UP;
	m_keyMapping[std::make_pair(InputDevice::KEYBOARD, DIK_E)] = DOWN;
	m_keyMapping[std::make_pair(InputDevice::KEYBOARD, DIK_D)] = RIGHT;
	m_keyMapping[std::make_pair(InputDevice::KEYBOARD, DIK_A)] = LEFT;
	m_keyMapping[std::make_pair(InputDevice::KEYBOARD, DIK_W)] = TOWARD;
	m_keyMapping[std::make_pair(InputDevice::KEYBOARD, DIK_S)] = AWAY;
	m_keyMapping[std::make_pair(InputDevice::KEYBOARD, DIK_SPACE)] = JUMP;
	m_keyMapping[std::make_pair(InputDevice::KEYBOARD, DIK_UP)] = FORWARD;
	m_keyMapping[std::make_pair(InputDevice::KEYBOARD, DIK_DOWN)] = BACKWARD;
	m_keyMapping[std::make_pair(InputDevice::KEYBOARD, DIK_LEFT)] = LEFT;
	m_keyMapping[std::make_pair(InputDevice::KEYBOARD, DIK_RIGHT)] = RIGHT;
	m_keyMapping[std::make_pair(InputDevice::KEYBOARD, DIK_ESCAPE)] = WINDOW_EXIT;
	m_keyMapping[std::make_pair(InputDevice::MOUSE, DIMOFS_X)] = CURSOR_X;
	m_keyMapping[std::make_pair(InputDevice::MOUSE, DIMOFS_Y)] = CURSOR_Y;
	m_keyMapping[std::make_pair(InputDevice::MOUSE, DIMOFS_Z)] = CURSOR_Z;
	m_keyMapping[std::make_pair(InputDevice::MOUSE, DIMOFS_BUTTON0)] = FORWARD;
	m_keyMapping[std::make_pair(InputDevice::MOUSE, DIMOFS_BUTTON1)] = BACKWARD;
}

/*
Checks every action in the keymapping if it is pressed or changed and
puts in a map. Only occured actions will be in the map. The default
value of a action is 100. This represents 100% with buttons but stands
for pixels when being a mouse movement.
*/
std::map<Input::InputManager::Action, long> Input::InputManager::GetCurrentActions(Window::Window* p_window)
{
	std::map<Action, long> actionMapping;

	if (p_window != NULL)
	{
		std::map<Window::Window*, std::map<InputDevice::Type, InputDevice*>>::iterator itWindow = m_windowDevices.find(p_window);

		//Check if there are InputDevices for the Window
		if (itWindow != m_windowDevices.end())
		{
			std::map<InputDevice::Type, InputDevice*>::iterator itInputDeviceType;
			std::map<std::pair<InputDevice::Type, int>, Action>::iterator itKeyMap;
			long stateValue;

			//Iterate all InputDevices
			for (itInputDeviceType = itWindow->second.begin(); itInputDeviceType != itWindow->second.end(); ++itInputDeviceType)
			{
				
				//Update the InputDevice
				//And read the InputDevice key states when the InputDevice updated successful
				if (itInputDeviceType->second->Update())
				{
					//Iterate all KeyMappings
					for (itKeyMap = m_keyMapping.begin(); itKeyMap != m_keyMapping.end(); ++itKeyMap)
					{
						//If the Key is mapped with the InputDevice
						//Add the value of the key state to actionMapping
						if (itKeyMap->first.first == itInputDeviceType->first)
						{
							stateValue = itInputDeviceType->second->GetStateOf(itKeyMap->first.second);

							if (stateValue != 0)
							{
								actionMapping.insert(std::pair<Action, long>(itKeyMap->second, stateValue));
							}
						}
					}
				}
			}
		}
	}

	return actionMapping;
}

//Adds a window to the m_windowDevices map. Also adds a mouse and a keyboard to it
void Input::InputManager::AddWindow(Window::Window* p_window)
{
	std::map<InputDevice::Type, InputDevice*> inputDevices;
	InputDevice* newMouse = inputDeviceFactory->CreateInputDevice(InputDevice::MOUSE, p_window);
	InputDevice* newKeyboard = inputDeviceFactory->CreateInputDevice(InputDevice::KEYBOARD, p_window);

	if (newMouse != NULL)
	{
		inputDevices.insert(std::pair<InputDevice::Type, InputDevice*>(InputDevice::MOUSE, newMouse));
	}
	if (newKeyboard != NULL)
	{
		inputDevices.insert(std::pair<InputDevice::Type, InputDevice*>(InputDevice::KEYBOARD, newKeyboard));
	}

	m_windowDevices.insert(std::pair<Window::Window*, std::map<InputDevice::Type, InputDevice*>>(p_window, inputDevices));

	logger->Log(Logger::Logger::INFO, "InputManager: Window added, devices initialized.");
}

//Releases the devices of the given window
void Input::InputManager::RemoveWindow(Window::Window& p_window)
{
	std::map<Window::Window*, std::map<InputDevice::Type, InputDevice*>>::iterator it = m_windowDevices.find(&p_window);

	//If the window is found
	if (it != m_windowDevices.end())
	{
		std::map<InputDevice::Type, InputDevice*>::iterator itInputDevice;

		//Destroy all InputDevices for the Window
		for (itInputDevice = it->second.begin(); itInputDevice != it->second.end(); ++itInputDevice)
		{
			itInputDevice->second->ReleaseDevice();
			delete itInputDevice->second;
		}

		m_windowDevices.erase(&p_window);

		logger->Log(Logger::Logger::INFO, "InputManager: Window destroyed. InputDevices destroyed.");
	}
}

void Input::InputManager::RemoveWindows()
{
	std::map<Window::Window*, std::map<InputDevice::Type, InputDevice*>>::iterator it;

	//Iterate all Windows
	for (it = m_windowDevices.begin(); it != m_windowDevices.end(); ++it)
	{
		std::map<InputDevice::Type, InputDevice*>::iterator itInputDevice;

		//Destroy all InputDevices for the Window
		for (itInputDevice = it->second.begin(); itInputDevice != it->second.end(); ++itInputDevice)
		{
			itInputDevice->second->ReleaseDevice();
			delete itInputDevice->second;
		}
	}

	logger->Log(Logger::Logger::INFO, "InputManager: All InputDevices deleted.");
}

void Input::InputManager::WindowClosed(Window::Window& p_window)
{
	RemoveWindow(p_window);
}

void Input::InputManager::WindowOpened(Window::Window& p_window)
{
	AddWindow(&p_window);
}