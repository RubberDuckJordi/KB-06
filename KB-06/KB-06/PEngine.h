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

		void NewWindow(int x, int y, int width, int height);
		void AddSceneFactory(char* key, SceneFactory* sceneFactory);

		void AddScene();
		void InitRenderer();
		Scene* AddScene(char* sceneFactory);
		void SetCurrentScene(Scene* scene);
		void GameLoop();

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