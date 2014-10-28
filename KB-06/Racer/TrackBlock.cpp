#include "TrackBlock.h"
#include "Vector3.h"

namespace racer
{
	TrackBlock::TrackBlock(float x, float y, float z, float yaw, TYPE trackType, Direction trackdirection, pengine::Object3D* _model)
	{
		SetPositionOffset(x, y, z);
		SetRotationOffset(yaw, 0, 0);
		type = trackType;
		direction = trackdirection;
		model = _model;
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

	void TrackBlock::SetModel(pengine::Object3D* p_xModel)
	{
		model = p_xModel;
	}
	Direction TrackBlock::GetDirection(){
		return direction;
	}

	void TrackBlock::SetPosition(float x, float y, float z)
	{
		Entity::SetPosition(x + positionOffset.x * scale.x, y + positionOffset.y * scale.y, z + positionOffset.z * scale.z);
	}

	void TrackBlock::SetPositionOffset(float x, float y, float z){
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

	pengine::Vector3* TrackBlock::GetRotationOffset(){
		return &rotationOffset;
	}

	float TrackBlock::GetRadius(){
		return 10.0f;
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
		rect->x += position.x;// -rect->width / 8;
		rect->y += position.y;
		rect->z += position.z;// +rect->depth / 4;

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

	pengine::Vector3* TrackBlock::GetCollisionForceVector()
	{
		return new pengine::Vector3();
	}

	float TrackBlock::GetCollisionMass()
	{
		return 0.0f;
	}

	std::string TrackBlock::GetType()
	{
		return "racer::TrackBlock";
	}
}