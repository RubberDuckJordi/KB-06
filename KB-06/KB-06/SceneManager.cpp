#include "stdafx.h"
#include "SceneManager.h"

pengine::SceneManager::SceneManager()
{
	logger = LoggerPool::GetInstance().GetLogger();
}

pengine::SceneManager::~SceneManager()
{
	LoggerPool::GetInstance().ReturnLogger(logger);
}

void pengine::SceneManager::AddSceneFactory(char* key, SceneFactory* sceneFactory)
{
	sceneFactories[key] = sceneFactory;
}

pengine::Scene* pengine::SceneManager::AddScene(char* sceneFactory)
{
	Scene* newScene = sceneFactories.at(sceneFactory)->CreateScene();
	scenes.push_back(newScene);
	return newScene;
}

void pengine::SceneManager::AddScene(Scene* scene)
{
	scenes.push_back(scene);
}


void pengine::SceneManager::RemoveScene(Scene* scene)
{

}

void pengine::SceneManager::UpdateScene(Scene* scene)
{

}

void pengine::SceneManager::UpdateActiveScene(float deltaTime, std::map<pengine::Input, long>* actions)
{
	currentScene->Update(deltaTime, actions);
}

void pengine::SceneManager::RenderActiveScene(pengine::Renderer* renderer)
{
	if (currentScene == NULL)
	{
		if (scenes.size() > 0)
		{
			logger->Log(Logger::WARNING, "CurrentScene not set, defaulting to the first added scene");
			currentScene = scenes.front();
		}
		else
		{
			logger->Log(Logger::ERR, "CurrentScene not set and no scenes available in the SceneManager");
			return;
		}
	}
	currentScene->Render(renderer);
}

void pengine::SceneManager::SetCurrentScene(Scene* scene)
{
	currentScene = scene;
}