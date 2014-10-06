#ifndef _PENGINE_RENDERER_H_
#define _PENGINE_RENDERER_H_

#include "PengineDefinitions.h"
#include "MaterialWrapper.h"
#include "TextureWrapper.h"
#include "MeshWrapper.h"
#include "VertexBufferWrapper.h"
#include "IndexBufferWrapper.h"
#include "LoggerPool.h"
#include "RGBAColor.h"
#include "RenderMatrix.h"
#include "Material.h"
#include "CustomD3DVertex.h"

namespace pengine
{
	class Renderer
	{
	public:
		Renderer();
		virtual ~Renderer() = 0;

		virtual void InitD3D(HWND hWnd) = 0;
		virtual void SetDefaultRenderStates() = 0;

		virtual void CreateD2DFactory() = 0;
		virtual void CreateRenderTarget(HWND hWnd) = 0;
		virtual void CreateWICImagingFactory() = 0;
		virtual void CreateDecoder(std::string path) = 0;
		virtual void GetBitmapFrame() = 0;
		virtual void InitializeBMP() = 0;
		virtual void CreateFormatConverter() = 0;
		virtual void CreateBitmapFromWIC() = 0;
		virtual void D2DDraw() = 0;

		virtual void SetRenderState(PENGINERENDERSTATETYPE* state, PENGINEDWORD* dword) = 0;

		virtual void SetActiveCamera(CameraData camera) = 0;
		virtual void SetProjectionMatrix(PEngineMatrix* ProjectionMatrix) = 0;
		virtual void SetProjectionMatrix(float FOV, float farClippingPlane) = 0;

		virtual void BeginScene() = 0;
		virtual void ClearScene(PENGINEDWORD* count, PENGINEDWORD* flags, PENGINECOLOR* color, float z, PENGINEDWORD* stencil) = 0;
		virtual void ClearScene(unsigned long count, unsigned long flags, RGBAColor color, float z, unsigned long stencil) = 0;
		virtual void PresentScene(HWND hWnd) = 0;
		virtual void EndScene() = 0;

		virtual void CreateVertexBuffer(int heightmapvertex, PENGINEDWORD* usage, PENGINEDWORD* fvf, PENGINEPOOL* pool, VertexBufferWrapper* vertexbuffer, HANDLE handle) = 0;
		virtual void CreateIndexBuffer(int length, PENGINEDWORD* usage, PENGINEFORMAT* format, PENGINEPOOL* pool, IndexBufferWrapper* Indexbuffer, HANDLE* handle) = 0;

		virtual void SetMaterialWrapper(MaterialWrapper* wrapper) = 0;
		virtual void SetMaterial(Material* material) = 0;
		virtual void SetTexture(TextureWrapper* wrapper) = 0;
		virtual void SetFvF(DWORD* fvf) = 0;

		//virtual void DrawPrimitive(Mesh mesh) = 0;
		virtual void DrawSubset(MeshWrapper* wrapper, int subset) = 0;
		//virtual void Draw(Vertex* vertexBuffer, int amountOfIndices);

		virtual void SetStreamSource() = 0; //??
		virtual void SetIndices() = 0; //??

		//virtual void Draw(Mesh* mesh) = 0;
		virtual void SetActiveMatrix(PEngineMatrix* matrix) = 0;

		virtual void SetLights() = 0;

		virtual VertexBufferWrapper* CreateVertexBuffer(D3DCustomVertex*, int amountOfIndices, int fvf) = 0;
		virtual void DrawVertexBuffer(VertexBufferWrapper*, int amountOfIndices) = 0;

	protected:
		Logger* logger;
	};
}
#endif