#include "DefaultEntity.h"
#include "Logger.h"
#include "LoggerPool.h"
#include <iostream>

Scene::DefaultEntity::DefaultEntity()
{
}

Scene::DefaultEntity::~DefaultEntity()
{
}

void Scene::DefaultEntity::UpdateLogic(std::map<Input::Input, long>* actions)
{
	AddRotation(rotationMod, rotationMod, rotationMod);
}

void Scene::DefaultEntity::SetMesh(Resource::Mesh* mesh)
{
	myMesh = mesh;
}

void Scene::DefaultEntity::Draw(Renderer::Renderer* renderer)
{
	if (xModel != NULL)
	{
		Renderer::RenderMatrix* myCache = new Renderer::RenderMatrix();//should be global
		renderer->SetActiveMatrix(myCachedMatrix->theMatrix);//should be called every frame

		Renderer::MaterialWrapper* materialWrapper;
		int materialCount;
		xModel->GetMaterials(materialWrapper, materialCount);

		Renderer::TextureWrapper* textureWrapper;
		int textureCount;
		xModel->GetTextures(textureWrapper, textureCount);

		Renderer::TextureWrapper* textureWrapperIndex = new Renderer::TextureWrapper(&textureWrapper->GetTexture()[0]);

		renderer->SetMaterial(materialWrapper);
		renderer->SetTexture(textureWrapperIndex);
		renderer->DrawSubset(xModel->GetMesh(), 0);
	}
	else
	{
		logger->Log(Logger::WARNING, "No xModel for entity!");
	}
}

void Scene::DefaultEntity::SetXModel(Resource::XModel* p_xmodel)
{
	xModel = p_xmodel;
}