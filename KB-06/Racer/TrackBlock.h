#ifndef _TRACKBLOCK_H_
#define _TRACKBLOCK_H_

#include "Renderer.h"
#include "Entity.h"

class TrackBlock : public pengine::Entity
{
public:
	TrackBlock();
	~TrackBlock();

	void Draw(pengine::Renderer* renderer){};

	// mesh?
	// texture?

	// std::map<Vector3, PowerUpEntity>

	// void onEnter(RaceKart Kart);
	// void onPassedHalfway(RaceKart Kart);
	// void onLeave(RaceKart Kart);
};
#endif
