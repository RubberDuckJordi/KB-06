#include "RaceCart.h"

racer::RaceCart::RaceCart()
{

}

racer::RaceCart::~RaceCart()
{

}

void racer::RaceCart::UpdateLogic(float deltaTime, std::map<pengine::Input, long>* actions)
{
	if (controllable)
	{
		typedef std::map<pengine::Input, long>::iterator it_type;
		for (it_type iterator = (*actions).begin(); iterator != (*actions).end(); ++iterator)
		{
			float speed = static_cast<float>(iterator->second);
			Vector3 vector = *new Vector3(0.0f, 0.0f, 0.0f); // Must be declared before the switch

			switch (iterator->first)
			{
			case pengine::Input::KEY_S:
				Brake(1.0f);
				break;
			case pengine::Input::KEY_W:
				Throttle(1.0f);
				break;
			case pengine::Input::KEY_D:
				this->AddRotation(2.0f, 0.0f, 0.0f);
				break;
			case pengine::Input::KEY_A:
				this->AddRotation(-2.0f, 0.0f, 0.0f);
				break;
			case pengine::Input::KEY_0:
				// Imaginary collision
				vector.z = -5.0f;
				AddRelativeForce(&vector);
				break;
			default:
				break;
			}
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

		renderer->SetMaterialWrapper(materialWrapper);
		renderer->SetTexture(textureWrapper);
		renderer->DrawSubset(xModel->GetMesh(), 0);
	}
}

void racer::RaceCart::SetXModel(pengine::XModel* p_xModel)
{
	xModel = p_xModel;
}

void racer::RaceCart::SetControllable(bool p_controllable)
{
	controllable = p_controllable;
}

void racer::RaceCart::SetHorsePower(float p_horsePower)
{
	horsePower = p_horsePower;
}

float racer::RaceCart::GetHorsePower()
{
	return horsePower;
}

void racer::RaceCart::Brake(float percentage)
{
	// 5.0f could be replaced by braking power
	ApplyFriction(5.0f * percentage);
}

void racer::RaceCart::Throttle(float percentage)
{
	Vector3 vector;
	vector.z = horsePower * percentage;
	AddRelativeForce(&vector);
}