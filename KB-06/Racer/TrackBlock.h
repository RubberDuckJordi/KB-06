#ifndef _TRACKBLOCK_H_
#define _TRACKBLOCK_H_

#include "Renderer.h"
#include "Entity.h"
#include "Logger.h"
#include "XModel.h"
#include "Object3D.h"

class TrackBlock : public pengine::Entity
{
public:
	TrackBlock(float width, float lenght);
	~TrackBlock();

	void Draw(pengine::Renderer* renderer);
	void SetXModel(pengine::Object3D*); //debug
	
	// mesh?
	// texture?

	// std::map<Vector3, PowerUpEntity>

	// void onEnter(RaceKart Kart);
	// void onPassedHalfway(RaceKart Kart);
	// void onLeave(RaceKart Kart);

	float lenght;
	float width;
private:
	pengine::Object3D* xModel; //debug
};
#endif
