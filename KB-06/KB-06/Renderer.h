#ifndef _RENDERER_RENDERER_H_
#define _RENDERER_RENDERER_H_

#include "PengineDefinitions.h"
#include "MatrixWrapper.h"
#include "MaterialWrapper.h"
#include "TextureWrapper.h"
#include "MeshWrapper.h"
#include "VertexBufferWrapper.h"
#include "IndexBufferWrapper.h"
#include "Mesh.h"
#include "LoggerPool.h"
#include "RGBAColor.h"
#include <d3dx9.h>
#include "RenderMatrix.h"

namespace Renderer
{
	class Renderer
	{
	public:
		Renderer();
		virtual ~Renderer() = 0;

		virtual void InitD3D(HWND hWnd) = 0;
		virtual void SetRenderState() = 0;

		virtual void SetActiveCamera(CameraData camera) = 0;
		virtual void SetProjectionMatrix(MatrixWrapper* ProjectionMatrix) = 0;
		virtual void SetProjectionMatrix(float FOV, float farClippingPlane) = 0;

		virtual void BeginScene() = 0;
		virtual void ClearScene(PENGINEDWORD* count, PENGINEDWORD* flags, PENGINECOLOR* color, float z, PENGINEDWORD* stencil) = 0;
		virtual void ClearScene(unsigned long count, unsigned long flags, Resource::RGBAColor color, float z, unsigned long stencil) = 0;
		virtual void PresentScene(HWND hWnd) = 0;
		virtual void EndScene() = 0;

		virtual void CreateVertexBuffer(int heightmapvertex, PENGINEDWORD* usage, PENGINEDWORD* fvf, PENGINEPOOL* pool, VertexBufferWrapper* vertexbuffer, HANDLE handle) = 0;
		virtual void CreateIndexBuffer(int length, PENGINEDWORD* usage, PENGINEFORMAT* format, PENGINEPOOL* pool, IndexBufferWrapper* Indexbuffer, HANDLE* handle) = 0;

		virtual void SetMaterial(MaterialWrapper* wrapper) = 0;
		virtual void SetTexture(TextureWrapper* wrapper) = 0;
		virtual void SetFvF(DWORD* fvf) = 0;

		virtual void DrawPrimitive(Resource::Mesh mesh) = 0;
		virtual void DrawSubset(MeshWrapper* wrapper, int subset) = 0;

		virtual void SetStreamSource() = 0; //??
		virtual void SetIndices() = 0; //??

		virtual void Draw(Resource::Mesh* mesh) = 0;
		virtual void SetActiveMatrix(PEngineMatrix* matrix) = 0;

		virtual void SetLights() = 0;
	protected:
		Logger::Logger* logger;
	};
}


#endif