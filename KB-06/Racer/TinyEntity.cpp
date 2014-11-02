#include "TinyEntity.h"

namespace racer
{
	void TinyEntity::UpdateLogic(float deltaTime, std::map<pengine::Input, long>* actions)
	{
		tinyModel->ClearSkinnedVertices();
		tinyModel->SetAnimationStep(2000 * deltaTime);
		tinyModel->UpdateAnimation();

		//this is probably inefficient and painful math...
		maxRadius = tinyModel->GetMaxRadius();
		defaultRadius = maxScale * maxRadius;
		pengine::Entity::UpdateLogic(deltaTime, actions);
	}

	void TinyEntity::CacheToRenderer(pengine::Renderer* renderer)
	{
		//This might already have been done by the pengine through the resourcemanager...
		tinyModel->CacheToRenderer(renderer);
	}

	void TinyEntity::SetObject3D(pengine::Object3D* object)
	{
		tinyModel = object;
		unsigned short int index = 1;
		tinyModel->MapAnimationSet(index);
		tinyModel->SetAnimationStep(1);
		tinyModel->ClearSkinnedVertices();
		tinyModel->UpdateAnimation();
	}

	void TinyEntity::Render(pengine::Renderer* renderer)
	{
		//pengine::Entity::Render(renderer);
		if (tinyModel != NULL)
		{
			renderer->SetActiveMatrix(myCachedMatrix); //should be called every frame
			tinyModel->Render(renderer);
		}
	}

	void TinyEntity::SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ)
	{
		Entity::SetAll(x, y, z, yaw, pitch, roll, scaleX, scaleY, scaleZ);

		//kind of unneeded because the scale is always 1, but you never know :)
		float maxScales = abs(myCachedMatrix->data[0]);
		if (abs(myCachedMatrix->data[5]) > maxScales)
		{
			maxScales = abs(myCachedMatrix->data[5]);
		}
		if (abs(myCachedMatrix->data[10]) > maxScales)
		{
			maxScales = abs(myCachedMatrix->data[10]);
		}
		maxScale = maxScales;
		defaultRadius = maxScale * maxRadius;
	}
}