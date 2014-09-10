#include "stdafx.h"
#include "ResourceManager.h"
#include "StringHelper.h"
#include "ObjLoader.h"
#include "MtlLoader.h"


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::load(std::string file){
	if (StringHelper::EndsWith(file, ".obj.mesh")){
		meshes[file] = ObjLoader::Load(file, this);
	}
	else if (StringHelper::EndsWith(file, ".mtl")){
		materials[file] = MtlLoader::Load(file);
	}
}

