#ifndef _PENGINE_SCENEMANAGER_H_
#define _PENGINE_SCENEMANAGER_H_

#include "Scene.h"
#include "SceneFactory.h"
#include "Input.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include <list>
#include <map>
#include <functional>

/*
SceneManager is responsible for creating and managing all scenes.
SceneManager expects factories (added by calling AddSceneFactory) before it is
able to create a scene. After creating, SetCurrentScene can be called.

UpdateActiveScene must be called every tick. SceneManager then passes the tick
on to the Scene.
*/

namespace pengine
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();
		std::vector<std::string>* ReadScene(std::string* path, ResourceManager* resourceManager);
		Scene* CreateScene(std::vector<std::string>* sceneFile, char* factoryKey, ResourceManager* resourceManager);
		void AddSceneFactory(char* key, SceneFactory* sceneFactory);
		void UpdateActiveScene(float deltaTime, std::map<Input, long>* actions);
		void RenderActiveScene(Renderer* renderer);
		void SetCurrentScene(Scene* scene);
		Scene* GetCurrentScene();
	private:
		Scene* currentScene;
		std::list<Scene*> scenes;
		std::map<char*, SceneFactory*> sceneFactories;
		Logger* logger;
	};
}
#endif
