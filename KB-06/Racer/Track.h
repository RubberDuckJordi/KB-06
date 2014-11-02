#ifndef _TRACK_H_
#define _TRACK_H_
#include <list>
#include "TrackBlock.h"
#include "Entity.h"

namespace racer
{
	class Track
	{
	public:
		Track();
		~Track();
		TrackBlock* AddTrackBlock(TrackBlock::TYPE trackBlockType, pengine::Object3D* model);
		std::list<TrackBlock*> GetTrackBlocks();
	private:
		std::list<TrackBlock*> trackBlocks;
	};
}
#endif