#ifndef _RESOURCE_OBJLOADER_H_
#define _RESOURCE_OBJLOADER_H_
#include "ResourceManager.h"
#include <string>

namespace Resource
{
	class ObjLoader
	{
	public:
		static Mesh Load(std::string file, ResourceManager* resourceManager);
	};
}

#endif