#include "stdafx.h"
#include "ResourceManager.h"
#include "StringHelper.h"
#include "ObjLoader.h"
#include "MtlLoader.h"


Resource::ResourceManager::ResourceManager()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}


Resource::ResourceManager::~ResourceManager()
{
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}

Resource::Resource* Resource::ResourceManager::GetResource(char* path, char* extension)
{
	if (resourceMap.find(path) == resourceMap.end())
	{
		logger->Log(Logger::Logger::DEBUG, "Resource should get loaded now!");
		std::string pathStr = path;
		
		//char* extension = &pathStr.substr(pathStr.find_last_of(".") + 1)[0];
		if (factoryForExtension.find(extension) != factoryForExtension.end())
		{
			Resource* r = factoryForExtension[extension]->LoadResource(path, this);
			if (r->GetIsLoaded())
			{
				resourceMap.insert(std::make_pair(path, r));
				return resourceMap[path];
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			logger->Log(Logger::Logger::WARNING, "Tried to load a resource without a registered factory!");
			return NULL;
		}
	}
	else
	{
		return resourceMap[path];
	}
	return NULL;
};

bool Resource::ResourceManager::RegisterFactory(char* extension, ResourceFactory* factory) 
{
	if (factoryForExtension.find(extension) == factoryForExtension.end())
	{
		factoryForExtension.insert(std::make_pair(extension, factory));
		return true;
	}
	else 
	{
		logger->Log(Logger::Logger::DEBUG, "You tried to register a factory for an extension twice!");
		return false;
	}
}

/*Resource::Mesh* Resource::ResourceManager::LoadMesh(const std::string& fileName, const std::string& extension)
{
	if (meshLoaders.find(extension) != meshLoaders.end()){
		meshes[fileName] = meshLoaders[extension]->Load(fileName, this);
		return &meshes[fileName];
	}
	else {
		logger->Log(Logger::Logger::ERR, "MeshLoader not found for extension:" + extension);
		return NULL;
	}
}*/

/*void Resource::ResourceManager::AddMeshLoader(BaseMeshLoader* newMeshLoader)
{
	meshLoaders[newMeshLoader->GetExtension()] = newMeshLoader;
}*/

/*std::map<std::string, Resource::Material>* Resource::ResourceManager::loadMaterials(std::string file)
{
	std::map<std::string, Material> newMaterials;
	if (Logger::StringHelper::EndsWith(file, ".mtl"))
	{
		newMaterials = MtlLoader::Load(file);
		materials[file] = newMaterials;
	}
	return &materials[file];
}*/

