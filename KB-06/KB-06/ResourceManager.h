#ifndef _RESOURCE_RESOURCEMANAGER_H_
#define _RESOURCE_RESOURCEMANAGER_H_

#include "LoggerPool.h"
#include "Mesh.h"
#include "Material.h"
#include "BaseMeshLoader.h"

#include <string>

namespace Resource
{
	class BaseMeshLoader;

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		Mesh* LoadMesh(const std::string& fileName, const std::string& extension);
		void AddMeshLoader(BaseMeshLoader*);
		std::map<std::string, Material>* loadMaterials(std::string file);

	private:
		std::map<std::string, Mesh> meshes;
		std::map<std::string, BaseMeshLoader*> meshLoaders;
		std::map<std::string, std::map<std::string, Material>> materials;
		Logger::Logger* logger;
	};
}
#endif
