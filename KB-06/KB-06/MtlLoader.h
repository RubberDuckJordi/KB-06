#ifndef _RESOURCE_MTLLOADER_H_
#define _RESOURCE_MTLLOADER_H_
#include "BaseMaterialLoader.h"
#include "Material.h"
#include <map>

namespace Resource
{
	class MtlLoader : public BaseMaterialLoader
	{
	public:
		std::map<std::string, Material> MtlLoader::Load(std::string file);
		std::string GetExtension();
	};
}
#endif

