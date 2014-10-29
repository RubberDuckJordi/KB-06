#ifndef _RACECART_H_
#define _RACECART_H_

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
	class RaceCart : public pengine::Entity, public pengine::Collidable
	{
	public:
		RaceCart();
		~RaceCart();
		void UpdateLogic(float deltaTime, std::map<pengine::Input, long>* actions);
		void Render(pengine::Renderer* renderer);
		void SetObject3D(pengine::Object3D*);
		void SetControllable(bool);
		
		void SetHorsePower(float);
		float GetHorsePower();
		
		void Brake(float percentage);
		void Throttle(float percentage);
		void Steer(float percentage);

		void AddCheckPoint(TrackBlock* checkPoint);

		// Collidable functions
		void OnCollide(pengine::COLLISIONEFFECT* effect);
		void InitCollisionBox();
		pengine::Vector3* GetCollisionForceVector();
		float GetCollisionMass();
		std::string GetType();

		std::list<TrackBlock*>* GetCheckPoints();

		pengine::Matrix* GetRenderMatrix();
		float GetRadius();
		bool IsOnTrack();

		// Should be set to the first block by default
		void SetLastCheckPoint(TrackBlock* checkPoint);

		void CacheToRenderer(pengine::Renderer* renderer);
		void SetTrackHeight(float height);

	private:
		// Every tick, the racecart should on track. We use this boolean to keep track of this
		bool isOnTrack;
		float horsePower = 10;
		float trackHeight;

		float fallingTime;
		TrackBlock* lastCheckPoint;

		std::list<TrackBlock*> checkPoints;
		pengine::Object3D* model;
		bool controllable;
	};
}
#endif