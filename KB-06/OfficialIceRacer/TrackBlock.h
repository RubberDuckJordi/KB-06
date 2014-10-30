#ifndef _TRACKBLOCK_H_
#define _TRACKBLOCK_H_
#include "Renderer.h"
#include "Entity.h"
#include "Logger.h"
#include "Object3D.h"
#include "Collidable.h"

namespace racer
{
	enum Direction
	{
		NORTH = 0,
		EAST = 1,
		SOUTH = 2,
		WEST = 3
	};

	class TrackBlock : public pengine::Entity, public pengine::Collidable
	{
	public:

		enum TYPE
		{
			STRAIGHT,
			LEFT,
			RIGHT
		};

		TrackBlock();
		~TrackBlock();
		void Render(pengine::Renderer* renderer);
		void SetModel(pengine::Object3D* model);
		Direction GetDirection();
		void SetPosition(float x, float y, float z);
		void SetPositionOffset(float x, float y, float z);
		pengine::Vector3* GetPositionOffset();
		void SetRotation(float yaw, float pitch, float roll);
		void SetRotationOffset(float yaw, float pitch, float roll);
		pengine::Vector3* GetRotationOffset();
		void CacheToRenderer(pengine::Renderer* renderer);
		float GetMaxSquareSize();

		void SetDirection(Direction direction);
		void SetBlockType(TYPE type);

		TYPE GetBlockType();
		float GetModelMinZ();
		float GetModelMaxZ();
		float GetModelMinX();
		float GetModelMaxX();

		// Collidable functions
		void OnCollide(pengine::COLLISIONEFFECT* effect);
		void InitCollisionBox();
		pengine::Vector3* GetCollisionForceVector();
		float GetCollisionMass();
		std::string GetType();

	private:
		pengine::Vector3 positionOffset;
		pengine::Vector3 rotationOffset;
		TYPE type;
		Direction direction;
		pengine::Object3D* model;
	};
}
#endif
