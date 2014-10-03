#ifndef _PENGINE_SCENEMANAGER_H_
#define _PENGINE_SCENEMANAGER_H_

#include "Scene.h"
#include "SceneFactory.h"
#include "Input.h"
#include "Renderer.h"
#include "SceneCallback.h"

#include <list>
#include <map>
#include <functional>

namespace pengine
{
	class SceneManager : public SceneCallback
	{
	public:
		SceneManager();
		~SceneManager();
		void AddSceneFactory(char* key, SceneFactory* sceneFactory);
		Scene* SetScene(char* sceneFactory);
		void RemoveScene(Scene* scene);
		void UpdateScene(Scene* scene);
		void UpdateActiveScene(float deltaTime, std::map<Input, long>* actions);
		void RenderActiveScene(Renderer* renderer);
		void SetCurrentScene(Scene* scene);
		Scene* GetCurrentScene();
		void ChangeScene(char* identifier);
	private:
		Scene* currentScene;
		std::list<Scene*> scenes;
		std::map<char*, SceneFactory*> sceneFactories;
		Logger* logger;
	};
}
#endif
