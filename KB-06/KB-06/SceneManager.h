
#ifndef __SCENE_SCENE_MANAGER_H__
#define __SCENE_SCENE_MANAGER_H__

#include "Scene.h"
#include "SceneFactory.h"
#include <list>
#include <map>
#include <string>

namespace Scene {
	class SceneManager {
	public:
		SceneManager();
		~SceneManager();
		void AddSceneFactory(std::string, SceneFactory* sceneFactory);
		Scene* AddScene(std::string sceneType);
		void RemoveScene(Scene* scene);
		void UpdateScene(Scene* scene);
		void UpdateActiveScene();
	private:
		Scene* activeScene;

		std::list<Scene*> scenes;
		std::map<std::string, SceneFactory*> sceneFactories;
	};
}

#endif
