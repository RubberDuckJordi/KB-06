#ifndef _TRACK_H_
#define _TRACK_H_
#include <list>
#include "TrackBlock.h"

class Track : public pengine::Entity 
{
public:
	Track();
	~Track();

	void ValidateTrack();
	void Draw(pengine::Renderer* renderer){};
	void AddTrackBlock(TrackBlock trackBlock);

	void SetPosition(float x, float y, float z);
	void SetRotation(float yaw, float pitch, float roll);
	void SetScale(float scaleX, float scaleY, float scaleZ);
	void SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ);
private:
	std::list<TrackBlock> trackBlocks;
};
#endif