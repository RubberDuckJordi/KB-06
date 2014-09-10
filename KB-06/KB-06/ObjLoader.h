#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_
#include "ResourceManager.h"
#include <string>

class ObjLoader
{
public:
	static Mesh Load(std::string file, ResourceManager* resourceManager);
};
#endif