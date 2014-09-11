#include "stdafx.h"
#include "ResourceManager.h"
#include "StringHelper.h"
#include "ObjLoader.h"
#include "MtlLoader.h"


Resource::ResourceManager::ResourceManager()
{
}


Resource::ResourceManager::~ResourceManager()
{
}

Resource::Mesh* Resource::ResourceManager::loadMesh(std::string file){
	Mesh mesh;
	if (Logger::StringHelper::EndsWith(file, ".obj.mesh")){
		mesh = ObjLoader::Load(file, this);
		meshes[file] = mesh;
	}
	return &mesh;
}

std::map<std::string, Resource::Material>* Resource::ResourceManager::loadMaterials(std::string file){
	std::map<std::string, Material> newMaterials;
	if (Logger::StringHelper::EndsWith(file, ".mtl")){
		newMaterials = MtlLoader::Load(file);
		materials[file] = newMaterials;
	}
	return &newMaterials;
}

