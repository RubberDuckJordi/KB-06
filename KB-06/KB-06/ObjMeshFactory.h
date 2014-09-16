#ifndef _RESOURCE_OBJFACTORY_H_
#define _RESOURCE_OBJFACTORY_H_
#include "BaseMeshFactory.h"

namespace Resource
{
	class ObjMeshFactory : public BaseMeshFactory
	{
	public:
		Mesh Load(const std::string file, const ResourceManager* resourceManager);
		std::string GetExtension();
	};
}

#endif