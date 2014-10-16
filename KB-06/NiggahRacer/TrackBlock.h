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
		TURN_LEFT,
		TURN_RIGHT
	};

	TrackBlock(float x, float y, float z, float yaw, TYPE type, Direction direction, pengine::Object3D* model);
	~TrackBlock();

	void Draw(pengine::Renderer* renderer);
	void SetXModel(pengine::Object3D*); //debug
	
	//float lenght;
	//float width;
	Direction GetDirection();

	void SetPosition(float x, float y, float z);
	void SetPositionOffset(float x, float y, float z);
	pengine::Vertex* GetPositionOffset();
	void SetRotation(float yaw, float pitch, float roll);
	void SetRotationOffset(float yaw, float pitch, float roll);
	pengine::Vertex* GetRotationOffset();
	
	float GetRadius();
private:
	pengine::Vertex positionOffset;
	pengine::Vertex rotationOffset;
	TYPE type;
	Direction direction;
	pengine::Object3D* xModel; //debug
};
#endif