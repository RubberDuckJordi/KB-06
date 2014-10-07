#include "stdafx.h"
#include "ResourceManager.h"
#include "StringHelper.h"

namespace pengine
{
	ResourceManager::ResourceManager()
	{
		logger = LoggerPool::GetInstance().GetLogger();
	}

	ResourceManager::~ResourceManager()
	{
		LoggerPool::GetInstance().ReturnLogger(logger);
	}

	/*Mesh* ResourceManager::LoadMesh(const std::string& fileName, const std::string& extension)
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
	}*/

	/*void ResourceManager::AddMeshLoader(BaseMeshLoader* newMeshLoader)
	{
	meshLoaders[newMeshLoader->GetExtension()] = newMeshLoader;
	}*/

	/*void ResourceManager::AddMaterialLoader(BaseMaterialLoader* newMaterialLoader)
	{
	materialLoaders[newMaterialLoader->GetExtension()] = newMaterialLoader;
	}*/

	/*Material* ResourceManager::LoadMaterial(const std::string& fileName, const std::string& extension)
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
	}*/

	BinaryData* ResourceManager::LoadBinaryFile(const std::string& fileName)
	{
		//logger->LogAll(Logger::DEBUG, "Going to load texture file: " + fileName);

		std::ifstream file(fileName, std::ios::binary);
		file.seekg(0, std::ios::end);
		std::streamsize size = file.tellg();
		file.clear();
		file.seekg(0, std::ios::beg);

		BinaryData* texture = new BinaryData();
		texture->rawData = new char[(unsigned int)size];
		texture->size = (unsigned int)size;
		texture->fileName = fileName;
		if (file.read(texture->rawData, size))
		{
			textures[fileName] = *texture;
			return texture;
		}
		return texture;
	}

	Ground* ResourceManager::LoadGround(std::string filename, std::string textureFilename)
	{
		Ground* ground = NULL;

		for (std::map<std::string, Ground>::iterator i = grounds.begin(); i != grounds.end(); ++i) 
		{
			if (i->first == filename)
			{
				ground = &i->second;
			}
		}

		if (ground == NULL)
		{
			ground = heightmapLoader.LoadHeightmap(filename);
			Material* material = new Material();
			material->texture = LoadBinaryFile(textureFilename);
			ground->SetMaterial(material);

			grounds[filename] = *ground;
		}
		

		return ground;
	}
}