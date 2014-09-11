#include "InputManager.h"
#include <iostream>

Input::InputManager::InputManager(InputDeviceFactory* p_inputDeviceFactory)
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
	inputDeviceFactory = p_inputDeviceFactory;
}

Input::InputManager::~InputManager()
{
	RemoveWindows();
	delete inputDeviceFactory;
}

/*
Checks every action in the keymapping if it is pressed or changed and
puts in a map. Only occured actions will be in the map. The default
value of a action is 100. This represents 100% with buttons but stands
for pixels when being a mouse movement.
*/
std::map<Input::Input, long> Input::InputManager::GetCurrentActions(Window::Window* p_window)
{
	std::map<Input, long> actionMapping;

	if (p_window != NULL)
	{
		std::map<Window::Window*, std::list<InputDevice*>>::iterator itWindow = m_windowDevices.find(p_window);

		//Check if there are InputDevices for the Window
		if (itWindow != m_windowDevices.end())
		{
			std::list<InputDevice*>::iterator itInputDevice;

			//Iterate all InputDevices
			for (itInputDevice = itWindow->second.begin(); itInputDevice != itWindow->second.end(); ++itInputDevice)
			{
				//Update the InputDevice
				//And read the InputDevice key states when the InputDevice updated successful
				if ((*itInputDevice)->Update())
				{
					std::map<Input, long>* stateValues = (*itInputDevice)->GetInputValues();
					actionMapping.insert((*stateValues).begin(), (*stateValues).end());
				}
			}
		}
	}

	return actionMapping;
}

//Adds a window to the m_windowDevices map. Also adds a mouse and a keyboard to it
void Input::InputManager::AddWindow(Window::Window* p_window)
{
	std::list<InputDevice*> inputDevices;
	InputDevice* newMouse = inputDeviceFactory->CreateInputDevice(InputDevice::MOUSE, p_window);
	InputDevice* newKeyboard = inputDeviceFactory->CreateInputDevice(InputDevice::KEYBOARD, p_window);

	if (newMouse != NULL)
	{
		inputDevices.push_back(newMouse);
	}
	if (newKeyboard != NULL)
	{
		inputDevices.push_back(newKeyboard);
	}

	m_windowDevices.insert(std::pair<Window::Window*, std::list<InputDevice*>>(p_window, inputDevices));

	logger->Log(Logger::Logger::INFO, "InputManager: Window added, devices initialized.");
}

//Releases the devices of the given window
void Input::InputManager::RemoveWindow(Window::Window& p_window)
{
	std::map<Window::Window*, std::list<InputDevice*>>::iterator it = m_windowDevices.find(&p_window);

	//If the window is found
	if (it != m_windowDevices.end())
	{
		//Destroy all InputDevices for the Window
		for (std::list<InputDevice*>::iterator itInputDevice = it->second.begin(); itInputDevice != it->second.end(); ++itInputDevice)
		{
			(*itInputDevice)->ReleaseDevice();
			delete (*itInputDevice);
		}

		m_windowDevices.erase(&p_window);

		logger->Log(Logger::Logger::INFO, "InputManager: Window destroyed. InputDevices destroyed.");
	}
}

void Input::InputManager::RemoveAllWindows()
{
	std::map<Window::Window*, std::list<InputDevice*>>::iterator it;

	//Iterate all Windows
	for (it = m_windowDevices.begin(); it != m_windowDevices.end(); ++it)
	{
		std::list<InputDevice*>::iterator itInputDevice;

		//Destroy all InputDevices for the Window
		for (itInputDevice = it->second.begin(); itInputDevice != it->second.end(); ++itInputDevice)
		{
			(*itInputDevice)->ReleaseDevice();
			delete (*itInputDevice);
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