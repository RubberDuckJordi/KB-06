#ifndef _RACESCENE_H_
#define _RACESCENE_H_

#include "Scene.h"
#include "Input.h"

namespace racer
{
	class RaceScene : public pengine::Scene
	{
	public:
		RaceScene();
		~RaceScene();
		void Update(float deltaTime, std::map<pengine::Input, long>* actions);
		void SetRaceCart(pengine::Entity*);
		void RenderToTexture(int texture, pengine::Renderer* renderer);
		void Render(pengine::Renderer* renderer);

	private:
		pengine::Entity* raceCart;
		float elapsedTime;
	};
}

#endif