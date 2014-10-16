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
			pengine::Vector3 vector = *new pengine::Vector3(0.0f, 0.0f, 0.0f); // Must be declared before the switch

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
		renderer->SetActiveMatrix(myCachedMatrix); //should be called every frame

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
	pengine::Vector3 vector;
	vector.z = horsePower * percentage;
	AddRelativeForce(&vector);
}

void racer::RaceCart::Steer(float percentage)
{
	pengine::Vector3 vector;

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

void racer::RaceCart::OnCollide(pengine::COLLISIONEFFECT* effect)
{
	pengine::Vector3* vector = new pengine::Vector3(effect->forceVectorX, effect->forceVectorY, effect->forceVectorZ);
	AddForce(vector, effect->mass);
}

void racer::RaceCart::InitCollisionBox()
{
	// Get bounds of model
	pengine::BEAM* rect = new pengine::BEAM();
	xModel->CreateCollisionBox(*rect);

	// Add transformation
	rect->x += position.x;// -rect->width / 8;
	rect->y += position.y;
	rect->z += position.z;// +rect->depth / 4;

	rect->width = rect->width / 2;
	rect->height = rect->height / 2;
	rect->depth = rect->depth / 2;

	// Add rotation
	rect->yaw = rotation.x;
	rect->pitch = rotation.y;
	rect->roll = rotation.z;

	float radius = sqrt(pow(rect->frontBottomLeft.x, 2) + pow(rect->frontBottomLeft.z, 2));//abc
	float angle = 0;

	angle = atan2f(rect->frontBottomLeft.z, rect->frontBottomLeft.x);
	rect->rotFrontBottomLeft.x = cos(angle - RADIANS(rect->yaw)) * radius;
	rect->rotFrontBottomLeft.y = rect->frontBottomLeft.y;//we aren't doing pitch rotation (yet...)
	rect->rotFrontBottomLeft.z = sin(angle - RADIANS(rect->yaw)) * radius;

	angle = atan2f(rect->frontBottomRight.z, rect->frontBottomRight.x);
	rect->rotFrontBottomRight.x = cos(angle - RADIANS(rect->yaw)) * radius;
	rect->rotFrontBottomRight.y = rect->frontBottomRight.y;//we aren't doing pitch rotation (yet...)
	rect->rotFrontBottomRight.z = sin(angle - RADIANS(rect->yaw)) * radius;

	angle = atan2f(rect->backBottomLeft.z, rect->backBottomLeft.x);
	rect->rotBackBottomLeft.x = cos(angle - RADIANS(rect->yaw)) * radius;
	rect->rotBackBottomLeft.y = rect->backBottomLeft.y;//we aren't doing pitch rotation (yet...)
	rect->rotBackBottomLeft.z = sin(angle - RADIANS(rect->yaw)) * radius;

	angle = atan2f(rect->backBottomRight.z, rect->backBottomRight.x);
	rect->rotBackBottomRight.x = cos(angle - RADIANS(rect->yaw)) * radius;
	rect->rotBackBottomRight.y = rect->backBottomRight.y;//we aren't doing pitch rotation (yet...)
	rect->rotBackBottomRight.z = sin(angle - RADIANS(rect->yaw)) * radius;

	angle = atan2f(rect->frontTopLeft.z, rect->frontTopLeft.x);
	rect->rotFrontTopLeft.x = cos(angle - RADIANS(rect->yaw)) * radius;
	rect->rotFrontTopLeft.y = rect->frontTopLeft.y;//we aren't doing pitch rotation (yet...)
	rect->rotFrontTopLeft.z = sin(angle - RADIANS(rect->yaw)) * radius;

	angle = atan2f(rect->frontTopRight.z, rect->frontTopRight.x);
	rect->rotFrontTopRight.x = cos(angle - RADIANS(rect->yaw)) * radius;
	rect->rotFrontTopRight.y = rect->frontTopRight.y;//we aren't doing pitch rotation (yet...)
	rect->rotFrontTopRight.z = sin(angle - RADIANS(rect->yaw)) * radius;

	angle = atan2f(rect->backTopLeft.z, rect->backTopLeft.x);
	rect->rotBackTopLeft.x = cos(angle - RADIANS(rect->yaw)) * radius;
	rect->rotBackTopLeft.y = rect->backTopLeft.y;//we aren't doing pitch rotation (yet...)
	rect->rotBackTopLeft.z = sin(angle - RADIANS(rect->yaw)) * radius;

	angle = atan2f(rect->backTopRight.z, rect->backTopRight.x);
	rect->rotBackTopRight.x = cos(angle - RADIANS(rect->yaw)) * radius;
	rect->rotBackTopRight.y = rect->backTopRight.y;//we aren't doing pitch rotation (yet...)
	rect->rotBackTopRight.z = sin(angle - RADIANS(rect->yaw)) * radius;

	collisionBox = *rect;
}

pengine::Vector3* racer::RaceCart::GetCollisionForceVector()
{
	return &movementVector;
}

float racer::RaceCart::GetCollisionMass()
{
	return mass;
}

float racer::RaceCart::GetRadius(){
	float radius = collisionBox.depth * scale.z;
	return radius;
}