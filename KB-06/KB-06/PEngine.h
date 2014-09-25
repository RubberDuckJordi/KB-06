#ifndef _PENGINE_H_
#define _PENGINE_H_

#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "WindowManager.h"

class PEngine
{
public:
	PEngine();
	~PEngine();

	Window::WindowManager* GetWindowManager();
	Resource::ResourceManager* GetResourceManager();
	Scene::SceneManager* GetSceneManager();
	Input::InputManager* GetInputManager();
	Renderer::Renderer* GetRenderer();
	void Init();

private:
	Scene::SceneManager* sceneManager;
	Window::WindowManager* windowManager;
	Resource::ResourceManager* resourceManager;
	Input::InputManager* inputManager;
	Renderer::Renderer* renderer;
	Logger::Logger* logger;
};
#endif