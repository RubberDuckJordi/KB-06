#include "TrackBlock.h"

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

void TrackBlock::CacheToRenderer(pengine::Renderer* renderer)
{
	model->CacheToRenderer(renderer);
}

float TrackBlock::GetMaxSquareSize()
{
	pengine::BEAM box;
	model->CreateCollisionBox(box);
	float max = box.width;
	if (max < box.height)
	{
		max = box.height;
	}
	return max;
}