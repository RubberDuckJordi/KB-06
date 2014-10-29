#include "Track.h"


Track::Track()
{
}


Track::~Track()
{
}


void Track::SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ)
{
	Entity::SetAll(x, y, z, yaw, pitch, roll, scaleX, scaleY, scaleZ);
	for (auto iterator = trackBlocks.begin(); iterator != trackBlocks.end(); ++iterator)
	{
		(*iterator)->SetAll(x, y, z, yaw, pitch, roll, scaleX, scaleY, scaleZ);
	}
}

void Track::Render(pengine::Renderer* renderer)
{
	for (auto iterator = trackBlocks.begin(); iterator != trackBlocks.end(); ++iterator)
	{
		(*iterator)->Render(renderer);
	}
}

void Track::AddTrackBlock(TrackBlock* trackBlock)
{
	trackBlocks.push_back(trackBlock);
}

void Track::AddTrackBlock(TrackBlock::TYPE trackBlockType, pengine::Object3D* model)
{
	Direction direction = Direction::NORTH;
	float x = 0;
	float y = -model->GetMaxY();
	float z = 0;
	float yaw = 0;

	TrackBlock* newBlock = new TrackBlock();
	newBlock->SetModel(model);
	if (trackBlocks.size() > 0)
	{
		TrackBlock* previousBlock = trackBlocks.back();
		x = previousBlock->GetPosition()->x;
		z = previousBlock->GetPosition()->z;

		float maxZ = newBlock->GetModelMaxZ();
		switch (trackBlockType)
		{
		case TrackBlock::TYPE::LEFT:
			switch (previousBlock->GetDirection())
			{
			case NORTH:
				direction = WEST;
				if (previousBlock->GetType() == TrackBlock::TYPE::STRAIGHT)
				{
					z = previousBlock->GetPosition()->z - (previousBlock->GetMaxSquareSize() / 2) - maxZ;
				}
				else
				{
					z = previousBlock->GetPosition()->z - maxZ - maxZ;
				}
				break;
			case EAST:
				direction = NORTH;
				yaw = 90;
				if (previousBlock->GetType() == TrackBlock::TYPE::STRAIGHT)
				{
					x = previousBlock->GetPosition()->x - (previousBlock->GetMaxSquareSize() / 2) - maxZ;
				}
				else
				{
					x = previousBlock->GetPosition()->x - maxZ - maxZ;
				}
				break;
			case SOUTH:
				direction = EAST;
				yaw = -180;
				if (previousBlock->GetType() == TrackBlock::TYPE::STRAIGHT)
				{
					z = previousBlock->GetPosition()->z + (previousBlock->GetMaxSquareSize() / 2) + maxZ;
				}
				else
				{
					z = previousBlock->GetPosition()->z + maxZ + maxZ;
				}
				break;
			case WEST:
				direction = SOUTH;
				yaw = 270;
				if (previousBlock->GetType() == TrackBlock::TYPE::STRAIGHT)
				{
					x = previousBlock->GetPosition()->x + (previousBlock->GetMaxSquareSize() / 2) + maxZ;
				}
				else
				{
					x = previousBlock->GetPosition()->x + maxZ + maxZ;
				}
				break;
			}
			break;
		case TrackBlock::TYPE::RIGHT:
			switch (previousBlock->GetDirection())
			{
			case NORTH:
				direction = EAST;
				yaw = 270;
				if (previousBlock->GetType() == TrackBlock::TYPE::STRAIGHT)
				{
					z = previousBlock->GetPosition()->z - (previousBlock->GetMaxSquareSize() / 2) - maxZ;
				}
				else
				{
					z = previousBlock->GetPosition()->z - maxZ - maxZ;
				}
				break;
			case EAST:
				direction = SOUTH;
				if (previousBlock->GetType() == TrackBlock::TYPE::STRAIGHT)
				{
					x = previousBlock->GetPosition()->x - (previousBlock->GetMaxSquareSize() / 2) - maxZ;
				}
				else
				{
					x = previousBlock->GetPosition()->x - maxZ - maxZ;
				}
				break;
			case SOUTH:
				direction = WEST;
				yaw = 90;
				if (previousBlock->GetType() == TrackBlock::TYPE::STRAIGHT)
				{
					z = previousBlock->GetPosition()->z + (previousBlock->GetMaxSquareSize() / 2) + maxZ;
				}
				else
				{
					z = previousBlock->GetPosition()->z + maxZ + maxZ;
				}
				break;
			case WEST:
				yaw = -180;
				direction = NORTH;
				if (previousBlock->GetType() == TrackBlock::TYPE::STRAIGHT)
				{
					x = previousBlock->GetPosition()->x + (previousBlock->GetMaxSquareSize() / 2) + maxZ;
				}
				else
				{
					x = previousBlock->GetPosition()->x + maxZ + maxZ;
				}
				break;
			}
			break;
		case TrackBlock::TYPE::STRAIGHT:
			switch (previousBlock->GetDirection())
			{
			case NORTH:
				direction = NORTH;
				if (previousBlock->GetType() == TrackBlock::TYPE::STRAIGHT)
				{
					z = previousBlock->GetPosition()->z - (previousBlock->GetMaxSquareSize() / 2) - (newBlock->GetMaxSquareSize() / 2);
				}
				else
				{
					z = previousBlock->GetPosition()->z - (newBlock->GetMaxSquareSize() / 2) - previousBlock->GetModelMaxZ();
				}
				break;
			case EAST:
				yaw = -270;
				direction = EAST;
				if (previousBlock->GetType() == TrackBlock::TYPE::STRAIGHT)
				{
					x = previousBlock->GetPosition()->x - (previousBlock->GetMaxSquareSize() / 2) - (newBlock->GetMaxSquareSize() / 2);
				}
				else
				{
					x = previousBlock->GetPosition()->x - (newBlock->GetMaxSquareSize() / 2) - previousBlock->GetModelMaxZ();
				}
				break;
			case SOUTH:
				direction = SOUTH;
				if (previousBlock->GetType() == TrackBlock::TYPE::STRAIGHT)
				{
					z = previousBlock->GetPosition()->z + (previousBlock->GetMaxSquareSize() / 2) + (newBlock->GetMaxSquareSize() / 2);
				}
				else
				{
					z = previousBlock->GetPosition()->z + (newBlock->GetMaxSquareSize() / 2) + previousBlock->GetModelMaxZ();
				}
				break;
			case WEST:
				yaw = -90;
				direction = WEST;
				if (previousBlock->GetType() == TrackBlock::TYPE::STRAIGHT)
				{
					x = previousBlock->GetPosition()->x + (previousBlock->GetMaxSquareSize() / 2) + (newBlock->GetMaxSquareSize() / 2);
				}
				else
				{
					x = previousBlock->GetPosition()->x + (newBlock->GetMaxSquareSize() / 2) + previousBlock->GetModelMaxZ();
				}
				break;
			}
			break;
		}
	}
	newBlock->SetAll(x, y, z, yaw, 0, 0, 1, 1, 1);
	newBlock->SetDirection(direction);
	newBlock->SetType(trackBlockType);
	trackBlocks.push_back(newBlock);
}

float Track::GetRadius()
{
	float highestScale = 0;
	if (scale.x > highestScale) highestScale = scale.x;
	if (scale.y > highestScale) highestScale = scale.y;
	if (scale.z > highestScale) highestScale = scale.z;
	return radius*highestScale;
}

void Track::CacheToRenderer(pengine::Renderer* renderer)
{
	for (auto it = trackBlocks.begin(); it != trackBlocks.end(); ++it)
	{
		(*it)->CacheToRenderer(renderer);
	}
}