#include "DefaultScene.h"
#include "Logger.h"
#include "LoggerPool.h"

pengine::DefaultScene::DefaultScene()
{

}

pengine::DefaultScene::~DefaultScene()
{

}

void pengine::DefaultScene::Update(float deltaTime, std::map<Input, long>* actions)
{
	Scene::Update(deltaTime, actions);
}