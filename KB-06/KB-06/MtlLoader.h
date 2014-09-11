#ifndef _RESOURCE_MTLLOADER_H_
#define _RESOURCE_MTLLOADER_H_
#include "Material.h"
#include <map>

namespace Resource
{
	class MtlLoader
	{
	public:
		static std::map<std::string, Material> MtlLoader::Load(std::string file);
	};
}

#endif

