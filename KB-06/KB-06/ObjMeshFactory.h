#ifndef _RESOURCE_OBJFACTORY_H_
#define _RESOURCE_OBJFACTORY_H_
#include "BaseMeshFactory.h"

namespace Resource
{
	class ObjMeshFactory : public BaseMeshFactory
	{
	public:
		Mesh Load(const std::string file);
		std::string GetExtension();
	};
}

#endif