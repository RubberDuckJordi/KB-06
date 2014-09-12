
#ifndef __SCENE_SCENE_MANAGER_H__
#define __SCENE_SCENE_MANAGER_H__

#include "Scene.h"
#include "SceneFactory.h"
#include "Input.h"
#include <list>
#include <map>

namespace Scene {
	class SceneManager {
	public:
		SceneManager();
		~SceneManager();
		void AddSceneFactory(std::string, SceneFactory* sceneFactory);
		Scene* AddScene(std::string sceneType);
		void RemoveScene(Scene* scene);
		void UpdateScene(Scene* scene);
		void UpdateActiveScene(std::map<Input::Input, long> actions);
	private:
		Scene* activeScene;

		std::list<Scene*> scenes;
		std::map<char*, SceneFactory*> sceneFactories;
	};
}

#endif
