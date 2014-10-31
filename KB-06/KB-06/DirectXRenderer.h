#ifndef _PENGINE_DIRECTXRENDERER_H_
#define _PENGINE_DIRECTXRENDERER_H_

#include <d3dx9.h>
#include <vector>
#include "Renderer.h"

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
		//void ClearScene(DWORD* count, DWORD* flags, PENGINECOLOR* color, float z, DWORD* stencil);
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

		VertexBufferWrapper* CreateVertexBuffer(Vertex* vertices, unsigned int amountOfVertices);
		VertexBufferWrapper* CreateColoredVertexBuffer(ColoredVertex* coloredVertices, unsigned int amountOfVertices);
		IndexBufferWrapper* CreateIndexBuffer(unsigned int* indices, unsigned int amountOfIndices);
		void DrawVertexBuffer(VertexBufferWrapper* vertexBufferWrapper);
		void DrawIndexedVertexBuffer(VertexBufferWrapper* vertexBufferWrapper, IndexBufferWrapper* indexBufferWrapper);

		void ActivateRenderingToTexture(unsigned int textureIndex, int tWidth, int tHeight, RGBAColor bgColor);
		void DeactivateRenderingToTexture(unsigned int textureIndex);
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

		/*!
		Allows you to put a texture in the renderer's cache, failing to do
		this for a texture will result in a crash!
		Fortunately, the PEngine will do this for every texture loaded
		by the resource manager.
		*/
		void CacheTexture(BinaryData* textureInRam);

		/*!
		Caches the given shader in text to the renderer.
		This will (depending on the renderer) compile the shader for the specific
		graphics card.
		*/
		void Cacheshader(std::string* shaderInText);

		/*!
		Sets the current shader to the given shader.
		Note that you still have to call 'BeginRenderingWithshader'.
		*/
		void Setshader(std::string* shader);

		/*!
		Getting a parameter handle once speeds things up when you need to set
		the value for the parameter.
		*/
		PENGINEHANDLE GetshaderParameterHandle(char* parameterName);

		/*!
		Getting a technique handle once speeds things up when you need to set
		the techique.
		*/
		PENGINEHANDLE GetshaderTechniqueHandle(char* techniqueName);

		/*!
		Sets the active technique to the given technique
		*/
		void SetshaderTechnique(PENGINEHANDLE technique);

		/*!
		The 'passes' parameter will be filled with the amount of passes in the
		currently active technique. It's up to you if you want to render with
		all the passes.
		*/
		void BeginRenderingWithshader(unsigned int* passes);

		/*!
		Begins rendering with the specified pass.
		*/
		void BeginRenderingWithPass(unsigned int pass);

		/*!
		Throws the given data in the parameter of the given shader.
		*/
		void SetshaderValue(PENGINEHANDLE handleToParameter, PENGINEVOID data, unsigned int sizeInBytes);

		/*!
		Throws the given matrix in the parameter of the given shader, you can get
		the parameter handle to the desired matrix with GetshaderParameterHandle.
		*/
		void SetshaderMatrix(PENGINEHANDLE handleToParameter, Matrix* data);

		/*!
		Updates changes to any 'set' calls in the pass. This should be called before
		any drawing call and after you have set all changes for the current pass.
		Basically, you do not need to call CommitChanges if you are not setting any parameters
		between the BeginRenderingWithPass and EndRenderingPass.
		*/
		void CommitChanges();

		/*!
		Ends rendering with the specified pass, should be called before beginning
		with a new pass.
		*/
		void EndRenderingPass();

		void EndRenderingWithshader();

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
		ID3DXEffect* currentlyActiveshader;
		std::map<std::string*, ID3DXEffect*> shaderCache;

		D3DXMATRIX* matrixCache;
		D3DXMATRIXA16 projectionMatix;

		D3DXPLANE   frustrumPlane[6];
	};
}
#endif