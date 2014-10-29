#ifndef _TRACKBLOCK_H_
#define _TRACKBLOCK_H_

#include "Renderer.h"
#include "Entity.h"
#include "Logger.h"
#include "Object3D.h"

enum Direction {
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};


class TrackBlock : public pengine::Entity
{
public:
	static enum TYPE {
		STRAIGHT,
		LEFT,
		RIGHT
	};

	TrackBlock();
	~TrackBlock();

	void Render(pengine::Renderer* renderer);
	void SetDirection(Direction direction);
	void SetModel(pengine::Object3D* model);
	void SetType(TYPE type);

	Direction GetDirection();
	TYPE GetType();

	void CacheToRenderer(pengine::Renderer* renderer);

	float GetMaxSquareSize();
	float GetModelMinZ();
	float GetModelMaxZ();
	float GetModelMinX();
	float GetModelMaxX();

private:
	Direction direction;
	TYPE type;
	pengine::Object3D* model;
};
#endif
