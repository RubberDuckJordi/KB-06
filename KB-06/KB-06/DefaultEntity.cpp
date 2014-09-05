#include "DefaultEntity.h"
#include "Logger.h"
#include <iostream>

Scene::DefaultEntity::DefaultEntity(){
	
}

Scene::DefaultEntity::~DefaultEntity(){
	Logger::Logger::GetLogger("main")->Log(Logger::Logger::DEBUG, "NOOOOOO");
}

void Scene::DefaultEntity::Update(){
	Logger::Logger::GetLogger("main")->Log(Logger::Logger::DEBUG, "DefaultEntity::Update()");
}