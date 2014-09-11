#ifndef _MTLLOADER_H_
#define _MTLLOADER_H_
#include "Material.h"
#include <map>
class MtlLoader
{
public:
	static std::map<std::string, Material> MtlLoader::Load(std::string file);
};
#endif

