
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
		int* GetSkyboxIndices();
		Material* GetMaterial();
		void SetMaterial(Material*);
		void Draw(Renderer* renderer, Vector3* position);

	private:
		Vertex* aSkyboxVertices;
		int* aSkyboxIndices;
		Material* material;
		int amountOfVertices;
		int amountOfIndices;
		VertexBufferWrapper* v_buffer;
		IndexBufferWrapper* i_buffer;
	};

}


#endif