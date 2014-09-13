#ifndef _RENDERER_DIRECTXRENDERER_H_
#define _RENDERER_DIRECTXRENDERER_H_

#include <d3dx9.h>
#include "Renderer.h"

namespace Renderer
{
	class DirectXRenderer : public Renderer
	{
	public:
		DirectXRenderer();
		~DirectXRenderer();

		void InitD3D(HWND hWnd);
		void SetRenderState();

		void SetWorldMatrix(MatrixWrapper* WorldMatrix);
		void SetViewMatrix(MatrixWrapper* ViewMatrix);
		void SetProjectionMatrix(MatrixWrapper* ProjectionMatrix);

		void BeginScene();
		void ClearScene(DWORDWrapper* count, DWORDWrapper* flags, ColorWrapper* color, float z, DWORDWrapper* stencil);
		void PresentScene(HWND hWnd);
		void StopScene();

		void CreateVertexBuffer(int heightmapvertex, DWORDWrapper* usage, DWORDWrapper* fvf, PoolWrapper* pool, VertexBufferWrapper* vertexbuffer, HANDLE handle);
		void CreateIndexBuffer(int length, DWORDWrapper* usage, FormatWrapper* format, PoolWrapper* pool, IndexBufferWrapper* Indexbuffer, HANDLE* handle);

		void SetMaterial(MaterialWrapper* wrapper);
		void SetTexture(TextureWrapper* wrapper);
		void SetFvF(DWORDWrapper* fvf);
		void SetTransform(int type, MatrixWrapper* wrapper);

		void DrawPrimitive(Resource::Mesh mesh);
		void DrawSubset(MeshWrapper* wrapper, int subset);

		void SetStreamSource(); //??
		void SetIndices(); //??

		LPDIRECT3DDEVICE9* GetDevice();
		void Draw(Resource::MeshResource* mesh);
	private:
		LPDIRECT3D9 g_pD3D;
		LPDIRECT3DDEVICE9 g_pd3dDevice;
		std::map<Resource::MeshResource*, LPD3DXMESH> meshCache;
	};
}


#endif