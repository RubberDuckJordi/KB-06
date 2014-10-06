#ifndef _PENGINE_SCENEFACTORY_H_
#define _PENGINE_SCENEFACTORY_H_

#include "ResourceManager.h"
#include "Scene.h"
#include <map>

namespace pengine
{
	class SceneFactory 
	{
	public:
		SceneFactory(ResourceManager* resourceManager);
		~SceneFactory();
		virtual Scene* CreateScene() = 0;
		void SetGroundResource(std::string);
		void SetGroundTexture(std::string p_groundTexture);
		void SetSkyboxTexture(std::string p_skyboxTexture);

	protected:
		ResourceManager* resourceManager;
		std::string groundResource;
		std::string groundTexture;
		std::string skyboxTexture;
	};
}
#endif