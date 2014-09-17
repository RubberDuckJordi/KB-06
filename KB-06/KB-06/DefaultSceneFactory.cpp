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

	Entity *entity2 = entityFactories.at("default")->CreateEntity();

	entity2->AddPosition(0.0f, 0.0f, -7.5f);
	entity2->AddScale(1.0f, 1.0f, 1.0f);
	entity2->AddRotation(0.0f, 0.0f, 0.0f);
	entity2->SetMesh(mesh);

	Entity *entity3 = entityFactories.at("default")->CreateEntity();

	entity3->AddPosition(7.5f, 0.0f, 0.0f);
	entity3->AddScale(1.0f, 1.0f, 1.0f);
	entity3->AddRotation(0.0f, 0.0f, 0.0f);
	entity3->SetMesh(mesh);

	Entity *entity4 = entityFactories.at("default")->CreateEntity();

	entity4->AddPosition(-7.5f, 0.0f, 0.0f);
	entity4->AddScale(1.0f, 1.0f, 1.0f);
	entity4->AddRotation(0.0f, 0.0f, 0.0f);
	entity4->SetMesh(mesh);

	Entity *entity5 = entityFactories.at("default")->CreateEntity();

	entity5->AddPosition(0.0f, 7.5f, 0.0f);
	entity5->AddScale(1.0f, 1.0f, 1.0f);
	entity5->AddRotation(0.0f, 0.0f, 0.0f);
	entity5->SetMesh(mesh);

	Entity *entity6 = entityFactories.at("default")->CreateEntity();

	entity6->AddPosition(0.0f, -7.5f, 0.0f);
	entity6->AddScale(1.0f, 1.0f, 1.0f);
	entity6->AddRotation(0.0f, 0.0f, 0.0f);
	entity6->SetMesh(mesh);
	
	DefaultScene* defaultScene = new DefaultScene();
	defaultScene->AddEntity(entity);
	defaultScene->AddEntity(entity2);
	defaultScene->AddEntity(entity3);
	defaultScene->AddEntity(entity4);
	defaultScene->AddEntity(entity5);
	defaultScene->AddEntity(entity6);


	EntityCamera* camera = new EntityCamera();
	camera->AddPosition(0.0f, 0.0f, 0.0f);
	defaultScene->SetCurrentCamera(camera); 

	return defaultScene;
}

void Scene::DefaultSceneFactory::setMesh(Resource::Mesh* p_mesh)
{
	mesh = p_mesh;
}