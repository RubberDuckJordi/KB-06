#include "stdafx.h"
#include "PEngine.h"
#include "DirectInputDeviceFactory.h"
#include "DirectXRenderer.h"

pengine::PEngine::PEngine()
{
	logger = LoggerPool::GetInstance().GetLogger();
	logger->NewFile();
}

pengine::PEngine::~PEngine()
{
	delete inputManager;
	delete windowManager;
	delete sceneManager;
	delete renderer;
	delete resourceManager;

	logger->Log(Logger::INFO, "Destructed PEngine");
	LoggerPool::GetInstance().ReturnLogger(logger);
}

void pengine::PEngine::Init()
{
	// Aanmaken van deze factory moet in een abstract factory gaan gebeuren
	windowManager = new WindowManager();
	InputDeviceFactory* inputDeviceFactory = new DirectInputDeviceFactory();
	inputManager = new InputManager(inputDeviceFactory);
	renderer = new DirectXRenderer();
	sceneManager = new SceneManager();
	resourceManager = new ResourceManager();
}

pengine::WindowManager* pengine::PEngine::GetWindowManager()
{
	return windowManager;
}

pengine::ResourceManager* pengine::PEngine::GetResourceManager()
{
	return resourceManager;
}

pengine::SceneManager* pengine::PEngine::GetSceneManager()
{
	return sceneManager;
}

pengine::InputManager* pengine::PEngine::GetInputManager()
{
	return inputManager;
}

pengine::Renderer* pengine::PEngine::GetRenderer()
{
	return renderer;
}