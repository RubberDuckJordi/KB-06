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

void Track::SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ){
	pengine::Entity::SetAll(x, y, z, yaw, pitch, roll, scaleX, scaleY, scaleZ);
	for (auto iterator = trackBlocks.begin(); iterator != trackBlocks.end(); ++iterator) {
		// todo
	}
}