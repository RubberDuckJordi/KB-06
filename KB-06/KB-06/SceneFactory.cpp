#include "SceneFactory.h"

Scene::SceneFactory::SceneFactory()
{

}

Scene::SceneFactory::~SceneFactory()
{
	std::map<char*, EntityFactory*>::iterator itr = entityFactories.begin();
	if (itr != entityFactories.end())
	{
		delete itr->second;
		entityFactories.erase(itr);
	}
}

void Scene::SceneFactory::AddEntityFactory(char* name, EntityFactory *entityFactory)
{
	entityFactories[name] = entityFactory;
}