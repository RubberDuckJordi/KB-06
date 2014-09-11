#ifndef _RENDERER_RENDERER_H_
#define _RENDERER_RENDERER_H_

#include "MatrixWrapper.cpp"
#include "MaterialWrapper.cpp"
#include "TextureWrapper.cpp"
#include "DWORDWrapper.cpp"
#include "MeshWrapper.cpp"
#include "PoolWrapper.cpp"
#include "VertexBufferWrapper.cpp"
#include "IndexBufferWrapper.cpp"
#include "FormatWrapper.cpp"
#include "ColorWrapper.cpp"
#include "Mesh.h"

namespace Renderer
{
	class Renderer
	{
	public:
		Renderer();
		virtual ~Renderer() = 0;

		virtual void InitD3D(HWND hWnd) = 0;
		virtual void SetRenderState() = 0;

		virtual void SetWorldMatrix(MatrixWrapper* WorldMatrix) = 0;
		virtual void SetViewMatrix(MatrixWrapper* ViewMatrix) = 0;
		virtual void SetProjectionMatrix(MatrixWrapper* ProjectionMatrix) = 0;

		virtual void BeginScene() = 0;
		virtual void ClearScene(DWORDWrapper* count, DWORDWrapper* flags, ColorWrapper* color, float z, DWORDWrapper* stencil) = 0;
		virtual void PresentScene(HWND hWnd) = 0;
		virtual void StopScene() = 0;

		virtual void CreateVertexBuffer(int heightmapvertex, DWORDWrapper* usage, DWORDWrapper* fvf, PoolWrapper* pool, VertexBufferWrapper* vertexbuffer, HANDLE handle) = 0;
		virtual void CreateIndexBuffer(int length, DWORDWrapper* usage, FormatWrapper* format, PoolWrapper* pool, IndexBufferWrapper* Indexbuffer, HANDLE* handle) = 0;

		virtual void SetMaterial(MaterialWrapper* wrapper) = 0;
		virtual void SetTexture(TextureWrapper* wrapper) = 0;
		virtual void SetFvF(DWORDWrapper* fvf) = 0;
		virtual void SetTransform(int type, MatrixWrapper* wrapper) = 0;

		virtual void DrawPrimitive(Resource::Mesh mesh) = 0;
		virtual void DrawSubset(MeshWrapper* wrapper, int subset) = 0;

		virtual void SetStreamSource() = 0; //??
		virtual void SetIndices() = 0; //??

		virtual void Draw(Resource::Mesh* mesh) = 0;
	};
}


#endif