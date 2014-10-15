#ifndef _RACESCENEFACTORY_H_
#define _RACESCENEFACTORY_H_

#include "SceneFactory.h"
#include "Object3D.h"
#include <string>
#include "RaceScene.h"

namespace racer
{
	class RaceSceneFactory : public pengine::SceneFactory
	{
	public:
		RaceSceneFactory(pengine::ResourceManager* resourceManager);
		~RaceSceneFactory();

		pengine::Scene* CreateScene(RaceScene* raceScene);
		pengine::Scene* CreateScene(std::vector<std::string>* sceneFile, pengine::ResourceManager* resourceManager);

		void SetXModel2(pengine::Object3D*); //debug
		void SetXModel3(pengine::Object3D*); //debug
		void SetObject3D(pengine::Object3D*);
	private:
		pengine::Object3D* xModel2; //debug.
		pengine::Object3D* xModel3; //debug.
		pengine::Object3D* object3d;
	};
}
#endif