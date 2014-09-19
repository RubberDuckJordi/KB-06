#include "DefaultEntity.h"
#include "Logger.h"
#include "LoggerPool.h"
#include <iostream>

Scene::DefaultEntity::DefaultEntity(){

}

Scene::DefaultEntity::~DefaultEntity(){

}

void Scene::DefaultEntity::UpdateLogic(std::map<Input::Input, long>* actions){
	AddRotation(rotationMod, rotationMod, rotationMod);
}

void Scene::DefaultEntity::SetMesh(Resource::Mesh* mesh)
{
	myMesh = mesh;
}

void Scene::DefaultEntity::Draw(Renderer::Renderer* renderer)
{
	if (myMesh != NULL)
	{
		RenderMatrix* myCache = new RenderMatrix();//should be global
		//renderer->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCache);//should only be called when needed (when any value has updated)
		//renderer->SetWorldMatrix(&position, &rotation, &scale, p_position, p_rotation);
		renderer->SetActiveMatrix(myCachedMatrix->theMatrix);//should be called every frame
		renderer->Draw(myMesh);
	}
	else
	{
		logger->Log(Logger::Logger::WARNING, "No mesh for entity!");
	}
}