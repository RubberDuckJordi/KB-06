#ifndef _PENGINE_DIRECTXRENDERER_H_
#define _PENGINE_DIRECTXRENDERER_H_

#include <d3dx9.h>
#include "Renderer.h"

namespace pengine
{
	class DirectXRenderer : public Renderer
	{
	public:
		DirectXRenderer();
		~DirectXRenderer();

		void InitD3D(HWND hWnd);
		void SetDefaultRenderStates();

		void SetRenderState(PENGINERENDERSTATETYPE* state, PENGINEDWORD* dword);

		void SetActiveCamera(CameraData camera);

		void SetProjectionMatrix(PEngineMatrix* ProjectionMatrix);
		void SetProjectionMatrix(float FOV, float farClippingPlane);

		void BeginScene();
		void ClearScene(PENGINEDWORD* count, PENGINEDWORD* flags, PENGINECOLOR* color, float z, PENGINEDWORD* stencil);
		void ClearScene(unsigned long count, unsigned long flags, RGBAColor color, float z, unsigned long stencil);
		void PresentScene(HWND hWnd);
		void EndScene();

		void CreateVertexBuffer(int heightmapvertex, PENGINEDWORD* usage, PENGINEDWORD* fvf, PENGINEPOOL* pool, VertexBufferWrapper* vertexbuffer, HANDLE handle);
		void CreateIndexBuffer(int length, PENGINEDWORD* usage, PENGINEFORMAT* format, PENGINEPOOL* pool, IndexBufferWrapper* Indexbuffer, HANDLE* handle);

		void SetMaterialWrapper(MaterialWrapper* wrapper);
		void SetMaterial(Material* material);
		void SetTexture(TextureWrapper* wrapper);
		void SetFvF(PENGINEDWORD* fvf);

		//void DrawPrimitive(Mesh mesh);
		void DrawSubset(MeshWrapper* wrapper, int subset);

		void SetStreamSource(); //??
		void SetIndices(); //??

		LPDIRECT3DDEVICE9* GetDevice();
		//void Draw(Mesh* mesh);
		void SetActiveMatrix(PEngineMatrix* matrix);

		void SetLights();

	private:
		//void SetTexture(BinaryData* texture);
		//void SetMaterial(Material* material);
		void SetMatrixCache(PEngineMatrix* matrix);

		LPDIRECT3D9 g_pD3D;
		LPDIRECT3DDEVICE9 g_pd3dDevice;
		//std::map<Mesh*, LPD3DXMESH> meshCache;
		std::map<BinaryData*, LPDIRECT3DTEXTURE9> textureCache;

		D3DXMATRIX* matrixCache;
	};
}
#endif