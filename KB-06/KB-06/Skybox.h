#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "TextureWrapper.h"
#include "Renderer.h"
#include "DirectXRenderer.h" // HACKING VOLGENS ROBERT
#include "CustomD3DVertex.h"



namespace pengine
{
	class Skybox
	{
	public:
		Skybox(Renderer* renderer, std::string textureString);
		~Skybox();
		D3DCustomVertex* GetSkyboxVertices();
		int* GetSkyboxIndices();
		TextureWrapper* GetTexture();

		void Draw(Renderer* renderer, Vertex* position);


	private:
		D3DCustomVertex* aSkyboxVertices;
		int* aSkyboxIndices;
		TextureWrapper* texture;
		int amountOfVertices;
		int amountOfIndices;
		LPDIRECT3DVERTEXBUFFER9 v_buffer;
		LPDIRECT3DINDEXBUFFER9 i_buffer;
		LPD3DXMESH d3dMesh;
	};

}


#endif