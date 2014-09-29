#include "RaceCart.h"

racer::RaceCart::RaceCart()
{

}

racer::RaceCart::~RaceCart()
{

}

void racer::RaceCart::UpdateLogic(float deltaTime, std::map<pengine::Input, long>* actions)
{
	force = 0.0f;

	typedef std::map<pengine::Input, long>::iterator it_type;
	for (it_type iterator = (*actions).begin(); iterator != (*actions).end(); iterator++)
	{
		float speed = static_cast<float>(iterator->second);

		switch (iterator->first)
		{
		case pengine::Input::KEY_S:
			force = 0.01f;
			break;
		case pengine::Input::KEY_W:
			force = -0.01f;
			break;
		case pengine::Input::KEY_D:
			this->AddPosition(-0.5f, 0.0f, 0.0f);
			break;
		case pengine::Input::KEY_A:
			this->AddPosition(0.5f, 0.0f, 0.0f);
			break;
		default:
			break;
		}
	}

	pengine::Entity::UpdateLogic(deltaTime, actions);
}

void racer::RaceCart::Draw(pengine::Renderer* renderer)
{
	if (xModel != NULL)
	{
		renderer->SetActiveMatrix(myCachedMatrix->theMatrix); //should be called every frame

		pengine::MaterialWrapper* materialWrapper;
		int materialCount;
		xModel->GetMaterials(materialWrapper, materialCount);

		pengine::TextureWrapper* textureWrapper;
		int textureCount;
		xModel->GetTextures(textureWrapper, textureCount);

		renderer->SetMaterial(materialWrapper);
		renderer->SetTexture(textureWrapper);
		renderer->DrawSubset(xModel->GetMesh(), 0);
	}
}

void racer::RaceCart::SetXModel(pengine::XModel* p_xModel)
{
	xModel = p_xModel;
}