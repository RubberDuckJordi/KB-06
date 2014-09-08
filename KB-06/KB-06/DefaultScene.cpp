#include "DefaultScene.h"
#include "Logger.h"
#include "LoggerPool.h"

Scene::DefaultScene::DefaultScene(){
	logger = Logger::LoggerPool::GetInstance().GetLogger();
	logger->Log(Logger::Logger::DEBUG, "DefaultScene::Update()");
}

Scene::DefaultScene::~DefaultScene(){
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}

void Scene::DefaultScene::Update(){
	Scene::Update();
}