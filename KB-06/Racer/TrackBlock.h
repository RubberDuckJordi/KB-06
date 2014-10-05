#ifndef _TRACKBLOCK_H_
#define _TRACKBLOCK_H_

#include "Renderer.h"
#include "Entity.h"
#include "Logger.h"
#include "XModel.h"

class TrackBlock : public pengine::Entity
{
public:
	TrackBlock(float width, float height);
	~TrackBlock();

	void Draw(pengine::Renderer* renderer);
	void SetXModel(pengine::XModel*); //debug
	
	// mesh?
	// texture?

	// std::map<Vector3, PowerUpEntity>

	// void onEnter(RaceKart Kart);
	// void onPassedHalfway(RaceKart Kart);
	// void onLeave(RaceKart Kart);

	float height;
	float width;
private:
	pengine::XModel* xModel; //debug
};
#endif
