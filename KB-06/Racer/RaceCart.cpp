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
			case pengine::Input::KEY_E:
				AddRotation(0.0f, 5.0f, 0.0f);
				break;
			case pengine::Input::KEY_S:
				Brake(1.0f);
				break;
			case pengine::Input::KEY_W:
				Throttle(1.0f);
				break;
			case pengine::Input::KEY_D:
				Steer(0.5f);
				break;
			case pengine::Input::KEY_A:
				Steer(-0.5f);
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

		xModel->ClearSkinnedVertices();
		xModel->UpdateAnimation();
		xModel->Draw(renderer);
	}
}

void racer::RaceCart::SetObject3D(pengine::Object3D* p_xModel)
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

void racer::RaceCart::Steer(float percentage)
{
	Vector3 vector;

	// Get current movement magnitude
	float magnitude = movementVector.GetMagnitude();
	// Rotate the object according to the speed
	this->AddRotation(percentage * sqrt(magnitude) * 2.0f, 0.0f, 0.0f);

	// Reset the speed
	movementVector.x = 0.0f;
	movementVector.y = 0.0f;
	movementVector.z = 0.0f;

	// Move the object forward relative to itself
	vector.z = magnitude * mass;
	AddRelativeForce(&vector);

	// Add friction
	ApplyFriction(abs(percentage) * 5.0f);
}