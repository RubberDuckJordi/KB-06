#include "stdafx.h"
#include "PEngine.h"
#include "DirectInputDeviceFactory.h"
#include "DirectXRenderer.h"

PEngine::PEngine()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
	logger->NewFile();
}

PEngine::~PEngine()
{
	delete inputManager;
	delete windowManager;
	delete sceneManager;
	delete renderer;
	delete resourceManager;

	logger->Log(Logger::INFO, "Destructed PEngine");
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}

void PEngine::Init()
{
	// Aanmaken van deze factory moet in een abstract factory gaan gebeuren
	windowManager = new Window::WindowManager();
	Input::InputDeviceFactory* inputDeviceFactory = new Input::DirectInputDeviceFactory();
	inputManager = new Input::InputManager(inputDeviceFactory);
	renderer = new Renderer::DirectXRenderer();
	sceneManager = new Scene::SceneManager();
	resourceManager = new Resource::ResourceManager();
}

Window::WindowManager* PEngine::GetWindowManager()
{
	return windowManager;
}

Resource::ResourceManager* PEngine::GetResourceManager()
{
	return resourceManager;
}

Scene::SceneManager* PEngine::GetSceneManager()
{
	return sceneManager;
}

Input::InputManager* PEngine::GetInputManager()
{
	return inputManager;
}

Renderer::Renderer* PEngine::GetRenderer()
{
	return renderer;
}