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

Mesh* ResourceManager::loadMesh(std::string file){
	Mesh mesh;
	if (StringHelper::EndsWith(file, ".obj.mesh")){
		mesh = ObjLoader::Load(file, this);
		meshes[file] = mesh;
	}
	return &mesh;
}

std::map<std::string, Material>* ResourceManager::loadMaterials(std::string file){
	std::map<std::string, Material> newMaterials;
	if (StringHelper::EndsWith(file, ".mtl")){
		newMaterials = MtlLoader::Load(file);
		materials[file] = newMaterials;
	}
	return &newMaterials;
}

