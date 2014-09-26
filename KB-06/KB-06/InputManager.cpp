#include "InputManager.h"

pengine::InputManager::InputManager(InputDeviceFactory* p_inputDeviceFactory)
{
	logger = LoggerPool::GetInstance().GetLogger();
	inputDeviceFactory = p_inputDeviceFactory;
	initialised = false;
}

pengine::InputManager::~InputManager()
{
	delete inputDeviceFactory;
}

void pengine::InputManager::Initialise(HWND hwnd)
{
	logger->Log(Logger::DEBUG, "InputManager::Initialise");
	inputDeviceFactory->Initialise(hwnd);
	inputDevices.push_back(inputDeviceFactory->CreateInputDevice(InputDevice::Type::KEYBOARD));
	inputDevices.push_back(inputDeviceFactory->CreateInputDevice(InputDevice::Type::MOUSE));

	initialised = true;
}

/*
Checks every action in the keymapping if it is pressed or changed and
puts in a map. Only occured actions will be in the map. The default
value of a action is 100. This represents 100% with buttons but stands
for pixels when being a mouse movement.
*/
std::map<pengine::Input, long>* pengine::InputManager::GetCurrentActions()
{
	std::map<Input, long>* actionMapping = new std::map < Input, long > ;
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

void pengine::InputManager::OnWindowCreated(pengine::Window* window)
{
	if (!initialised)
	{
		Initialise(window->GetHWND());
	}
}

void pengine::InputManager::OnWindowFocusGained(pengine::Window* window)
{
	logger->Log(Logger::DEBUG, "InputManager::Focus gained");
	std::list<InputDevice*>::iterator deviceIt;
	for (deviceIt = inputDevices.begin(); deviceIt != inputDevices.end(); ++deviceIt)
	{
		(*deviceIt)->OnWindowFocusGained(window);
	}
}

void pengine::InputManager::OnWindowFocusLost(pengine::Window* window)
{
	logger->Log(Logger::DEBUG, "InputManager::Focus lost");
	std::list<InputDevice*>::iterator deviceIt;
	for (deviceIt = inputDevices.begin(); deviceIt != inputDevices.end(); ++deviceIt)
	{
		(*deviceIt)->OnWindowFocusLost(window);
	}
}