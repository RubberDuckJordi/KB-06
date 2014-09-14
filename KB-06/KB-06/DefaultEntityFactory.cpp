#include "DefaultEntityFactory.h"
#include <iostream>


Scene::DefaultEntityFactory::DefaultEntityFactory(){

};

Scene::DefaultEntityFactory::~DefaultEntityFactory(){

};

Scene::Entity* Scene::DefaultEntityFactory::CreateEntity() {
	DefaultEntity *defaultEntity = new DefaultEntity();
	return defaultEntity;
};
