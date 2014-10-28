#ifndef _TRACK_H_
#define _TRACK_H_
#include <list>
#include "TrackBlock.h"
#include "Entity.h"

namespace racer
{
	class Track : public pengine::Entity
	{
	public:
		Track();
		~Track();
		void ValidateTrack();
		void Render(pengine::Renderer* renderer);
		void AddTrackBlock(TrackBlock* trackBlock);
		TrackBlock* AddTrackBlock(TrackBlock::TYPE trackBlockType, pengine::Object3D* model);
		void SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ);
		float GetRadius();
		void CacheToRenderer(pengine::Renderer* renderer);
	private:
		std::list<TrackBlock*> trackBlocks;
		float offsetX = 0.0f;
		float offsetY = 0.0f;
		float offsetZ = 0.0f;
	};
}
#endif