#ifndef _RESOURCE_MTLLOADER_H_
#define _RESOURCE_MTLLOADER_H_
#include "Material.h"
#include <map>
#include "ResourceFactory.h"

namespace Resource
{
	class MtlLoader : public ResourceFactory
	{
	public:
		static std::map<std::string, Material> MtlLoader::Load(std::string file);
		Resource* LoadResource(char* path, ResourceManager* rsmgr);
	};
}

#endif

