
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

		//Mesh* LoadMesh(const std::string& fileName, const std::string& extension);
		Material* LoadMaterial(const std::string& fileName, const std::string& extension);
		BinaryData* LoadBinaryFile(const std::string& fileName);
		Ground* LoadGround(std::string filename, std::string textureFilename, float cellSize);
		Shader* LoadShader(std::string VertexShaderFilename, std::string PixelShaderFilename, std::string filename, Renderer* renderer);
		std::vector<std::string>* LoadSceneFile(std::string* path);
		Object3D* LoadXFile(std::string* fileName);
		void CacheToRenderer(Renderer* renderer);

		//Mesh* LoadSound(const std::string& fileName, const std::string& extension);

		//void AddMeshLoader(BaseMeshLoader*);
		//void AddMaterialLoader(BaseMaterialLoader*);
		//void AddSoundLoader(BaseMeshLoader*);

		//std::map<std::string, Material>* LoadMaterials(std::string file);
	private:
		Logger* logger;

		HeightmapLoader heightmapLoader;
		SceneLoader* sceneLoader;
		SuperXLoader* superXLoader;
		//std::map<std::string, Mesh> meshes;
		std::map<std::string, Material> materials;
		std::map<std::string, BinaryData*> textures;
		std::map<std::string, Ground> grounds;
		std::map<std::string, Shader> shaders;
		std::map<std::string, Model3D*> models;

		//std::map<std::string, BaseMeshLoader*> meshLoaders;
		//std::map<std::string, BaseMaterialLoader*> materialLoaders;
	};
}
#endif
