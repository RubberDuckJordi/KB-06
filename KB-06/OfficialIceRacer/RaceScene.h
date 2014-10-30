#ifndef _RACESCENE_H_
#define _RACESCENE_H_

#include "Scene.h"
#include "Input.h"
#include "RaceKart.h"

namespace racer
{
	class RaceScene : public pengine::Scene
	{
	public:
		RaceScene();
		~RaceScene();
		void Update(float deltaTime, std::map<pengine::Input, long>* actions);
		void SetRaceKart(RaceKart*);
		void RenderToTexture(int texture, pengine::Renderer* renderer);
		void Render(pengine::Renderer* renderer);

	private:
		bool loss;
		bool win;
		RaceKart* raceKart;
		float elapsedTime;
	};
}

#endif