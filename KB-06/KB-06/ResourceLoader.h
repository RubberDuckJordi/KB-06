#pragma once
#include "Mesh.h"

class ResourceLoader
{
public:
	ResourceLoader();
	~ResourceLoader();
	static virtual Mesh Load(std::string file, ResourceManager* resourceManager) = 0;;
};

