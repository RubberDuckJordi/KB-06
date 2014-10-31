#include "TinyEntity.h"

namespace racer
{
	void TinyEntity::UpdateLogic(float deltaTime, std::map<pengine::Input, long>* actions)
	{
		tinyModel->ClearSkinnedVertices();
		tinyModel->SetAnimationStep(2000 * deltaTime);
		tinyModel->UpdateAnimation();
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
}