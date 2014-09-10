#ifndef _MTLLOADER_H_
#define _MTLLOADER_H_
#include <string>
#include "Material.h"
class MtlLoader
{
public:
	static Material Load(std::string file);
};
#endif

