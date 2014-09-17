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

	//logger->Log(1, "New render!");

	for each(Entity* entity in entities)
	{
		D3DXMATRIXA16 entityMatrix;
		Resource::Vertex* pos = entity->GetPosition();
		D3DXMatrixTranslation(&entityMatrix, pos->x, pos->y, pos->z);

		MatrixWrapper* theRealFinalMatix = new MatrixWrapper(entityMatrix);



		renderer->SetWorldMatrix(theRealFinalMatix);

		/*D3DXMATRIXA16 matWorldFinal;
		D3DXMatrixMultiply(&matWorldFinal, &currentEntity->finalMatrix, &activeCamera->finalMatrix);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorldFinal);*/

		entity->Draw(renderer, currentCamera->GetPosition(), currentCamera->GetRotation());
	}
	//logger->Log(1, "End render!");
}

Scene::EntityCamera* Scene::Scene::GetCurrentCamera()
{
	return currentCamera;
}

void Scene::Scene::SetCurrentCamera(EntityCamera* camera)
{
	currentCamera = camera;
}