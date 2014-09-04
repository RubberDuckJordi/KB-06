#include "DefaultEntity.h"
#include <iostream>

Scene::DefaultEntity::DefaultEntity(){
	std::cout << "DefaultEntity::DefaultEntity()" << std::endl;
}

Scene::DefaultEntity::~DefaultEntity(){
	std::cout << "DefaultEntity::~DefaultEntity()" << std::endl;
}

void Scene::DefaultEntity::Update(){
	std::cout << "Updating DefaultEntity" << std::endl;
}