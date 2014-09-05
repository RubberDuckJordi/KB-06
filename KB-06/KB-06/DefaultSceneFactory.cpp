#include "DefaultSceneFactory.h"
#include "DefaultScene.h"

Scene::DefaultSceneFactory::DefaultSceneFactory()
{

}

Scene::DefaultSceneFactory::~DefaultSceneFactory()
{

}

Scene::Scene* Scene::DefaultSceneFactory::CreateScene()
{
	// Add two entities from factory default
	Entity *entity = entityFactories.at("default")->CreateEntity();
	Entity *entityTwo = entityFactories.at("default")->CreateEntity();
	
	DefaultScene* defaultScene = new DefaultScene();
	defaultScene->AddEntity(entity);
	defaultScene->AddEntity(entityTwo);

	return defaultScene;
}