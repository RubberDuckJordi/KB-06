#include "DefaultSceneFactory.h"
#include "DefaultScene.h"
#include "DefaultEntityFactory.h"

Scene::DefaultSceneFactory::DefaultSceneFactory()
{

}

Scene::DefaultSceneFactory::~DefaultSceneFactory()
{

}

Scene::Scene* Scene::DefaultSceneFactory::CreateScene()
{
	// Add two entities from factory default
	entityFactories["default"] = new DefaultEntityFactory();
	Entity *entity = entityFactories.at("default")->CreateEntity();
	
	DefaultScene* defaultScene = new DefaultScene();
	defaultScene->AddEntity(entity);
	entity->SetMesh(mesh);

	EntityCamera* camera = new EntityCamera();
	camera->AddPosition(-100, 0, 0);
	defaultScene->SetCurrentCamera(camera);

	return defaultScene;
}

void Scene::DefaultSceneFactory::setMesh(Resource::Mesh* p_mesh)
{
	mesh = p_mesh;
}