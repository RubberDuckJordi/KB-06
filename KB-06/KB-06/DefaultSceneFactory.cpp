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

	entity->AddPosition(0.0f, 0.0f, 7.5f);
	entity->AddScale(1.0f, 1.0f, 1.0f);
	entity->AddRotation(0.0f, 0.0f, 0.0f);
	entity->SetMesh(mesh);
	
	DefaultScene* defaultScene = new DefaultScene();
	defaultScene->AddEntity(entity);

	EntityCamera* camera = new EntityCamera();
	camera->AddPosition(0.0f, 0.0f, 0.0f);
	defaultScene->SetCurrentCamera(camera); 

	return defaultScene;
}

void Scene::DefaultSceneFactory::setMesh(Resource::Mesh* p_mesh)
{
	mesh = p_mesh;
}