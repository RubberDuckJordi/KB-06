// KB-06.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include "loggerPool.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "DirectInputDeviceFactory.h"
#include "ResourceManager.h"
#include "DirectXRenderer.h"

int _tmain(int argc, _TCHAR* argv[])
{ 
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetLogger();
	logger->NewFile();
	logger->SetLogLevel(Logger::Logger::INFO);

	Resource::ResourceManager* resourceManager = new Resource::ResourceManager();
	resourceManager->loadMesh("cube.obj.mesh");
	Renderer::DirectXRenderer* renderer = new Renderer::DirectXRenderer();

	Window::WindowManager* wManager = new Window::WindowManager(NULL);
	// Aanmaken van deze factory moet in een abstract factory gaan gebeuren
	Input::InputDeviceFactory* inputDeviceFactory = new Input::DirectInputDeviceFactory();
	Input::InputManager* iManager = new Input::InputManager(inputDeviceFactory);
	wManager->AddWindowListener(iManager);
	wManager->NewWindow(NULL, 10, 10, 500, 500);
	wManager->GetLastWindow()->SetTitle("Waarom lees jij deze titel? Het kost je meer tijd dan het waard is!");
	wManager->NewWindow(NULL, 100, 100, 500, 500);
	wManager->GetLastWindow()->SetTitle("Waarom lees jij deze titel? Het kost je meer tijd dan het waard is!");	

	while (wManager->HasActiveWindow())
	{
		wManager->UpdateWindows();
		std::map<Input::Input, long> actions = iManager->GetCurrentActions(wManager->GetLastWindow());

		if (actions.size() > 0){
			logger->Log(Logger::Logger::INFO, "Input!");
		}
	}
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
	return 0;
}

