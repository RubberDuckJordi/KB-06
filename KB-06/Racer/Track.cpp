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
		(*iterator)->SetAll(x + offsetX, y + offsetY, z + offsetZ, yaw, pitch, roll, scaleX, scaleY, scaleZ);
		offsetZ += (*iterator)->lenght;
		logger->Log(pengine::Logger::DEBUG, std::to_string(offsetZ));
	}
}

void Track::Draw(pengine::Renderer* renderer)
{
	for (auto iterator = trackBlocks.begin(); iterator != trackBlocks.end(); ++iterator) {
		(*iterator)->Draw(renderer);
	}
}

void Track::AddTrackBlock(TrackBlock* trackBlock){
	trackBlocks.push_back(trackBlock);
}