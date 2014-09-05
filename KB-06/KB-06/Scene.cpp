#include "stdafx.h"
#include "Scene.h"


Scene::Scene::Scene()
{
}


Scene::Scene::~Scene()
{
	while (!entities.empty()) delete entities.front(), entities.pop_front();
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