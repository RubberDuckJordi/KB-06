#include "SceneFactory.h"

Scene::SceneFactory::SceneFactory()
{

}

Scene::SceneFactory::~SceneFactory()
{
	std::map<std::string, EntityFactory*>::iterator itr = entityFactories.begin();
	if (itr != entityFactories.end())
	{
		delete itr->second;
		entityFactories.erase(itr);
	}
}

void Scene::SceneFactory::AddEntityFactory(std::string name, EntityFactory *entityFactory)
{
	entityFactories[name] = entityFactory;
}