#include "DefaultEntity.h"
#include "Logger.h"
#include "LoggerPool.h"
#include <iostream>

namespace pengine
{
	DefaultEntity::DefaultEntity()
	{
	}

	DefaultEntity::~DefaultEntity()
	{
	}

	void DefaultEntity::UpdateLogic(float deltaTime, std::map<Input, long>* actions)
	{
		AddRotation(rotationMod, rotationMod, rotationMod);
		Entity::UpdateLogic(deltaTime, actions);
	}

	//void DefaultEntity::SetMesh(Mesh* mesh)
	//{
	//	myMesh = mesh;
	//}

	void DefaultEntity::Draw(Renderer* renderer)
	{
		if (xModel != NULL)
		{
			RenderMatrix* myCache = new RenderMatrix();//should be global
			renderer->SetActiveMatrix(myCachedMatrix->theMatrix);//should be called every frame

			MaterialWrapper* materialWrapper;
			int materialCount;
			xModel->GetMaterials(materialWrapper, materialCount);

			TextureWrapper* textureWrapper;
			int textureCount;
			xModel->GetTextures(textureWrapper, textureCount);

			TextureWrapper* textureWrapperIndex = new TextureWrapper(&textureWrapper->GetTexture()[0]);

			renderer->SetMaterialWrapper(materialWrapper);
			renderer->SetTexture(textureWrapperIndex);
			renderer->DrawSubset(xModel->GetMesh(), 0);
		}
		else
		{
			logger->Log(Logger::WARNING, "No xModel for entity!");
		}
	}

	void DefaultEntity::SetXModel(XModel* p_xmodel)
	{
		xModel = p_xmodel;
	}
}