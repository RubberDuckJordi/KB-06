#ifndef _RESOURCE_RESOURCEFACTORY_H_
#define _RESOURCE_RESOURCEFACTORY_H_

#include "Resource.h"

namespace Resource {
	class Resource;
	class ResourceManager;

	class ResourceFactory
	{
	public:
		ResourceFactory();
		~ResourceFactory();
		virtual Resource* LoadResource(char* path, ResourceManager* rsmgr) = 0;
	};
};
#endif
