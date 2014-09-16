#ifndef _RESOURCE_RESOURCEMANAGER_H_
#define _RESOURCE_RESOURCEMANAGER_H_

#include "LoggerPool.h"
#include "Mesh.h"
#include "Texture.h"
#include "Sound.h"
#include "Material.h"
#include "BaseMeshFactory.h"
#include "BaseMaterialFactory.h"

#include <string>

namespace Resource
{
	class BaseMeshFactory;

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		Mesh* LoadMesh(const std::string& fileName, const std::string& extension);
		Mesh* LoadMaterial(const std::string& fileName, const std::string& extension);
		Mesh* LoadTexture(const std::string& fileName, const std::string& extension);
		Mesh* LoadSound(const std::string& fileName, const std::string& extension);

		void AddMeshFactory(BaseMeshFactory*);
		void AddMaterialFactory(BaseMaterialFactory*);
		void AddTexureFactory(BaseMeshFactory*);
		void AddSoundFactory(BaseMeshFactory*);

		std::map<std::string, Material>* loadMaterials(std::string file);
	private:
		Logger::Logger* logger;

		std::map<std::string, Mesh> meshes;
		std::map<std::string, Material> materials;
		std::map<std::string, Texture> textures;
		std::map<std::string, Sound> sounds;

		std::map<std::string, BaseMeshFactory*> meshFactories;
		std::map<std::string, BaseMaterialFactory*> materialFactories;
	};
}
#endif
