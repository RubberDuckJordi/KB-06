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
		void SetDefaultRenderStates();

		void SetRenderState(PENGINERENDERSTATETYPE* state, PENGINEDWORD* dword);

		void SetActiveCamera(CameraData camera);

		void SetProjectionMatrix(MatrixWrapper* ProjectionMatrix);
		void SetProjectionMatrix(float FOV, float farClippingPlane);

		void BeginScene();
		void ClearScene(PENGINEDWORD* count, PENGINEDWORD* flags, PENGINECOLOR* color, float z, PENGINEDWORD* stencil);
		void ClearScene(unsigned long count, unsigned long flags, Resource::RGBAColor color, float z, unsigned long stencil);
		void PresentScene(HWND hWnd);
		void EndScene();

		void CreateVertexBuffer(int heightmapvertex, PENGINEDWORD* usage, PENGINEDWORD* fvf, PENGINEPOOL* pool, VertexBufferWrapper* vertexbuffer, HANDLE handle);
		void CreateIndexBuffer(int length, PENGINEDWORD* usage, PENGINEFORMAT* format, PENGINEPOOL* pool, IndexBufferWrapper* Indexbuffer, HANDLE* handle);

		void SetMaterial(MaterialWrapper* wrapper);
		void SetTexture(TextureWrapper* wrapper);
		void SetFvF(PENGINEDWORD* fvf);
		//void SetTransform(int type, MatrixWrapper* wrapper);

		void DrawPrimitive(Resource::Mesh mesh);
		void DrawSubset(MeshWrapper* wrapper, int subset);

		void SetStreamSource(); //??
		void SetIndices(); //??

		LPDIRECT3DDEVICE9* GetDevice();
		void Draw(Resource::Mesh* mesh);
		void SetActiveMatrix(PEngineMatrix* matrix);

		void SetWorldMatrixForStaticEntity(Resource::Vertex* translation, Resource::Vertex* rotation, Resource::Vertex* scaling);
		void SetWorldMatrix(Resource::Vertex* translation, Resource::Vertex* rotation, Resource::Vertex* scaling, Resource::Vertex* cameraPosition, Resource::Vertex* cameraRotation);
		void SetLights();
	private:
		void SetTexture(Resource::BinaryData* texture);
		void SetMaterial(Resource::Material* material);
		D3DXMATRIX* CreateD3DMATRIX(Resource::Vertex* p_translation, Resource::Vertex* p_rotation, Resource::Vertex* p_scaling);

		LPDIRECT3D9 g_pD3D;
		LPDIRECT3DDEVICE9 g_pd3dDevice;
		std::map<Resource::Mesh*, LPD3DXMESH> meshCache;
		std::map<Resource::BinaryData*, LPDIRECT3DTEXTURE9> textureCache;
		D3DXMATRIXA16 matView;

		D3DXMATRIX* matrixCache;
	};
}


#endif