#ifndef _RESOURCE_RESOURCEMANAGER_H_
#define _RESOURCE_RESOURCEMANAGER_H_
#include <map>
#include "Mesh.h"
#include "Material.h"

#include <string>

namespace Resource
{
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();
		Mesh* ResourceManager::loadMesh(std::string);
		std::map<std::string, Material>* ResourceManager::loadMaterials(std::string file);
	private:
		std::map<std::string, Mesh> meshes;
		std::map<std::string, std::map<std::string, Material>> materials;
	};
}

#endif 
