#include "TrackBlock.h"

namespace racer
{
	TrackBlock::TrackBlock()
	{
		direction = NORTH;
		type = TYPE::STRAIGHT;
	}

	TrackBlock::~TrackBlock()
	{
	}

	void TrackBlock::Render(pengine::Renderer* renderer)
	{
		if (model != NULL)
		{
			renderer->SetActiveMatrix(myCachedMatrix); //should be called every frame
			model->ClearSkinnedVertices();
			model->UpdateAnimation();
			model->Render(renderer);
		}
	}

	void TrackBlock::SetDirection(Direction d)
	{
		direction = d;
	}

	void TrackBlock::SetModel(pengine::Object3D* p_xModel)
	{
		model = p_xModel;
	}

	void TrackBlock::SetBlockType(TrackBlock::TYPE _type)
	{
		type = _type;
	}

	Direction TrackBlock::GetDirection()
	{
		return direction;
	}

	TrackBlock::TYPE TrackBlock::GetBlockType()
	{
		return type;
	}

	void TrackBlock::SetPosition(float x, float y, float z)
	{
		Entity::SetPosition(x + positionOffset.x * scale.x, y + positionOffset.y * scale.y, z + positionOffset.z * scale.z);
	}

	void TrackBlock::SetPositionOffset(float x, float y, float z)
	{
		positionOffset.x = x;
		positionOffset.y = y;
		positionOffset.z = z;
	}

	pengine::Vector3* TrackBlock::GetPositionOffset()
	{
		return &positionOffset;
	}

	void TrackBlock::SetRotation(float yaw, float pitch, float roll)
	{
		Entity::SetRotation(yaw + rotationOffset.x, pitch + rotationOffset.y, roll + rotationOffset.z);
	}

	void TrackBlock::SetRotationOffset(float yaw, float pitch, float roll)
	{
		rotationOffset.x = yaw;
		rotationOffset.y = pitch;
		rotationOffset.z = roll;
	}

	pengine::Vector3* TrackBlock::GetRotationOffset()
	{
		return &rotationOffset;
	}

	float TrackBlock::GetMaxSquareSize()
	{
		pengine::BEAM box;
		model->CreateCollisionBox(box);
		float max = box.width;
		if (max < box.depth)
		{
			max = box.depth;
		}
		return max;
	}

	float TrackBlock::GetModelMinZ()
	{
		return model->GetMinZ();
	}

	float TrackBlock::GetModelMaxZ()
	{
		return model->GetMaxZ();
	}

	float TrackBlock::GetModelMinX()
	{
		return model->GetMinX();
	}

	float TrackBlock::GetModelMaxX()
	{
		return model->GetMaxX();
	}

	void TrackBlock::CacheToRenderer(pengine::Renderer* renderer)
	{
		model->CacheToRenderer(renderer);
	}

	void TrackBlock::OnCollide(pengine::COLLISIONEFFECT* effect)
	{

	}

	void TrackBlock::InitCollisionBox()
	{
		// Get bounds of model
		pengine::BEAM* rect = new pengine::BEAM();
		model->CreateCollisionBox(*rect);

		// Add transformation
		rect->x += position.x;
		rect->y += position.y;
		rect->z += position.z;

		if (type == TrackBlock::TYPE::STRAIGHT)
		{
			rect->yaw = rotation.x;
			rect->roll = rotation.y;
			rect->pitch = rotation.z;
		}
		else
		{
			rect->yaw = rotation.x + 180;
			rect->roll = rotation.y;
			rect->pitch = rotation.z;
		}


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
		rect->rotFrontTopLeft.y = rect->frontTopLeft.y + 1.0f;//we aren't doing pitch rotation (yet...)
		rect->rotFrontTopLeft.z = sin(angle - RADIANS(rect->yaw)) * radius;

		angle = atan2f(rect->frontTopRight.z, rect->frontTopRight.x);
		rect->rotFrontTopRight.x = cos(angle - RADIANS(rect->yaw)) * radius;
		rect->rotFrontTopRight.y = rect->frontTopRight.y + 1.0f;//we aren't doing pitch rotation (yet...)
		rect->rotFrontTopRight.z = sin(angle - RADIANS(rect->yaw)) * radius;

		angle = atan2f(rect->backTopLeft.z, rect->backTopLeft.x);
		rect->rotBackTopLeft.x = cos(angle - RADIANS(rect->yaw)) * radius;
		rect->rotBackTopLeft.y = rect->backTopLeft.y + 1.0f;//we aren't doing pitch rotation (yet...)
		rect->rotBackTopLeft.z = sin(angle - RADIANS(rect->yaw)) * radius;

		angle = atan2f(rect->backTopRight.z, rect->backTopRight.x);
		rect->rotBackTopRight.x = cos(angle - RADIANS(rect->yaw)) * radius;
		rect->rotBackTopRight.y = rect->backTopRight.y + 1.0f;//we aren't doing pitch rotation (yet...)
		rect->rotBackTopRight.z = sin(angle - RADIANS(rect->yaw)) * radius;

		collisionBox = *rect;
	}

	std::string TrackBlock::GetType()
	{
		return "racer::TrackBlock";
	}

	pengine::Vector3* TrackBlock::GetCollisionForceVector()
	{
		return new pengine::Vector3();
	}

	float TrackBlock::GetCollisionMass()
	{
		return 0.0f;
	}
}