#include "XModel.h"

pengine::XModel::XModel()
{
	materials = NULL;
	mesh = NULL;
	textures = NULL;
}

pengine::XModel::~XModel()
{
	delete mesh;
	delete[] materials;
}

pengine::MeshWrapper* pengine::XModel::GetMesh()
{
	return mesh;
}

void pengine::XModel::SetMesh(pengine::MeshWrapper* p_mesh)
{
	mesh = p_mesh;
}

int pengine::XModel::GetTextureCount()
{
	return materialCount;
}

pengine::TextureWrapper* pengine::XModel::GetTexture(int p_textureIndex)
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

void pengine::XModel::GetTextures(pengine::TextureWrapper*& p_textures, int& p_textureCount)
{
	p_textures = textures;
	p_textureCount = textureCount;
}

void pengine::XModel::SetTextures(pengine::TextureWrapper* p_textures, int p_textureCount)
{
	textures = p_textures;
	textureCount = p_textureCount;
}

int pengine::XModel::GetMaterialCount()
{
	return materialCount;
}

void pengine::XModel::GetMaterials(pengine::MaterialWrapper*& p_materials, int& p_materialCount)
{
	p_materials = materials;
	p_materialCount = materialCount;
}

void pengine::XModel::SetMaterials(pengine::MaterialWrapper* p_materials, int p_materialCount)
{
	materials = p_materials;
	materialCount = p_materialCount;
}