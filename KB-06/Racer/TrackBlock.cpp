#include "TrackBlock.h"

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

void TrackBlock::SetType(TrackBlock::TYPE _type)
{
	type = _type;
}

Direction TrackBlock::GetDirection()
{
	return direction;
}

TrackBlock::TYPE TrackBlock::GetType()
{
	return type;
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