#include "stdafx.h"
#include "SceneManager.h"


Scene::SceneManager::SceneManager()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}


Scene::SceneManager::~SceneManager()
{
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}

void Scene::SceneManager::AddSceneFactory(char* key, SceneFactory* sceneFactory)
{
	sceneFactories[key] = sceneFactory;
}

Scene::Scene* Scene::SceneManager::AddScene(char* sceneFactory){
	Scene* newScene = sceneFactories.at(sceneFactory)->CreateScene();
	scenes.push_back(newScene);
	return newScene;
}

void Scene::SceneManager::AddScene(Scene* scene)
{
	scenes.push_back(scene);
}


void Scene::SceneManager::RemoveScene(Scene* scene)
{

}

void Scene::SceneManager::UpdateScene(Scene* scene)
{

}

void Scene::SceneManager::UpdateActiveScene(std::map<Input::Input, long>* actions)
{
	currentScene->Update(actions);
}

void Scene::SceneManager::RenderActiveScene(Renderer::Renderer* renderer){
	if (currentScene == NULL){
		if (scenes.size() > 0) {
			logger->Log(Logger::Logger::WARNING, "CurrentScene not set, defaulting to the first added scene");
			currentScene = scenes.front();
		}
		else {
			logger->Log(Logger::Logger::ERR, "CurrentScene not set and no scenes available in the SceneManager");
			return;
		}
	}
	currentScene->Render(renderer);
}

void Scene::SceneManager::SetCurrentScene(Scene* scene)
{
	currentScene = scene;
}