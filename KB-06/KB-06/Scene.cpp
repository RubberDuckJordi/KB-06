#include "stdafx.h"
#include "Scene.h"

namespace pengine
{
	Scene::Scene()
	{
		logger = LoggerPool::GetInstance().GetLogger();
	}

	Scene::~Scene()
	{
		while (!entities.empty()) delete entities.front(), entities.pop_front();
		LoggerPool::GetInstance().ReturnLogger(logger);
	}

	void Scene::AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	void Scene::InitSkybox(Renderer* renderer, std::string texture)
	{
		Skybox* box = new Skybox(renderer, texture);
		skybox = box;
	}

	void Scene::Update(float deltaTime, std::map<Input, long>* actions)
	{
		for (std::list<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
		{
			(*i)->UpdateLogic(deltaTime, actions);
		}
		currentCamera->UpdateLogic(deltaTime, actions);
	}


	void Scene::Render(Renderer* renderer)
	{
		/*Resource::Vertex* cameraPosition = currentCamera->GetPosition();
		Resource::Vertex* cameraRotation = currentCamera->GetRotation();*/

		//renderer->SetViewMatrix(0, 0, -0.5f, 0, 0, 0.5f);
		renderer->SetActiveCamera(currentCamera->GetCameraData());

		Vertex* cameraPosition = currentCamera->GetPosition();

		skybox->Draw(renderer, cameraPosition);

		for each(Entity* entity in entities)
		{
			entity->Draw(renderer);
		}
	}

	EntityCamera* Scene::GetCurrentCamera()
	{
		return currentCamera;
	}

	void Scene::SetCurrentCamera(EntityCamera* camera)
	{
		currentCamera = camera;
	}

	void Scene::SetSceneCallback(SceneCallback* callback){
		this->callback = callback;
	}
}