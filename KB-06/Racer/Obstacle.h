#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "Entity.h"
#include "Logger.h"
#include "Renderer.h"
#include "Object3D.h"
#include "CollisionEffect.h"
#include "Beam.h"
#include "Vector3.h"
#include "TrackBlock.h"

namespace racer
{
	class Obstacle : public pengine::Entity, public pengine::Collidable
	{
	public:
		Obstacle();
		~Obstacle();
		void UpdateLogic(float deltaTime, std::map<pengine::Input, long>* actions);
		void Render(pengine::Renderer* renderer);
		void SetObject3D(pengine::Object3D*);
		void SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ);

		// Collidable functions
		void OnCollide(pengine::COLLISIONEFFECT* effect);
		void InitCollisionBox();
		pengine::Vector3* GetCollisionForceVector();
		float GetCollisionMass();
		std::string GetType();

		pengine::Matrix* GetRenderMatrix();
		float GetRadius();
		bool IsOnTrack();

		// Should be set to the first block by default

		void CacheToRenderer(pengine::Renderer* renderer);
		void SetTrackHeight(float height);

	private:
		// Every tick, the racecart should on track. We use this boolean to keep track of this
		bool isOnTrack;
		float trackHeight;

		float fallingTime;
		TrackBlock* lastCheckPoint;

		pengine::Object3D* model;
		float maxRadius;
		float maxScale;
	};
}
#endif