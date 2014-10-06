
#ifndef _PENGINE_SKYBOX_H_
#define _PENGINE_SKYBOX_H_

#include "TextureWrapper.h"
#include "Renderer.h"
#include "DirectXRenderer.h" // HACKING VOLGENS ROBERT
#include "CustomD3DVertex.h"
#include "Vertex.h"


namespace pengine
{
	class Skybox
	{
	public:
		Skybox();
		~Skybox();
		D3DCustomVertex* GetSkyboxVertices();
		int* GetSkyboxIndices();
		Material* GetMaterial();
		void SetMaterial(Material*);
		void Draw(Renderer* renderer, Vertex* position);

	private:
		D3DCustomVertex* aSkyboxVertices;
		int* aSkyboxIndices;
		Material* material;
		int amountOfVertices;
		int amountOfIndices;
		VertexBufferWrapper* v_buffer;
		IndexBufferWrapper* i_buffer;
	};

}


#endif