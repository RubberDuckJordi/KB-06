#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_
#include <hash_map>
#include "Mesh.h"
#include "Material.h"
#include <string>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	void load(std::string file);
private:
	std::hash_map<std::string, Mesh> meshes;
	std::hash_map<std::string, Material> materials;
};
#endif 
