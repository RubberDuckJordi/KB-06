#include "DefaultScene.h"
#include "Logger.h"
#include "LoggerPool.h"

Scene::DefaultScene::DefaultScene(){

}

Scene::DefaultScene::~DefaultScene(){

}

void Scene::DefaultScene::Update(){
	Scene::Update();
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetLogger();
	logger->Log(Logger::Logger::DEBUG, "DefaultScene::Update()");
}