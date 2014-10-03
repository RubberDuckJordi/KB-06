#ifndef __PENGINE_XMODEL_H__
#define __PENGINE_XMODEL_H__

#include "MeshWrapper.h"
#include "TextureWrapper.h"
#include "MaterialWrapper.h"

namespace pengine
{
	class XModel
	{
	public:
		XModel();
		~XModel();
		MeshWrapper* GetMesh();
		void SetMesh(MeshWrapper* p_mesh);
		int GetTextureCount();
		void GetTextures(TextureWrapper*& p_textures, int& p_textureCount);
		void SetTextures(TextureWrapper* p_textures, int p_textureCount);
		TextureWrapper* GetTexture(int p_textureIndex);
		int GetMaterialCount();
		void GetMaterials(MaterialWrapper*& p_material, int& p_materialCount);
		void SetMaterials(MaterialWrapper* p_material, int p_materialCount);

	private:
		MeshWrapper* mesh;
		int materialCount;
		MaterialWrapper* materials;
		int textureCount;
		TextureWrapper* textures;
	};
}
#endif