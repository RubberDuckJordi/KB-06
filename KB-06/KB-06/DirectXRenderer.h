#ifndef _DIRECTXRENDERER_H_
#define _DIRECTXRENDERER_H_

#include <d3dx9.h>
#include "MatrixWrapper.cpp"
#include "MaterialWrapper.cpp"
#include "TextureWrapper.cpp"
#include "MeshWrapper.cpp"

class DirectXRenderer
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
	void ClearScene(DWORD count, DWORD flags, D3DCOLOR color, float z, DWORD stencil);
	void PresentScene();
	void StopScene();

	void CreateVertexBuffer(int heightmapvertex, DWORD usage, DWORD fvf, D3DPOOL pool, void* vertexbuffer, HANDLE handle);
	void CreateIndexBuffer(int length, DWORD usage, D3DFORMAT format, D3DPOOL pool, void* Indexbuffer, HANDLE* handle);

	void SetMaterial(MaterialWrapper* wrapper);
	void SetTexture(TextureWrapper* wrapper);
	void SetFvF(DWORD fvf);
	void SetTransform(int type, MatrixWrapper* wrapper);

	void DrawPrimitive();
	void DrawSubset(MeshWrapper* wrapper);

	void SetStreamSource(); //??
	void SetIndices(); //??

	LPDIRECT3DDEVICE9* GetDevice();

private:
	LPDIRECT3D9 g_pD3D;
	LPDIRECT3DDEVICE9 g_pd3dDevice;
};

#endif