#include "stdafx.h"
#include "SceneManager.h"
#include "SceneCallback.h"

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

pengine::Scene* pengine::SceneManager::SetScene(char* sceneFactory)
{
	if (sceneFactories.find(sceneFactory) != sceneFactories.end())
	{
		Scene* currentScene = sceneFactories.at(sceneFactory)->CreateScene();
		currentScene->SetSceneCallback(this);
		return currentScene;
	}
	else 
	{
		logger->Log(Logger::ERR, "SceneFactory \"" + std::string(sceneFactory) + "\" not found");
		return NULL;
	}
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

pengine::Scene* pengine::SceneManager::GetCurrentScene()
{
	return currentScene;
}

void pengine::SceneManager::ChangeScene(char* identifier){
	SetScene(identifier);
}