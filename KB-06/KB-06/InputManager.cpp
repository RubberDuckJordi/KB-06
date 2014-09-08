#include "InputManager.h"
#include <iostream>

Input::InputManager::InputManager()
{
	m_dInput = NULL;
	logger = Logger::LoggerPool::GetInstance().GetLogger();
	Initialize();
}

Input::InputManager::~InputManager()
{
	RemoveWindows();

	if (m_dInput != NULL)
	{
		m_dInput->Release();
		m_dInput = NULL;
	}
}

//Initializes Key Mapping and the Direct Input object
void Input::InputManager::Initialize()
{
	LoadKeyMapping();

	if (SUCCEEDED(DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_dInput,
		NULL)))
	{
		logger->Log(Logger::Logger::INFO, "InputManager: Initialisation successful.");
	}
	else
	{
		logger->Log(Logger::Logger::WARNING, "InputManager: Initialisation failed.");
	}
}

/*
Load the actions bound to what key/button from which device. Currently
defined below, in the future this should be read out of a configuration
file with custom actions from the user of the engine.
*/
void Input::InputManager::LoadKeyMapping()
{
	//TODO: read config and get the properbindings
	m_keyMapping[std::make_pair(KEYBOARD, DIK_Q)] = UP;
	m_keyMapping[std::make_pair(KEYBOARD, DIK_E)] = DOWN;
	m_keyMapping[std::make_pair(KEYBOARD, DIK_D)] = RIGHT;
	m_keyMapping[std::make_pair(KEYBOARD, DIK_A)] = LEFT;
	m_keyMapping[std::make_pair(KEYBOARD, DIK_W)] = TOWARD;
	m_keyMapping[std::make_pair(KEYBOARD, DIK_S)] = AWAY;
	m_keyMapping[std::make_pair(KEYBOARD, DIK_SPACE)] = JUMP;
	m_keyMapping[std::make_pair(KEYBOARD, DIK_UP)] = FORWARD;
	m_keyMapping[std::make_pair(KEYBOARD, DIK_DOWN)] = BACKWARD;
	m_keyMapping[std::make_pair(KEYBOARD, DIK_LEFT)] = LEFT;
	m_keyMapping[std::make_pair(KEYBOARD, DIK_RIGHT)] = RIGHT;
	m_keyMapping[std::make_pair(KEYBOARD, DIK_ESCAPE)] = WINDOW_EXIT;
	m_keyMapping[std::make_pair(MOUSE, DIMOFS_X)] = CURSOR_X;
	m_keyMapping[std::make_pair(MOUSE, DIMOFS_Y)] = CURSOR_Y;
	m_keyMapping[std::make_pair(MOUSE, DIMOFS_Z)] = CURSOR_Z;
	m_keyMapping[std::make_pair(MOUSE, DIMOFS_BUTTON0)] = FORWARD;
	m_keyMapping[std::make_pair(MOUSE, DIMOFS_BUTTON1)] = BACKWARD;
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
		std::map<Window::Window*, std::map<InputDeviceType, InputDevice*>>::iterator itWindow = m_windowDevices.find(p_window);

		//Check if there are InputDevices for the Window
		if (itWindow != m_windowDevices.end())
		{
			std::map<InputDeviceType, InputDevice*>::iterator itInputDeviceType;
			std::map<std::pair<InputDeviceType, int>, Action>::iterator itKeyMap;
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
	std::map<InputDeviceType, InputDevice*> inputDevices;
	Mouse* newMouse = new Mouse();
	Keyboard* newKeyboard = new Keyboard();

	if (newKeyboard->Initialize(p_window->GetHWND(), m_dInput))
	{
		inputDevices.insert(std::pair<InputDeviceType, InputDevice*>(KEYBOARD, newKeyboard));
	}
	else
	{
		delete newKeyboard;
	}

	if (newMouse->Initialize(p_window->GetHWND(), m_dInput))
	{
		inputDevices.insert(std::pair<InputDeviceType, InputDevice*>(MOUSE, newMouse));
	}
	else
	{
		delete newMouse;
	}

	m_windowDevices.insert(std::pair<Window::Window*, std::map<InputDeviceType, InputDevice*>>(p_window, inputDevices));

	logger->Log(Logger::Logger::INFO, "InputManager: Window added, devices initialized.");
}

//Releases the devices of the given window
void Input::InputManager::RemoveWindow(Window::Window& p_window)
{
	std::map<Window::Window*, std::map<InputDeviceType, InputDevice*>>::iterator it = m_windowDevices.find(&p_window);

	//If the window is found
	if (it != m_windowDevices.end())
	{
		std::map<InputDeviceType, InputDevice*>::iterator itInputDevice;

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
	std::map<Window::Window*, std::map<InputDeviceType, InputDevice*>>::iterator it;

	//Iterate all Windows
	for (it = m_windowDevices.begin(); it != m_windowDevices.end(); ++it)
	{
		std::map<InputDeviceType, InputDevice*>::iterator itInputDevice;

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