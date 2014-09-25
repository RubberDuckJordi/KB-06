#ifndef _RESOURCE_OBJFACTORY_H_
#define _RESOURCE_OBJFACTORY_H_

#include "BaseMeshLoader.h"

namespace Resource
{
	class ObjMeshLoader : public BaseMeshLoader
	{
	public:
		Mesh Load(const std::string file);
		std::string GetExtension();
	};
}
#endif