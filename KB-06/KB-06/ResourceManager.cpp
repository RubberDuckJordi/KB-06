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
	if (meshes.find(fileName) == meshes.end()){
		if (meshFactories.find(extension) != meshFactories.end()){
			std::pair<Resource::Mesh, std::vector<const std::string>> loadedMesh = meshFactories[extension]->Load(fileName);
			meshes[fileName] = loadedMesh.first;
			std::vector<std::string> elements;
			for (unsigned int i = 0; i < loadedMesh.second.size(); ++i){
				// load the material file by assuming everything afther the last '.' is the extension
				elements = Logger::StringHelper::split(loadedMesh.second.at(i), '.');
				LoadMaterial(loadedMesh.second.at(i), elements.back());
			}
		}
		else {
			logger->Log(Logger::Logger::ERR, "MeshLoader not found for extension:" + extension);
			return NULL;
		}
	}
	return &meshes[fileName];
}

void Resource::ResourceManager::AddMeshFactory(Resource::BaseMeshFactory* newMeshLoader)
{
	meshFactories[newMeshLoader->GetExtension()] = newMeshLoader;
}

Resource::Mesh* Resource::ResourceManager::LoadMaterial(const std::string& fileName, const std::string& extension)
{
	std::map<std::string, Material> newMaterials;
	if (Logger::StringHelper::EndsWith(fileName, ".mtl"))
	{
		newMaterials = MtlLoader::Load(fileName);
		//materials[file] = newMaterials;
	}
	return NULL;
}

