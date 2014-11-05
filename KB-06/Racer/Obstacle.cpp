#include "Obstacle.h"

namespace racer
{
	Obstacle::Obstacle()
	{
		collides = false;
		isOnTrack = false;
		fallingTime = 0.0f;
	}

	Obstacle::~Obstacle()
	{

	}

	void Obstacle::UpdateLogic(float deltaTime, std::map<pengine::Input, long>* actions)
	{
		pengine::Entity::UpdateLogic(deltaTime, actions);

		defaultRadius = maxScale * maxRadius;
		if (!isOnTrack)
		{
			AddForce(new pengine::Vector3(0.0f, -100.0f * deltaTime * mass, 0.0f));
			fallingTime += deltaTime;
			if (!fallingTime >= 3.0f)
			{
				// To prevent glitching by flying from one trackblock to the next
				movementVector.x = 0.0f;
				movementVector.z = 0.0f;

				AddForce(new pengine::Vector3(0.0f, -100.0f * deltaTime * mass, 0.0f));
				fallingTime += deltaTime;
			}
		}

		// Reset the flags so we can determine them again next tick
		collides = false;
		isOnTrack = false;
	}

	void Obstacle::Render(pengine::Renderer* renderer)
	{
		if (model != NULL)
		{
			renderer->SetActiveMatrix(myCachedMatrix); //should be called every frame

			model->ClearSkinnedVertices();
			model->UpdateAnimation();
			model->Render(renderer);
		}
	}

	void Obstacle::SetObject3D(pengine::Object3D* p_xModel)
	{
		model = p_xModel;
	}

	void Obstacle::OnCollide(pengine::COLLISIONEFFECT* effect)
	{
		if (!effect->isStatic)
		{
			collides = true;
			RevertPreviousMovementStep();
			pengine::Vector3* vector = new pengine::Vector3(effect->forceVectorX, effect->forceVectorY, effect->forceVectorZ);
			AddForce(vector, effect->mass);
		}
		else
		{
			if (effect->type == "racer::TrackBlock")
			{
				isOnTrack = true;
			}
			else
			{
				// if there is collision with a static object, stand still immediately
				collides = true;
				movementVector.x = 0.0f;
				movementVector.y = 0.0f;
				movementVector.z = 0.0f;
				RevertPreviousMovementStep();
			}
		}
	}

	void Obstacle::SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ)
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

	void Obstacle::InitCollisionBox()
	{
		// Get bounds of model
		pengine::BEAM* rect = new pengine::BEAM();
		model->CreateCollisionBox(*rect);

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
		rect->rotFrontBottomLeft.y = position.y + rect->frontBottomLeft.y;//we aren't doing pitch rotation (yet...)
		rect->rotFrontBottomLeft.z = sin(angle - RADIANS(rect->yaw)) * radius;

		angle = atan2f(rect->frontBottomRight.z, rect->frontBottomRight.x);
		rect->rotFrontBottomRight.x = cos(angle - RADIANS(rect->yaw)) * radius;
		rect->rotFrontBottomRight.y = position.y + rect->frontBottomRight.y;//we aren't doing pitch rotation (yet...)
		rect->rotFrontBottomRight.z = sin(angle - RADIANS(rect->yaw)) * radius;

		angle = atan2f(rect->backBottomLeft.z, rect->backBottomLeft.x);
		rect->rotBackBottomLeft.x = cos(angle - RADIANS(rect->yaw)) * radius;
		rect->rotBackBottomLeft.y = position.y + rect->backBottomLeft.y;//we aren't doing pitch rotation (yet...)
		rect->rotBackBottomLeft.z = sin(angle - RADIANS(rect->yaw)) * radius;

		angle = atan2f(rect->backBottomRight.z, rect->backBottomRight.x);
		rect->rotBackBottomRight.x = cos(angle - RADIANS(rect->yaw)) * radius;
		rect->rotBackBottomRight.y = position.y + rect->backBottomRight.y;//we aren't doing pitch rotation (yet...)
		rect->rotBackBottomRight.z = sin(angle - RADIANS(rect->yaw)) * radius;

		angle = atan2f(rect->frontTopLeft.z, rect->frontTopLeft.x);
		rect->rotFrontTopLeft.x = cos(angle - RADIANS(rect->yaw)) * radius;
		rect->rotFrontTopLeft.y = position.y + rect->frontTopLeft.y;//we aren't doing pitch rotation (yet...)
		rect->rotFrontTopLeft.z = sin(angle - RADIANS(rect->yaw)) * radius;

		angle = atan2f(rect->frontTopRight.z, rect->frontTopRight.x);
		rect->rotFrontTopRight.x = cos(angle - RADIANS(rect->yaw)) * radius;
		rect->rotFrontTopRight.y = position.y + rect->frontTopRight.y;//we aren't doing pitch rotation (yet...)
		rect->rotFrontTopRight.z = sin(angle - RADIANS(rect->yaw)) * radius;

		angle = atan2f(rect->backTopLeft.z, rect->backTopLeft.x);
		rect->rotBackTopLeft.x = cos(angle - RADIANS(rect->yaw)) * radius;
		rect->rotBackTopLeft.y = position.y + rect->backTopLeft.y;//we aren't doing pitch rotation (yet...)
		rect->rotBackTopLeft.z = sin(angle - RADIANS(rect->yaw)) * radius;

		angle = atan2f(rect->backTopRight.z, rect->backTopRight.x);
		rect->rotBackTopRight.x = cos(angle - RADIANS(rect->yaw)) * radius;
		rect->rotBackTopRight.y = position.y + rect->backTopRight.y;//we aren't doing pitch rotation (yet...)
		rect->rotBackTopRight.z = sin(angle - RADIANS(rect->yaw)) * radius;

		collisionBox = *rect;
	}

	std::string Obstacle::GetType()
	{
		return "racer::Obstacle";
	}

	pengine::Vector3* Obstacle::GetCollisionForceVector()
	{
		return &movementVector;
	}

	float Obstacle::GetCollisionMass()
	{
		return mass;
	}

	float Obstacle::GetRadius()
	{
		float radius = collisionBox.depth * scale.z;
		return radius;
	}

	void Obstacle::CacheToRenderer(pengine::Renderer* renderer)
	{
		model->CacheToRenderer(renderer);
	}

	bool Obstacle::IsOnTrack()
	{
		return isOnTrack;
	}

	void Obstacle::SetTrackHeight(float height)
	{
		trackHeight = height;
	}
}