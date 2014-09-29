#ifndef _RACECART_H_
#define _RACECART_H_

#include "Entity.h"
#include "Logger.h"
#include "Renderer.h"
#include "XModel.h"

namespace racer
{
	class RaceCart : public pengine::Entity 
	{
	public:
		RaceCart();
		~RaceCart();
		void UpdateLogic(float deltaTime, std::map<pengine::Input, long>* actions);
		void Draw(pengine::Renderer* renderer);
		void SetXModel(pengine::XModel*); //debug

	private:
		pengine::XModel* xModel; //debug
	};
}
#endif