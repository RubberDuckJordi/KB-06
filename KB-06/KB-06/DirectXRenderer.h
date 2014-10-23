#ifndef _PENGINE_DIRECTXRENDERER_H_
#define _PENGINE_DIRECTXRENDERER_H_

//#include <d2d1.h>
#include <d3dx9.h>
#include <vector>
#include "Renderer.h"
//#include <wincodec.h>

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

		void SetActiveCamera(CameraData camera, bool orthographic);

		void SetProjectionMatrix(Matrix* ProjectionMatrix);
		void SetViewMatrix(Matrix*);
		void SetProjectionMatrix(float FOV, float farClippingPlane);

		void BeginScene();
		void ClearScene(DWORD* count, DWORD* flags, PENGINECOLOR* color, float z, DWORD* stencil);
		void ClearScene(unsigned long count, unsigned long flags, RGBAColor color, float z, unsigned long stencil);
		void PresentScene(HWND hWnd);
		void EndScene();

		void SetMaterialWrapper(MaterialWrapper* wrapper);
		void SetMaterial(Material* material);
		void SetTexture(TextureWrapper* wrapper);
		void SetFvF(DWORD* fvf);

		void DrawSubset(MeshWrapper* wrapper, int subset);

		LPDIRECT3DDEVICE9* GetDevice();
		void SetActiveMatrix(Matrix* matrix);

		void SetLights();

		VertexBufferWrapper* CreateVertexBuffer(Vertex* vertices, int amountOfVertices);
		VertexBufferWrapper* CreateColoredVertexBuffer(ColoredVertex* coloredVertices, int amountOfVertices);
		IndexBufferWrapper* CreateIndexBuffer(int* indices, int amountOfIndices);
		void DrawVertexBuffer(VertexBufferWrapper* vertexBufferWrapper, int amountOfVertices);
		void DrawIndexedVertexBuffer(VertexBufferWrapper* vertexBufferWrapper, IndexBufferWrapper* indexBufferWrapper, int amountOfIndices, int amountOfFaces);

		void ActivateRenderingToTexture(int textureIndex, int tWidth, int tHeight, RGBAColor bgColor);
		void DeactivateRenderingToTexture(int textureIndex);
		void SetTextureToRenderedTexture(int textureIndex);

		/*!
		Sets the font texture that will be used to the given texture.
		*/
		void SetFontTexture(BinaryData* texture);
		/*!
		Draws the given text in the world using the currently active matrix as center.
		It uses the currently set fontTexure as texture.
		Note: every character is 1x1 in object space.
		Unknown characters are replaced with ?
		Undefined behaviour if the font texture isn't set/loaded.
		*/
		void DrawString(std::string text, DWORD color);

	private:
		void SetMatrixCache(Matrix* matrix);

		// Have yet to figure out how to get rid of this.
		// Basically it's a copied pointer to the device's back buffer
		LPDIRECT3DSURFACE9 MainSurface;

		// And here we have the whole point of this file: The render surface and associated texture
		std::vector<LPDIRECT3DSURFACE9> RenderSurfaces;
		std::vector<LPDIRECT3DTEXTURE9> RenderTextures;

		RECT rectangle;

		//IWICBitmapDecoder* iwicBmpDecoder;
		//IWICImagingFactory* iwicFactory;
		//IWICBitmapFrameDecode *bitmapFrame;
		//IWICFormatConverter* iwicFormatConverter;
		/*ID2D1Bitmap* d2dBmp;

		ID2D1Factory* d2dFactory;
		ID2D1HwndRenderTarget* d2dRenderTarget;*/

		LPDIRECT3DTEXTURE9 surfaceTexture;
		IDirect3DSurface9* d3dSurface;
		IDirect3DSurface9* surfaceLevel;
		IDirect3DSurface9* backbuffer;

		LPDIRECT3D9 g_pD3D;
		LPDIRECT3DDEVICE9 g_pd3dDevice;

		std::map<BinaryData*, LPDIRECT3DTEXTURE9> textureCache;

		D3DXMATRIX* matrixCache;
		D3DXMATRIXA16 projectionMatix;

		D3DXPLANE   frustrumPlane[6];
	};
}
#endif