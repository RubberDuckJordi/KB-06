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
		logger->Log(Logger::INFO, "ResourceManager destructed");
	}

	BinaryData* ResourceManager::LoadBinaryFile(const std::string& fileName)
	{
		logger->Log(Logger::DEBUG, "Going to load texture file: " + fileName);

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

	Shader* ResourceManager::LoadShader(std::string VertexShaderFilename, std::string PixelShaderFilename, std::string filename, Renderer* renderer)
	{
		Shader* shader = new Shader();
		HRESULT hr;

		if (!VertexShaderFilename.empty())
		{
			// Create vertex shader
			LPD3DXBUFFER pCode;

			D3DVERTEXELEMENT9 decl[] =
			{
				{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
				{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
				D3DDECL_END()
			};

			LPDIRECT3DVERTEXDECLARATION9 declaration = shader->GetVertexDeclaration();

			((*((DirectXRenderer*)renderer)->GetDevice())->CreateVertexDeclaration(decl, &declaration));


			shader->SetVertexDeclaration(declaration);

			// Find the vertex shader file
			//DXUTFindDXSDKMediaFileCch(strPath, 512, L"HLSLwithoutEffects.vsh");



			DWORD dwShaderFlags = 0;
			LPCWSTR strPath;
			std::wstring strPathNew = L"resources/HLSLwithoutEffects.fx";
			strPath = strPathNew.c_str();

			LPD3DXCONSTANTTABLE constantTable = shader->GetVertexShaderConstantTable();

			// Assemble the vertex shader from the file
			D3DXCompileShaderFromFile(strPath, NULL, NULL, "Ripple",
				"vs_2_0", dwShaderFlags, &pCode,
				NULL, &constantTable);

			shader->SetVertexShaderConstantTable(constantTable);

			LPDIRECT3DVERTEXSHADER9 vertexShader = shader->GetVertexShader();

			// Create the vertex shader
			hr = (*((DirectXRenderer*)renderer)->GetDevice())->CreateVertexShader((DWORD*)pCode->GetBufferPointer(),
				&vertexShader);
			pCode->Release();
			if (FAILED(hr))
			{
				//return DXTRACE_ERR(TEXT("CreateVertexShader"), hr);
			}
			shader->SetVertexShader(vertexShader);
		}

		if (!PixelShaderFilename.empty())
		{
			LPD3DXBUFFER pCode;

			DWORD dwShaderFlags = 0;

			LPCWSTR strPath;

			std::wstring strPathNew = L"resources/ColorPixelShader.fx";

			strPath = strPathNew.c_str();

			LPD3DXCONSTANTTABLE constantTable = shader->GetPixelShaderConstantTable();

			// Assemble the vertex shader from the file
			D3DXCompileShaderFromFile(strPath, NULL, NULL, "main",
				"ps_2_0", dwShaderFlags, &pCode,
				NULL, &constantTable);

			shader->SetPixelShaderConstantTable(constantTable);

			LPDIRECT3DPIXELSHADER9 pixelShader = shader->GetPixelShader();

			(*((DirectXRenderer*)renderer)->GetDevice())->CreatePixelShader((DWORD*)pCode->GetBufferPointer(), &pixelShader);

			shader->SetPixelShader(pixelShader);
		}

		shaders[filename] = *shader;
		return shader;
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
			for (std::list<pengine::Mesh*>::iterator i = model->_Meshes.begin(); i != model->_Meshes.end(); ++i)
			{
				for (std::list<pengine::Material*>::iterator j = (*i)->_Materials.begin(); j != (*i)->_Materials.end(); ++j)
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

}