
#ifndef _PENGINE_SKYBOX_H_
#define _PENGINE_SKYBOX_H_

#include "TextureWrapper.h"
#include "Renderer.h"
#include "DirectXRenderer.h" // HACKING VOLGENS ROBERT
#include "Vertex.h"
#include "Vector3.h"


namespace pengine
{
	class Skybox
	{
	public:
		Skybox();
		~Skybox();
		Vertex* GetSkyboxVertices();
		unsigned int* GetSkyboxIndices();
		Material* GetMaterial();
		void SetMaterial(Material*);
		void CacheToRenderer(Renderer* renderer);
		void Render(Renderer* renderer, Vector3* position);
	private:
		Vertex* aSkyboxVertices;
		unsigned int* aSkyboxIndices;
		Material* material;
		unsigned int amountOfVertices;
		unsigned int amountOfIndices;
		VertexBufferWrapper* v_buffer;
		IndexBufferWrapper* i_buffer;
	};

}


#endif