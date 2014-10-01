#include "XModel.h"

namespace pengine
{
	XModel::XModel()
	{
		materials = NULL;
		mesh = NULL;
		textures = NULL;
	}

	XModel::~XModel()
	{
		delete mesh;
		delete[] materials;
	}

	MeshWrapper* XModel::GetMesh()
	{
		return mesh;
	}

	void XModel::SetMesh(MeshWrapper* p_mesh)
	{
		mesh = p_mesh;
	}

	int XModel::GetTextureCount()
	{
		return materialCount;
	}

	TextureWrapper* XModel::GetTexture(int p_textureIndex)
	{
		if (p_textureIndex < 0 || p_textureIndex >= textureCount)
		{
			return NULL;
		}
		else
		{
			return &textures[p_textureIndex];
		}
	}

	void XModel::GetTextures(TextureWrapper*& p_textures, int& p_textureCount)
	{
		p_textures = textures;
		p_textureCount = textureCount;
	}

	void XModel::SetTextures(TextureWrapper* p_textures, int p_textureCount)
	{
		textures = p_textures;
		textureCount = p_textureCount;
	}

	int XModel::GetMaterialCount()
	{
		return materialCount;
	}

	void XModel::GetMaterials(MaterialWrapper*& p_materials, int& p_materialCount)
	{
		p_materials = materials;
		p_materialCount = materialCount;
	}

	void XModel::SetMaterials(MaterialWrapper* p_materials, int p_materialCount)
	{
		materials = p_materials;
		materialCount = p_materialCount;
	}
}