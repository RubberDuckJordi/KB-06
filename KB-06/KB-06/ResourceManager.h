
#ifndef _PENGINE_RESOURCEMANAGER_H_
#define _PENGINE_RESOURCEMANAGER_H_

#include "LoggerPool.h"
#include "BinaryData.h"
#include "Material.h"
#include "Ground.h"
#include "HeightmapLoader.h"
#include "SceneLoader.h"
#include "SuperXLoader.h"
#include "Shader.h"
#include "Object3D.h"

#include <vector>
#include <string>

namespace pengine
{
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		BinaryData* LoadBinaryFile(const std::string& fileName);
		std::string* LoadShaderFile(const std::string& fileName);
		Ground* LoadGround(std::string filename, std::string textureFilename, float cellSize);
		std::vector<std::string>* LoadSceneFile(std::string* path);
		Object3D* LoadXFile(std::string* fileName);
		void CacheToRenderer(Renderer* renderer);

	private:
		Logger* logger;

		HeightmapLoader heightmapLoader;
		SceneLoader* sceneLoader;
		SuperXLoader* superXLoader;
		//std::map<std::string, Mesh> meshes;
		std::map<std::string, Material> materials;
		std::map<std::string, BinaryData*> textures;
		std::map<std::string, Ground> grounds;
		std::map<std::string, std::string*> shaders;
		std::map<std::string, Model3D*> models;

		//std::map<std::string, BaseMeshLoader*> meshLoaders;
		//std::map<std::string, BaseMaterialLoader*> materialLoaders;
	};
}
#endif
