#ifndef _PENGINE_H_
#define _PENGINE_H_

#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "WindowManager.h"

namespace pengine
{
	class PEngine
	{
	public:
		PEngine();
		~PEngine();

		WindowManager* GetWindowManager();
		ResourceManager* GetResourceManager();
		SceneManager* GetSceneManager();
		InputManager* GetInputManager();
		Renderer* GetRenderer();
		void Init();

	private:
		SceneManager* sceneManager;
		WindowManager* windowManager;
		ResourceManager* resourceManager;
		InputManager* inputManager;
		Renderer* renderer;
		Logger* logger;
	};
}

#endif