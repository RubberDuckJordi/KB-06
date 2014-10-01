#include "XModelLoader.h"

namespace pengine
{
	XModelLoader::XModelLoader()
	{
		logger = LoggerPool::GetInstance().GetLogger();
	}

	XModelLoader::~XModelLoader()
	{
		LoggerPool::GetInstance().ReturnLogger(logger);
	}

	void XModelLoader::LoadXModel(std::string filename, DirectXRenderer* renderer, XModel* xmodel)
	{
		logger->Log(Logger::DEBUG, "XModelLoader: Loading XModel");

		LPD3DXBUFFER mtrlBuffer = NULL;
		DWORD mtrlCount = NULL;
		LPD3DXMESH* mesh = new LPD3DXMESH();
		LPDIRECT3DDEVICE9* d = renderer->GetDevice();

		HRESULT result = D3DXLoadMeshFromXA(filename.c_str(),
			D3DXMESH_SYSTEMMEM,
			*d,
			NULL,
			&mtrlBuffer,
			NULL,
			&mtrlCount,
			mesh);

		if (mtrlBuffer != NULL)
		{
			D3DXMATERIAL* d3dxMaterial = static_cast<D3DXMATERIAL*>(mtrlBuffer->GetBufferPointer());
			D3DMATERIAL9* materials = new D3DMATERIAL9[mtrlCount];
			LPDIRECT3DTEXTURE9* textures = new LPDIRECT3DTEXTURE9[mtrlCount];

			for (int i = 0; i < static_cast<int>(mtrlCount); i++)
			{
				materials[i] = d3dxMaterial[i].MatD3D;
				materials[i].Ambient = materials[i].Diffuse;

				if (d3dxMaterial[i].pTextureFilename != NULL && d3dxMaterial[i].pTextureFilename != "")
				{
					int pos = filename.rfind("/");
					std::string filepathNew = filename.substr(0, pos + 1);
					filepathNew.append(d3dxMaterial[i].pTextureFilename);

					LPDIRECT3DTEXTURE9* texture = new LPDIRECT3DTEXTURE9();
					HRESULT result = D3DXCreateTextureFromFileA(*renderer->GetDevice(), filepathNew.c_str(), texture);
					textures[i] = *texture;
				}
				else
				{
					textures[i] = NULL;
				}
			}

			MeshWrapper* meshWrapper = new MeshWrapper(mesh);
			MaterialWrapper* materialWrapper = new MaterialWrapper(materials);
			TextureWrapper* textureWrapper = new TextureWrapper(textures);

			xmodel->SetMesh(meshWrapper);
			xmodel->SetMaterials(materialWrapper, mtrlCount);
			xmodel->SetTextures(textureWrapper, mtrlCount);

			mtrlBuffer->Release();
		}
		else
		{
			logger->Log(Logger::ERR, "Unable to load X file");
		}
	}
}