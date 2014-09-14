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

void Scene::Scene::Update() {
	for (std::list<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		(*i)->Update();
	}
}


void Scene::Scene::Render(Renderer::Renderer* renderer){
	for each(Entity* enitity in entities)
	{
		enitity->Draw(renderer, currentCamera.GetMatrix());
	}
}