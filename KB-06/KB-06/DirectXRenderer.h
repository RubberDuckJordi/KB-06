#ifndef _DIRECTXRENDERER_H_
#define _DIRECTXRENDERER_H_

#include <d3dx9.h>
#include "MatrixWrapper.cpp"
#include "MaterialWrapper.cpp"
#include "TextureWrapper.cpp"
#include "DWORDWrapper.cpp"

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
	void ClearScene(DWORDWrapper* count, DWORDWrapper* flags, D3DCOLOR color, float z, DWORDWrapper* stencil);
	void PresentScene();
	void StopScene();

	void CreateVertexBuffer(int heightmapvertex, DWORDWrapper* usage, DWORDWrapper* fvf, D3DPOOL pool, void* vertexbuffer, HANDLE handle);
	void CreateIndexBuffer(int length, DWORDWrapper* usage, D3DFORMAT format, D3DPOOL pool, void* Indexbuffer, HANDLE* handle);

	void SetMaterial(MaterialWrapper* wrapper);
	void SetTexture(TextureWrapper* wrapper);
	void SetFvF(DWORDWrapper* fvf);
	void SetTransform(int type, MatrixWrapper* wrapper);

	void DrawPrimitive();
	void DrawSubset();

	void SetStreamSource(); //??
	void SetIndices(); //??

	LPDIRECT3DDEVICE9* GetDevice();

private:
	LPDIRECT3D9 g_pD3D;
	LPDIRECT3DDEVICE9 g_pd3dDevice;
};

#endif