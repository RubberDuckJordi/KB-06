#include "DefaultSceneFactory.h"
#include "DefaultScene.h"
#include "DefaultEntity.h"

pengine::DefaultSceneFactory::DefaultSceneFactory()
{

}

pengine::DefaultSceneFactory::~DefaultSceneFactory()
{

}

pengine::Scene* pengine::DefaultSceneFactory::CreateScene()
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

	entity->SetXModel(xModel);
	entity2->SetXModel(xModel);
	entity3->SetXModel(xModel);
	entity4->SetXModel(xModel);
	entity5->SetXModel(xModel);
	entity6->SetXModel(xModel);

	/*entity->rotationMod = 1;
	entity2->rotationMod = -1;
	entity3->rotationMod = 2;
	entity4->rotationMod = -2;
	entity5->rotationMod = 3;
	entity6->rotationMod = -3;*/

	DefaultScene* defaultScene = new DefaultScene();
	defaultScene->AddEntity(entity);
	defaultScene->AddEntity(entity2);
	defaultScene->AddEntity(entity3);
	defaultScene->AddEntity(entity4);
	defaultScene->AddEntity(entity5);
	defaultScene->AddEntity(entity6);

	EntityCamera* camera = new EntityCamera();
	camera->AddPosition(0.0f, 200.0f, 0.1f);
	camera->myMesh = mesh2;
	camera->myMesh2 = mesh3;
	camera->useInput = false;
	defaultScene->SetCurrentCamera(camera);

	EntityCamera* camera2 = new EntityCamera();//this is a testing camera
	camera2->AddPosition(0.0f, 0.0f, 0.0f);
	camera2->myMesh = mesh2;
	camera2->myMesh2 = mesh3;
	camera2->SetXModel(xModel2);
	camera2->useInput = true;

	//defaultScene->AddEntity(camera);
	defaultScene->AddEntity(camera2);

	return defaultScene;
}

void pengine::DefaultSceneFactory::setMesh(pengine::Mesh* p_mesh)
{
	mesh = p_mesh;
}

void pengine::DefaultSceneFactory::setMesh2(pengine::Mesh* p_mesh)
{
	mesh2 = p_mesh;
}

void pengine::DefaultSceneFactory::setMesh3(pengine::Mesh* p_mesh)
{
	mesh3 = p_mesh;
}

void pengine::DefaultSceneFactory::SetXModel(pengine::XModel* p_xModel)
{
	xModel = p_xModel;
}

void pengine::DefaultSceneFactory::SetXModel2(pengine::XModel* p_xModel)
{
	xModel2 = p_xModel;
}