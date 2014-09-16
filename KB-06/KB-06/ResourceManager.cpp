#include "stdafx.h"
#include "ResourceManager.h"
#include "StringHelper.h"
#include "ObjMeshFactory.h"
#include "MtlLoader.h"


Resource::ResourceManager::ResourceManager()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}


Resource::ResourceManager::~ResourceManager()
{
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}

Resource::Mesh* Resource::ResourceManager::LoadMesh(const std::string& fileName, const std::string& extension)
{
	if (meshLoaders.find(extension) != meshLoaders.end()){
		meshes[fileName] = meshLoaders[extension]->Load(fileName, this);
		return &meshes[fileName];
	}
	else {
		logger->Log(Logger::Logger::ERR, "MeshLoader not found for extension:" + extension);
		return NULL;
	}
}

void Resource::ResourceManager::AddMeshLoader(Resource::BaseMeshLoader* newMeshLoader)
{
	meshLoaders[newMeshLoader->GetExtension()] = newMeshLoader;
}

std::map<std::string, Resource::Material>* Resource::ResourceManager::loadMaterials(std::string file)
{
	std::map<std::string, Material> newMaterials;
	if (Logger::StringHelper::EndsWith(file, ".mtl"))
	{
		newMaterials = MtlLoader::Load(file);
		materials[file] = newMaterials;
	}
	return &materials[file];
}

