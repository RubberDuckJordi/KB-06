#include "DefaultEntityFactory.h"
#include <iostream>

namespace Scene{
	DefaultEntityFactory::DefaultEntityFactory(){
		std::cout << "DefaultEntityFactory::DefaultEntityFactory()" << std::endl;
	};

	DefaultEntityFactory::~DefaultEntityFactory(){
		std::cout << "DefaultEntityFactory::~DefaultEntityFactory()" << std::endl;
	};

	Entity* Scene::DefaultEntityFactory::CreateEntity() {
		DefaultEntity defaultEntity;
		return &defaultEntity;
	};
}
