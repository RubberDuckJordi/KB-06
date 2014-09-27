#include "stdafx.h"
#include "ResourceManager.h"
#include "StringHelper.h"
#include "ObjMeshLoader.h"
#include "MtlLoader.h"

pengine::ResourceManager::ResourceManager()
{
	logger = LoggerPool::GetInstance().GetLogger();
}

pengine::ResourceManager::~ResourceManager()
{
	LoggerPool::GetInstance().ReturnLogger(logger);
}

pengine::Mesh* pengine::ResourceManager::LoadMesh(const std::string& fileName, const std::string& extension)
{
	if (meshes.find(fileName) == meshes.end())
	{
		if (meshLoaders.find(extension) != meshLoaders.end())
		{
			Mesh loadedMesh = meshLoaders[extension]->Load(fileName);
			std::vector<std::string> elements;
			for (unsigned int i = 0; i < loadedMesh.defaultMaterialFiles.size(); ++i)
			{
				// load the material file by assuming everything afther the last '.' is the extension
				elements = StringHelper::split(loadedMesh.defaultMaterialFiles.at(i), '.');
				LoadMaterial(loadedMesh.defaultMaterialFiles.at(i), elements.back());
			}
			for (unsigned int i = 0; i < loadedMesh.subsets.size(); ++i)
			{
				Material material = materials.at(loadedMesh.subsets.at(i).defaultMaterial.name);
				loadedMesh.subsets.at(i).defaultMaterial = material;
			}
			meshes[fileName] = loadedMesh;
		}
		else
		{
			logger->Log(Logger::ERR, "MeshLoader not found for extension:" + extension);
			return NULL;
		}
	}
	return &meshes[fileName];
}

void pengine::ResourceManager::AddMeshLoader(pengine::BaseMeshLoader* newMeshLoader)
{
	meshLoaders[newMeshLoader->GetExtension()] = newMeshLoader;
}

void pengine::ResourceManager::AddMaterialLoader(pengine::BaseMaterialLoader* newMaterialLoader)
{
	materialLoaders[newMaterialLoader->GetExtension()] = newMaterialLoader;
}

pengine::Material* pengine::ResourceManager::LoadMaterial(const std::string& fileName, const std::string& extension)
{
	std::map<std::string, Material> newMaterials;
	if (extension == "mtl")
	{
		newMaterials = materialLoaders[extension]->Load(fileName);
		for (auto iterator = newMaterials.begin(); iterator != newMaterials.end(); iterator++)
		{
			if (iterator->second.defaultTexture.fileName != "")
			{
				iterator->second.defaultTexture = LoadBinaryFile(iterator->second.defaultTexture.fileName);
			}
		}
		materials.insert(newMaterials.begin(), newMaterials.end());
	}
	return NULL;
}

pengine::BinaryData pengine::ResourceManager::LoadBinaryFile(const std::string& fileName)
{
	std::ifstream file("resources/" + fileName, std::ios::binary);
	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.clear();
	file.seekg(0, std::ios::beg);

	BinaryData texture;
	texture.rawData = new char[(unsigned int)size];
	texture.size = (unsigned int)size;
	texture.fileName = fileName;
	if (file.read(texture.rawData, size))
	{
		textures[fileName] = texture;
		return texture;
	}
	return texture;
}