#ifndef _RACESCENEFACTORY_H_
#define _RACESCENEFACTORY_H_

#include "SceneFactory.h"
#include "XModel.h"
#include <string>

namespace racer
{
	class RaceSceneFactory : public pengine::SceneFactory
	{
	public:
		RaceSceneFactory(pengine::ResourceManager* resourceManager);
		~RaceSceneFactory();
		pengine::Scene* CreateScene();
		void SetXModel(pengine::XModel*); //debug
		void SetXModel2(pengine::XModel*); //debug

	private:
		pengine::XModel* xModel; //debug.
		pengine::XModel* xModel2; //debug.
	};
}

#endif