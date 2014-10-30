#include "ResourceManager.h"

namespace pengine
{
	ResourceManager::ResourceManager()
	{
		logger = LoggerPool::GetInstance().GetLogger();
		sceneLoader = NULL;
		superXLoader = NULL;
	}

	ResourceManager::~ResourceManager()
	{
		if (sceneLoader != NULL)
		{
			delete sceneLoader;
			sceneLoader = NULL;
		}
		if (superXLoader != NULL)
		{
			delete superXLoader;
			superXLoader = NULL;
		}
		logger->Log(Logger::INFO, "ResourceManager destructed");
	}

	BinaryData* ResourceManager::LoadBinaryFile(const std::string& fileName)
	{
		if (textures[fileName] == NULL)
		{
			logger->Log(Logger::DEBUG, "Going to load texture file: " + fileName);

			std::ifstream file(fileName, std::ios::binary);
			if (file)
			{
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
					textures[fileName] = texture;
				}
			}
			else
			{
				logger->Log(Logger::WARNING, "Failed to open file: " + fileName);
			}

		}
		return textures[fileName];
	}

	std::string* ResourceManager::LoadShaderFile(const std::string& fileName)
	{
		if (shaderps[fileName] == NULL)
		{
			std::ifstream in(fileName, std::ios::in | std::ios::binary);
			if (in)
			{
				std::string contents;
				std::string* stored = new std::string();
				in.seekg(0, std::ios::end);
				contents.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				//&contents[0] gives the C char* array
				in.read(&contents[0], contents.size());
				in.close();

				*stored = contents;
				shaderps[fileName] = stored;
			}
		}

		logger->Log(Logger::DEBUG, "Shader string: " + *shaderps[fileName]);
		return shaderps[fileName];
	}

	Ground* ResourceManager::LoadGround(std::string filename, std::string textureFilename, float cellSize)
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
			ground = heightmapLoader.LoadHeightmap(filename, cellSize);
			Material* material = new Material();
			material->texture = LoadBinaryFile(textureFilename);
			ground->SetMaterial(material);

			grounds[filename] = *ground;
		}
		return ground;
	}

	std::vector<std::string>* ResourceManager::LoadSceneFile(std::string* path)
	{
		if (sceneLoader == NULL)
		{
			sceneLoader = new SceneLoader();
		}

		std::vector<std::string>* textVector = sceneLoader->LoadFile(path);
		return textVector;
	}

	Object3D* ResourceManager::LoadXFile(std::string* filePath)
	{
		pengine::Model3D* model = new pengine::Model3D();

		if (models.find(*filePath) != models.end())
		{
			model = models.at(*filePath);
		}
		else
		{
			if (superXLoader == NULL)
			{
				superXLoader = new SuperXLoader();
			}

			superXLoader->Load(*filePath, model);

			size_t found = filePath->find_last_of("/");
			for (auto i = model->_Meshes.begin(); i != model->_Meshes.end(); ++i)
			{
				for (auto j = (*i)->_Materials.begin(); j != (*i)->_Materials.end(); ++j)
				{
					if ((*j)->texturePath != "")
					{
						(*j)->texture = LoadBinaryFile(filePath->substr(0, found) + "/" + (*j)->texturePath);
					}
				}
			}
			model->ConcatenateMeshes();

			models[*filePath] = model;
		}

		pengine::Object3D* object3D = new Object3D();
		object3D->SetupModel(model);
		object3D->showWarning = false;
		object3D->ClearSkinnedVertices();

		return object3D;
	}


	void ResourceManager::CacheToRenderer(Renderer* renderer)
	{
		for (auto it = textures.begin(); it != textures.end(); ++it)
		{
			renderer->CacheTexture((*it).second);
		}

		for (auto it = shaderps.begin(); it != shaderps.end(); ++it)
		{
			//compile shaderp on renderer
			renderer->CacheShaderp((*it).second);
		}
	}
}