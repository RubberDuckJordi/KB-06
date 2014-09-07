#include "DefaultEntity.h"
#include "Logger.h"
#include "LoggerPool.h"
#include <iostream>

Scene::DefaultEntity::DefaultEntity(){
	
}

Scene::DefaultEntity::~DefaultEntity(){
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetLogger();
	logger->Log(Logger::Logger::DEBUG, "NOOOOOO");
}

void Scene::DefaultEntity::Update(){
	Logger::Logger* logger = Logger::LoggerPool::GetInstance().GetLogger();
	logger->Log(Logger::Logger::DEBUG, "DefaultEntity::Update()");
}