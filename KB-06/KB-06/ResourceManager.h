#ifndef _PENGINE_RESOURCEMANAGER_H_
#define _PENGINE_RESOURCEMANAGER_H_

#include "LoggerPool.h"
#include "BinaryData.h"
#include "Sound.h"
#include "Material.h"
#include "Ground.h"
#include "HeightmapLoader.h"

#include <vector>
#include <string>

namespace pengine
{
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		//Mesh* LoadMesh(const std::string& fileName, const std::string& extension);
		Material* LoadMaterial(const std::string& fileName, const std::string& extension);
		BinaryData* LoadBinaryFile(const std::string& fileName);
		Ground* LoadGround(std::string filename, std::string textureFilename);

		//Mesh* LoadSound(const std::string& fileName, const std::string& extension);

		//void AddMeshLoader(BaseMeshLoader*);
		//void AddMaterialLoader(BaseMaterialLoader*);
		//void AddSoundLoader(BaseMeshLoader*);

		//std::map<std::string, Material>* LoadMaterials(std::string file);
	private:
		Logger* logger;

		HeightmapLoader heightmapLoader;
		//std::map<std::string, Mesh> meshes;
		std::map<std::string, Material> materials;
		std::map<std::string, BinaryData> textures;
		std::map<std::string, Sound> sounds;
		std::map<std::string, Ground> grounds;

		//std::map<std::string, BaseMeshLoader*> meshLoaders;
		//std::map<std::string, BaseMaterialLoader*> materialLoaders;
	};
}
#endif
