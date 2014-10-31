#ifndef _RACESCENEFACTORY_H_
#define _RACESCENEFACTORY_H_

#include "SceneFactory.h"
#include "Object3D.h"
#include <string>

namespace racer
{
	class RaceSceneFactory : public pengine::SceneFactory
	{
	public:
		RaceSceneFactory();
		~RaceSceneFactory();
		pengine::Scene* CreateScene(std::vector<std::string>* sceneFile, pengine::ResourceManager* resourceManager);
	};
}
#endif