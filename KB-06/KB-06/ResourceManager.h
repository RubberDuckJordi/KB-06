#ifndef _RESOURCE_RESOURCEMANAGER_H_
#define _RESOURCE_RESOURCEMANAGER_H_

#include "LoggerPool.h"
#include "Mesh.h"
#include "Material.h"
#include "Resource.h"
#include "ResourceFactory.h"

#include <string>

namespace Resource
{
	class BaseMeshLoader;
	class Resource;
	class ResourceFactory;

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		/*!
		Returns the resource of specified path, will try to load the resource if it was not loaded yet.

		@return Resource*: A pointer to the resource, NULL if there was an error loading the resource or if there was no factory registered for it.
		@param path: The path to the resource file on the disk.
		*/
		Resource* GetResource(char* path, char* extension);

		/*!
		Registers the specified factory to be used for loading a resource of the specified extension.

		@return bool: True when the factory is newly registered, false otherwise.
		@param extension: The file extension for which the factory will be used, without the period.
		@param factory: The factory to use for the extension.
		*/
		bool RegisterFactory(char* extension, ResourceFactory* factory);


		//Mesh* LoadMesh(const std::string& fileName, const std::string& extension);
		//void AddMeshLoader(BaseMeshLoader*);
		//std::map<std::string, Material>* loadMaterials(std::string file);

	private:
		//std::map<std::string, Mesh> meshes;
		//std::map<std::string, BaseMeshLoader*> meshLoaders;
		//std::map<std::string, std::map<std::string, Material>> materials;
		Logger::Logger* logger;
		std::map<char*, Resource*> resourceMap;
		std::map<char*, ResourceFactory*> factoryForExtension;
	};
}
#endif
