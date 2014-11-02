#include "Track.h"

namespace racer
{
	Track::Track()
	{
	}
	Track::~Track()
	{
	}

	TrackBlock* Track::AddTrackBlock(TrackBlock::TYPE trackBlockType, pengine::Object3D* model)
	{
		Direction direction = Direction::NORTH;
		float x = 0;
		float y = 0;
		float z = 0;
		float yaw = 180; // 180 degrees to make first block face north :)

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
					yaw = 0;
					if (previousBlock->GetBlockType() == TrackBlock::TYPE::STRAIGHT)
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
					if (previousBlock->GetBlockType() == TrackBlock::TYPE::STRAIGHT)
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
					yaw = 180;
					if (previousBlock->GetBlockType() == TrackBlock::TYPE::STRAIGHT)
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
					if (previousBlock->GetBlockType() == TrackBlock::TYPE::STRAIGHT)
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
					if (previousBlock->GetBlockType() == TrackBlock::TYPE::STRAIGHT)
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
					yaw = 0;
					if (previousBlock->GetBlockType() == TrackBlock::TYPE::STRAIGHT)
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
					if (previousBlock->GetBlockType() == TrackBlock::TYPE::STRAIGHT)
					{
						z = previousBlock->GetPosition()->z + (previousBlock->GetMaxSquareSize() / 2) + maxZ;
					}
					else
					{
						z = previousBlock->GetPosition()->z + maxZ + maxZ;
					}
					break;
				case WEST:
					yaw = 180;
					direction = NORTH;
					if (previousBlock->GetBlockType() == TrackBlock::TYPE::STRAIGHT)
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
					yaw = 180;
					if (previousBlock->GetBlockType() == TrackBlock::TYPE::STRAIGHT)
					{
						z = previousBlock->GetPosition()->z - (previousBlock->GetMaxSquareSize() / 2) - (newBlock->GetMaxSquareSize() / 2);
					}
					else
					{
						z = previousBlock->GetPosition()->z - (newBlock->GetMaxSquareSize() / 2) - previousBlock->GetModelMaxZ();
					}
					break;
				case EAST:
					yaw = 270;
					direction = EAST;
					if (previousBlock->GetBlockType() == TrackBlock::TYPE::STRAIGHT)
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
					yaw = 0;
					if (previousBlock->GetBlockType() == TrackBlock::TYPE::STRAIGHT)
					{
						z = previousBlock->GetPosition()->z + (previousBlock->GetMaxSquareSize() / 2) + (newBlock->GetMaxSquareSize() / 2);
					}
					else
					{
						z = previousBlock->GetPosition()->z + (newBlock->GetMaxSquareSize() / 2) + previousBlock->GetModelMaxZ();
					}
					break;
				case WEST:
					yaw = 90;
					direction = WEST;
					if (previousBlock->GetBlockType() == TrackBlock::TYPE::STRAIGHT)
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
		newBlock->SetBlockType(trackBlockType);
		trackBlocks.push_back(newBlock);
		return newBlock;
	}

	std::list<TrackBlock*> Track::GetTrackBlocks()
	{
		return trackBlocks;
	}
}