#ifndef _RESOURCE_RESOURCE_H_
#define _RESOURCE_RESOURCE_H_

#include "ResourceManager.h"
namespace Resource
{
	class ResourceManager;
	class Resource
	{
	public:
		Resource();
		~Resource();
		//virtual void LoadResource(char* path, const ResourceManager* resourceManager) = 0;
		bool GetIsLoaded();
	protected:
		bool isLoaded;
	};
}
#endif