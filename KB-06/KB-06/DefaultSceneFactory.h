#ifndef _PENGINE_DEFAULT_SCENE_FACTORY_H_
#define _PENGINE_DEFAULT_SCENE_FACTORY_H_

#include "SceneFactory.h"
#include "XModel.h"

namespace pengine
{
	class DefaultSceneFactory : public SceneFactory
	{
	public:
		DefaultSceneFactory(ResourceManager* resourceManager);
		~DefaultSceneFactory();
		Scene* CreateScene();
		void SetXModel(XModel*); //debug
	private:

		XModel* xModel; //debug.
	};
}
#endif