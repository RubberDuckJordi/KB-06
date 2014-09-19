#include "DefaultSceneFactory.h"
#include "DefaultScene.h"
#include "DefaultEntity.h"

Scene::DefaultSceneFactory::DefaultSceneFactory()
{

}

Scene::DefaultSceneFactory::~DefaultSceneFactory()
{

}

Scene::Scene* Scene::DefaultSceneFactory::CreateScene()
{
	DefaultEntity* entity = new DefaultEntity();
	DefaultEntity* entity2 = new DefaultEntity();
	DefaultEntity* entity3 = new DefaultEntity();
	DefaultEntity* entity4 = new DefaultEntity();
	DefaultEntity* entity5 = new DefaultEntity();
	DefaultEntity* entity6 = new DefaultEntity();

	entity->AddAll(-7.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	entity2->AddAll(7.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	entity3->AddAll(0.0f, -7.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	entity4->AddAll(0.0f, 7.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	entity5->AddAll(0.0f, 0.0f, -7.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	entity6->AddAll(0.0f, 0.0f, 7.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	entity->SetMesh(mesh);
	entity2->SetMesh(mesh);
	entity3->SetMesh(mesh);
	entity4->SetMesh(mesh);
	entity5->SetMesh(mesh);
	entity6->SetMesh(mesh);

	entity->rotationMod = 1;
	entity2->rotationMod = -1;
	entity3->rotationMod = 2;
	entity4->rotationMod = -2;
	entity5->rotationMod = 3;
	entity6->rotationMod = -3;

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