#include "DefaultEntity.h"
#include "Logger.h"
#include "LoggerPool.h"
#include <iostream>

Scene::DefaultEntity::DefaultEntity(){
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}

Scene::DefaultEntity::~DefaultEntity(){
	logger->Log(Logger::Logger::DEBUG, "NOOOOOO");
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}

void Scene::DefaultEntity::Update(){
	logger->Log(Logger::Logger::DEBUG, "DefaultEntity::Update()");
}