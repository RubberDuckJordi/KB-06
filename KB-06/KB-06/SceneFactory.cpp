#include "SceneFactory.h"

namespace pengine
{
	SceneFactory::SceneFactory(ResourceManager* p_resourceManager)
	{
		resourceManager = p_resourceManager;
	}

	SceneFactory::~SceneFactory()
	{
		delete resourceManager;
	}
}