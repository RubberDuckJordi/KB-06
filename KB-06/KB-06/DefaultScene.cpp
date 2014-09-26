#include "DefaultScene.h"
#include "Logger.h"
#include "LoggerPool.h"

pengine::DefaultScene::DefaultScene()
{

}

pengine::DefaultScene::~DefaultScene()
{

}

void pengine::DefaultScene::Update(std::map<Input, long>* actions)
{
	Scene::Update(actions);
}