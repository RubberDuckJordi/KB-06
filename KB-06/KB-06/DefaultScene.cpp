#include "DefaultScene.h"
#include "Logger.h"
#include "LoggerPool.h"

Scene::DefaultScene::DefaultScene()
{

}

Scene::DefaultScene::~DefaultScene()
{

}

void Scene::DefaultScene::Update(std::map<Input::Input, long>* actions)
{
	Scene::Update(actions);
}