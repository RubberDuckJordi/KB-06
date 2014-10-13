#include "DefaultSceneFactory.h"
#include "DefaultScene.h"
#include "DefaultEntity.h"

namespace pengine
{
	DefaultSceneFactory::DefaultSceneFactory(ResourceManager* resourceManager)
		:SceneFactory(resourceManager)
	{

	}

	DefaultSceneFactory::~DefaultSceneFactory()
	{

	}

	Scene* DefaultSceneFactory::CreateScene()
	{
		return CreateScene(0, NULL);
	}

	Scene* DefaultSceneFactory::CreateScene(std::vector<std::string>* sceneFile, pengine::ResourceManager* aResourceManager)
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

		DefaultScene* defaultScene = new DefaultScene();
		defaultScene->AddEntity(entity);
		defaultScene->AddEntity(entity2);
		defaultScene->AddEntity(entity3);
		defaultScene->AddEntity(entity4);
		defaultScene->AddEntity(entity5);
		defaultScene->AddEntity(entity6);

		EntityCamera* camera = new EntityCamera();
		camera->AddPosition(0.0f, 0.0f, 100.0f);
		/*camera->myMesh = mesh2;
		camera->myMesh2 = mesh3;*/
		camera->useInput = false;
		defaultScene->SetCurrentCamera(camera);

		EntityCamera* camera2 = new EntityCamera();//this is a testing camera
		camera2->AddPosition(0.0f, 0.0f, 0.0f);
		camera2->useInput = true;

		Skybox* skybox = new pengine::Skybox();
		Material* material = new pengine::Material();
		material->texture = resourceManager->LoadBinaryFile(skyboxTexture);
		skybox->SetMaterial(material);

		defaultScene->SetSkybox(skybox);

		//defaultScene->AddEntity(camera);
		defaultScene->AddEntity(camera2);

		return defaultScene;
	}
}