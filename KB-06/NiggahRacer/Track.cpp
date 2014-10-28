#include "Track.h"


Track::Track()
{
}


Track::~Track()
{
}

void Track::SetPosition(float x, float y, float z){
	pengine::Entity::SetPosition(x, y, z);
	for (auto iterator = trackBlocks.begin(); iterator != trackBlocks.end(); ++iterator) {
		// todo relative position
	}
}

void Track::SetRotation(float yaw, float pitch, float roll){
	pengine::Entity::SetRotation(yaw, pitch, roll);
	for (auto iterator = trackBlocks.begin(); iterator != trackBlocks.end(); ++iterator) {
		// todo
	}
}

void Track::SetScale(float scaleX, float scaleY, float scaleZ){
	pengine::Entity::SetScale(scaleX, scaleY, scaleZ);
	for (auto iterator = trackBlocks.begin(); iterator != trackBlocks.end(); ++iterator) {
		// todo
	}
}

void Track::SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ)
{
	Entity::SetAll(x, y, z, yaw, pitch, roll, scaleX, scaleY, scaleZ);
	for (auto iterator = trackBlocks.begin(); iterator != trackBlocks.end(); ++iterator) {
		(*iterator)->SetAll(x, y, z, yaw, pitch, roll, scaleX, scaleY, scaleZ);
	}
}

void Track::Render(pengine::Renderer* renderer)
{
	for (auto iterator = trackBlocks.begin(); iterator != trackBlocks.end(); ++iterator) {
		(*iterator)->Render(renderer);
	}
}

void Track::AddTrackBlock(TrackBlock* trackBlock){
	trackBlocks.push_back(trackBlock);
}

void Track::AddTrackBlock(TrackBlock::TYPE trackBlockType, pengine::Object3D* model){
	Direction direction = Direction::NORTH;
	float x = 0;
	float y = 0;
	float z = 0;
	float yaw = 0;
	if (trackBlocks.size() > 0)
	{
		TrackBlock* prevTrackBLock = trackBlocks.back();
		direction = prevTrackBLock->GetDirection();
		x = prevTrackBLock->GetPositionOffset()->x;
		y = prevTrackBLock->GetPositionOffset()->y;
		z = prevTrackBLock->GetPositionOffset()->z;
		
		switch(direction)
		{
		case NORTH:	z -= trackBlockSize; break;
		case EAST: x -= trackBlockSize;  break;
		case SOUTH: z += trackBlockSize; break;
		case WEST: x += trackBlockSize;	break;
		}

		if (abs(x) > radius - trackBlockSize) radius = abs(x) + trackBlockSize;
		if (abs(z) > radius - trackBlockSize) radius = abs(z) + trackBlockSize;

		int newDirectionValue = direction;
		yaw = direction * 90;

		switch (trackBlockType)
		{
		case TrackBlock::TYPE::TURN_RIGHT:	newDirectionValue += 1;
			yaw += 90;
			if (newDirectionValue > 3)
			{
				newDirectionValue -= 4;
			}
			break;
		case TrackBlock::TYPE::TURN_LEFT:	
			yaw += 180;
			newDirectionValue -= 1;
			if (newDirectionValue < 0)
			{
				newDirectionValue += 4;
			}
			break;
		}
		switch (newDirectionValue){
		case 0: direction = NORTH; break;
		case 1: direction = EAST; break;
		case 2: direction = SOUTH; break;
		case 3: direction = WEST; break;
		}
	}
	trackBlocks.push_back(new TrackBlock(x, y, z, yaw, trackBlockType, direction, model));
}

float Track::GetRadius()
{
	float radius = 0.0f;
	for (auto & trackBlock : trackBlocks) 
	{
		radius += trackBlock->GetRadius();
	}
	return radius;
}

void Track::CacheToRenderer(pengine::Renderer* renderer)
{
	for (auto it = trackBlocks.begin(); it != trackBlocks.end(); ++it)
	{
		(*it)->CacheToRenderer(renderer);
	}
}
