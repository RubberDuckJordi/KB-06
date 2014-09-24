#include "XModel.h"

Resource::XModel::XModel()
{
	materials = NULL;
	mesh = NULL;
	textures = NULL;
}

Resource::XModel::~XModel()
{
	delete mesh;
	delete[] materials;
}

Renderer::MeshWrapper* Resource::XModel::GetMesh()
{
	return mesh;
}

void Resource::XModel::SetMesh(Renderer::MeshWrapper* p_mesh)
{
	mesh = p_mesh;
}

int Resource::XModel::GetTextureCount()
{
	return materialCount;
}

Renderer::TextureWrapper* Resource::XModel::GetTexture(int p_textureIndex)
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

void Resource::XModel::GetTextures(Renderer::TextureWrapper*& p_textures, int& p_textureCount)
{
	p_textures = textures;
	p_textureCount = textureCount;
}

void Resource::XModel::SetTextures(Renderer::TextureWrapper* p_textures, int p_textureCount)
{
	textures = p_textures;
	textureCount = p_textureCount;
}

int Resource::XModel::GetMaterialCount()
{
	return materialCount;
}

void Resource::XModel::GetMaterials(Renderer::MaterialWrapper*& p_materials, int& p_materialCount)
{
	p_materials = materials;
	p_materialCount = materialCount;
}

void Resource::XModel::SetMaterials(Renderer::MaterialWrapper* p_materials, int p_materialCount)
{
	materials = p_materials;
	materialCount = p_materialCount;
}