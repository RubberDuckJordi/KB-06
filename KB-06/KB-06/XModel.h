#ifndef __RESOURCE_XMODEL_H__
#define __RESOURCE_XMODEL_H__

#include "MeshWrapper.h"
#include "TextureWrapper.h"
#include "MaterialWrapper.h"

namespace Resource
{
	class XModel
	{
	public:
		XModel();
		~XModel();
		Renderer::MeshWrapper* GetMesh();
		void SetMesh(Renderer::MeshWrapper* p_mesh);
		int GetTextureCount();
		void GetTextures(Renderer::TextureWrapper*& p_textures, int& p_textureCount);
		void SetTextures(Renderer::TextureWrapper* p_textures, int p_textureCount);
		Renderer::TextureWrapper* GetTexture(int p_textureIndex);
		int GetMaterialCount();
		void GetMaterials(Renderer::MaterialWrapper*& p_material, int& p_materialCount);
		void SetMaterials(Renderer::MaterialWrapper* p_material, int p_materialCount);

	private:
		Renderer::MeshWrapper* mesh;
		int materialCount;
		Renderer::MaterialWrapper* materials;
		int textureCount;
		Renderer::TextureWrapper* textures;
	};
}
#endif