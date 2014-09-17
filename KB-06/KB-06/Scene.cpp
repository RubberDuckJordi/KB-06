#include "stdafx.h"
#include "Scene.h"

Scene::Scene::Scene()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}


Scene::Scene::~Scene()
{
	while (!entities.empty()) delete entities.front(), entities.pop_front();
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}

void Scene::Scene::AddEntity(Entity* entity){
	entities.push_back(entity);
}

void Scene::Scene::Update(std::map<Input::Input, long>* actions) {
	for (std::list<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		(*i)->Update(actions);
	}
	currentCamera->Update(actions);
}


void Scene::Scene::Render(Renderer::Renderer* renderer){

	Resource::Vertex* cameraPosition = currentCamera->GetPosition();
	Resource::Vertex* cameraRotation = currentCamera->GetRotation();

	renderer->SetViewMatrix(0, 0, -0.5f, 0, 0, 0.5f);

	for each(Entity* entity in entities)
	{
		entity->Draw(renderer, currentCamera->GetPosition(), currentCamera->GetRotation());
	}
}

Scene::EntityCamera* Scene::Scene::GetCurrentCamera()
{
	return currentCamera;
}

void Scene::Scene::SetCurrentCamera(EntityCamera* camera)
{
	currentCamera = camera;
}