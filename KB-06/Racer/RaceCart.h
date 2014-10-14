#ifndef _RACECART_H_
#define _RACECART_H_

#include "Entity.h"
#include "Logger.h"
#include "Renderer.h"
#include "Object3D.h"
#include "CollisionEffect.h"
#include "Beam.h"
#include "Vector3.h"

namespace racer
{
	class RaceCart : public pengine::Entity, public pengine::Collidable
	{
	public:
		RaceCart();
		~RaceCart();
		void UpdateLogic(float deltaTime, std::map<pengine::Input, long>* actions);
		void Draw(pengine::Renderer* renderer);
		void SetObject3D(pengine::Object3D*); //debug
		void SetControllable(bool);
		
		void SetHorsePower(float);
		float GetHorsePower();
		
		void Brake(float percentage);
		void Throttle(float percentage);
		void Steer(float percentage);

		// Collidable functions
		void OnCollide(pengine::COLLISIONEFFECT*);
		void InitCollisionBox();
		pengine::Vector3* GetCollisionForceVector();
		float GetCollisionMass();
		pengine::Matrix* GetRenderMatrix();
		float GetRadius();
	private:
		float horsePower = 10;

		pengine::Object3D* xModel; //debug
		bool controllable;
	};
}
#endif