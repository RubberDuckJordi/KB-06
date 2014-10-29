#include "SceneFactory.h"

namespace pengine
{
	SceneFactory::SceneFactory(ResourceManager* p_resourceManager)
	{
		resourceManager = p_resourceManager;
	}

	SceneFactory::~SceneFactory()
	{
	}

	void SceneFactory::SetGroundResource(std::string p_groundResource)
	{
		groundResource = p_groundResource;
	}

	void SceneFactory::SetGroundTexture(std::string p_groundTexture)
	{
		groundTexture = p_groundTexture;
	}

	void SceneFactory::SetSkyboxTexture(std::string p_skyboxTexture)
	{
		skyboxTexture = p_skyboxTexture;
	}
}