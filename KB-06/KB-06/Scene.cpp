#include "stdafx.h"
#include "Scene.h"

pengine::Scene::Scene()
{
	logger = LoggerPool::GetInstance().GetLogger();
}

pengine::Scene::~Scene()
{
	while (!entities.empty()) delete entities.front(), entities.pop_front();
	LoggerPool::GetInstance().ReturnLogger(logger);
}

void pengine::Scene::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}

void pengine::Scene::Update(float deltaTime, std::map<pengine::Input, long>* actions)
{
	for (std::list<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		(*i)->UpdateLogic(deltaTime, actions);
	}
	currentCamera->UpdateLogic(deltaTime, actions);
}


void pengine::Scene::Render(pengine::Renderer* renderer)
{
	/*Resource::Vertex* cameraPosition = currentCamera->GetPosition();
	Resource::Vertex* cameraRotation = currentCamera->GetRotation();*/

	//renderer->SetViewMatrix(0, 0, -0.5f, 0, 0, 0.5f);
	renderer->SetActiveCamera(currentCamera->GetCameraData());

	for each(Entity* entity in entities)
	{
		entity->Draw(renderer);
	}
}

pengine::EntityCamera* pengine::Scene::GetCurrentCamera()
{
	return currentCamera;
}

void pengine::Scene::SetCurrentCamera(EntityCamera* camera)
{
	currentCamera = camera;
}