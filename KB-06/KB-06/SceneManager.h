#ifndef __SCENE_SCENE_MANAGER_H__
#define __SCENE_SCENE_MANAGER_H__

#include "Scene.h"
#include "SceneFactory.h"
#include "Input.h"
#include "Renderer.h"

#include <list>
#include <map>

namespace pengine
{
	class SceneManager 
	{
	public:
		SceneManager();
		~SceneManager();
		void AddSceneFactory(char* key, SceneFactory* sceneFactory);
		Scene* AddScene(char* sceneFactory);
		void AddScene(Scene* scene);
		void RemoveScene(Scene* scene);
		void UpdateScene(Scene* scene);
		void UpdateActiveScene(float deltaTime, std::map<Input, long>* actions);
		void RenderActiveScene(Renderer* renderer);
		void SetCurrentScene(Scene* scene);

	private:
		Scene* currentScene;
		std::list<Scene*> scenes;
		std::map<char*, SceneFactory*> sceneFactories;
		Logger* logger;
	};
}
#endif
