#include "stdafx.h"
#include "SceneManager.h"


Scene::SceneManager::SceneManager()
{
}


Scene::SceneManager::~SceneManager()
{
}

void Scene::SceneManager::AddSceneFactory(std::string, SceneFactory* sceneFactory)
{

}

Scene::Scene* Scene::SceneManager::AddScene(std::string sceneType)
{

}

void Scene::SceneManager::RemoveScene(Scene* scene)
{

}

void Scene::SceneManager::UpdateScene(Scene* scene)
{

}

void Scene::SceneManager::UpdateActiveScene(std::map<Input::Input, long> actions)
{

}