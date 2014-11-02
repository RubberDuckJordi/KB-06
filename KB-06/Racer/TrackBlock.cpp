#include "TrackBlock.h"

namespace racer
{
	TrackBlock::TrackBlock()
	{
		direction = NORTH;
		type = TYPE::STRAIGHT;
		defaultRadius = 10;
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

	void TrackBlock::SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ)
	{
		Entity::SetAll(x, y, z, yaw, pitch, roll, scaleX, scaleY, scaleZ);

		//kind of unneeded because the scale is always 1, but you never know :)
		float maxScale = abs(myCachedMatrix->data[0]);
		if (abs(myCachedMatrix->data[5]) > maxScale)
		{
			maxScale = abs(myCachedMatrix->data[5]);
		}
		if (abs(myCachedMatrix->data[10]) > maxScale)
		{
			maxScale = abs(myCachedMatrix->data[10]);
		}
		defaultRadius *= maxScale;
	}

	void TrackBlock::SetModel(pengine::Object3D* p_xModel)
	{
		model = p_xModel;
		defaultRadius = model->GetMaxRadius();
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