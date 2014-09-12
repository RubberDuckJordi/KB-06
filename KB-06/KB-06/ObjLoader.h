#ifndef _RESOURCE_OBJLOADER_H_
#define _RESOURCE_OBJLOADER_H_
#include "BaseMeshLoader.h"

namespace Resource
{
	class ObjLoader : public BaseMeshLoader
	{
	public:
		ObjLoader();
		Mesh Load(std::string file, const ResourceManager* resourceManager);
		std::string GetExtension();
	};
}

#endif