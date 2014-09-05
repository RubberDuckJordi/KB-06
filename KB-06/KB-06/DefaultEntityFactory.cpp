#include "DefaultEntityFactory.h"
#include <iostream>


Scene::DefaultEntityFactory::DefaultEntityFactory(){
	std::cout << "DefaultEntityFactory::DefaultEntityFactory()" << std::endl;
};

Scene::DefaultEntityFactory::~DefaultEntityFactory(){
	std::cout << "DefaultEntityFactory::~DefaultEntityFactory()" << std::endl;
};

Scene::Entity* Scene::DefaultEntityFactory::CreateEntity() {
	DefaultEntity defaultEntity;
	return &defaultEntity;
};

