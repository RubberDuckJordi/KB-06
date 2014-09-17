#ifndef _RENDERER_RENDERER_H_
#define _RENDERER_RENDERER_H_

#include "PengineDefinitions.h"
#include "MatrixWrapper.cpp"
#include "MaterialWrapper.cpp"
#include "TextureWrapper.cpp"
#include "DWORDWrapper.cpp"
#include "MeshWrapper.cpp"
#include "PoolWrapper.cpp"
#include "VertexBufferWrapper.cpp"
#include "IndexBufferWrapper.cpp"
#include "FormatWrapper.cpp"
#include "Mesh.h"
#include "LoggerPool.h"
#include "RGBAColor.h"
#include <d3dx9.h>

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
		virtual void SetViewMatrix(float posX, float posY, float posZ, float roatationX, float roatationY, float roatationZ) = 0;
		virtual void SetProjectionMatrix(MatrixWrapper* ProjectionMatrix) = 0;
		virtual void SetProjectionMatrix(float FOV, float farClippingPlane) = 0;

		virtual void BeginScene() = 0;
		virtual void ClearScene(DWORDWrapper* count, DWORDWrapper* flags, ColorWrapper* color, float z, DWORDWrapper* stencil) = 0;
		virtual void ClearScene(unsigned long count, unsigned long flags, Resource::RGBAColor color, float z, unsigned long stencil) = 0;
		virtual void PresentScene(HWND hWnd) = 0;
		virtual void EndScene() = 0;

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
		virtual void SetWorldMatrix(D3DXMATRIXA16* matrix, D3DXMATRIXA16* offset, boolean staticEntity) = 0;
	protected:
		Logger::Logger* logger;
	};
}


#endif