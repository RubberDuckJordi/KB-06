#ifndef _PENGINE_DIRECTXRENDERER_H_
#define _PENGINE_DIRECTXRENDERER_H_

#include <d2d1.h>
#include <d3dx9.h>
#include "Renderer.h"
#include <wincodec.h>

namespace pengine
{
	class DirectXRenderer : public Renderer
	{
	public:
		DirectXRenderer();
		~DirectXRenderer();

		void CreateD2DFactory();
		void CreateRenderTarget(HWND hWnd);
		void CreateWICImagingFactory();
		void CreateDecoder(std::string path);
		void GetBitmapFrame();
		void InitializeBMP();
		void CreateFormatConverter();
		void CreateBitmapFromWIC();
		void D2DDraw();

		void InitD3D(HWND hWnd);
		void SetDefaultRenderStates();

		void SetCulling(CULLINGTYPE);
		void SetZBuffer(bool);
		void SetFillMode(FILLMODE);

		void SetActiveCamera(CameraData camera);

		void SetProjectionMatrix(PEngineMatrix* ProjectionMatrix);
		void SetProjectionMatrix(float FOV, float farClippingPlane);

		void BeginScene();
		void ClearScene(PENGINEDWORD* count, PENGINEDWORD* flags, PENGINECOLOR* color, float z, PENGINEDWORD* stencil);
		void ClearScene(unsigned long count, unsigned long flags, RGBAColor color, float z, unsigned long stencil);
		void PresentScene(HWND hWnd);
		void EndScene();

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

		VertexBufferWrapper* CreateVertexBuffer(D3DCustomVertex*, int amountOfIndices, int fvf);
		IndexBufferWrapper* CreateIndexBuffer(int* indices, int amountOfIndices);
		void DrawVertexBuffer(VertexBufferWrapper*, int amountOfIndices);
		void DrawIndexedVertexBuffer(VertexBufferWrapper*, IndexBufferWrapper*, int amountOfVertices);

	private:
		//void SetTexture(BinaryData* texture);
		//void SetMaterial(Material* material);
		void SetMatrixCache(PEngineMatrix* matrix);

		RECT rectangle;

		IWICBitmapDecoder* iwicBmpDecoder;
		IWICImagingFactory* iwicFactory;
		IWICBitmapFrameDecode *bitmapFrame;
		IWICFormatConverter* iwicFormatConverter;
		ID2D1Bitmap* d2dBmp;

		ID2D1Factory* d2dFactory;
		ID2D1HwndRenderTarget* d2dRenderTarget;

		LPDIRECT3D9 g_pD3D;
		LPDIRECT3DDEVICE9 g_pd3dDevice;
		//std::map<Mesh*, LPD3DXMESH> meshCache;
		std::map<BinaryData*, LPDIRECT3DTEXTURE9> textureCache;

		D3DXMATRIX* matrixCache;
	};
}
#endif