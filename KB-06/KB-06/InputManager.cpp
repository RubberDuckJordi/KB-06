#include "InputManager.h"
#include <iostream>

Input::InputManager::InputManager(InputDeviceFactory* p_inputDeviceFactory)
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
	inputDeviceFactory = p_inputDeviceFactory;

	inputDevices.push_back(inputDeviceFactory->CreateInputDevice(InputDevice::Type::KEYBOARD));
	inputDevices.push_back(inputDeviceFactory->CreateInputDevice(InputDevice::Type::MOUSE));
}

Input::InputManager::~InputManager()
{
	delete inputDeviceFactory;
}

/*
Checks every action in the keymapping if it is pressed or changed and
puts in a map. Only occured actions will be in the map. The default
value of a action is 100. This represents 100% with buttons but stands
for pixels when being a mouse movement.
*/
std::map<Input::Input, long>* Input::InputManager::GetCurrentActions()
{
	std::map<Input, long>* actionMapping = new std::map<Input, long>;
	std::list<InputDevice*>::iterator itInputDevice;

	//Iterate all InputDevices
	for (itInputDevice = inputDevices.begin(); itInputDevice != inputDevices.end(); ++itInputDevice)
	{
		//Update the InputDevice
		//And read the InputDevice key states when the InputDevice updated successful
		if ((*itInputDevice)->Update())
		{
			std::map<Input, long>* stateValues = (*itInputDevice)->GetInputValues();
			(*actionMapping).insert((*stateValues).begin(), (*stateValues).end());
		}
	}

	return actionMapping;
}

void Input::InputManager::OnWindowFocusGained(Window::Window* p_window)
{
	std::list<InputDevice*>::iterator inputDeviceIterator;
	for (inputDeviceIterator = inputDevices.begin(); inputDeviceIterator != inputDevices.end(); inputDeviceIterator++)
	{
		(*inputDeviceIterator)->SetActiveWindow(p_window);
	}
}

void Input::InputManager::OnWindowFocusLost(Window::Window* p_window)
{
	std::list<InputDevice*>::iterator inputDeviceIterator;
	for (inputDeviceIterator = inputDevices.begin(); inputDeviceIterator != inputDevices.end(); inputDeviceIterator++)
	{
		(*inputDeviceIterator)->SetWindowInactive(p_window);
	}
}