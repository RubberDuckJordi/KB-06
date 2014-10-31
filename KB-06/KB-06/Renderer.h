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
#include "Material.h"
#include "Vertex.h"
#include "Matrix.h"

/*
This interface contains all rendering functions
Must be implemented by a renderer implementation
*/

namespace pengine
{
	typedef unsigned int __w64	PENGINEHANDLE;
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

		virtual void SetCulling(CULLINGTYPE) = 0;
		virtual void SetZBuffer(bool) = 0;
		virtual void SetFillMode(FILLMODE) = 0;

		virtual void SetActiveCamera(CameraData camera, bool orthographic) = 0;
		virtual void SetProjectionMatrix(Matrix* ProjectionMatrix) = 0;
		virtual void SetViewMatrix(Matrix*) = 0;
		virtual void SetProjectionMatrix(float FOV, float farClippingPlane) = 0;

		virtual void BeginScene() = 0;
		//virtual void ClearScene(DWORD* count, DWORD* flags, PENGINECOLOR* color, float z, DWORD* stencil) = 0;
		virtual void ClearScene(unsigned long count, unsigned long flags, RGBAColor color, float z, unsigned long stencil) = 0;
		virtual void PresentScene(HWND hWnd) = 0;
		virtual void EndScene() = 0;

		virtual void SetMaterialWrapper(MaterialWrapper* wrapper) = 0;
		virtual void SetMaterial(Material* material) = 0;
		virtual void SetTexture(TextureWrapper* wrapper) = 0;
		virtual void SetFvF(DWORD* fvf) = 0;

		virtual void DrawSubset(MeshWrapper* wrapper, int subset) = 0;

		virtual void SetActiveMatrix(Matrix* matrix) = 0;

		virtual void SetLights() = 0;

		virtual VertexBufferWrapper* CreateVertexBuffer(Vertex*, unsigned int amountOfVertices) = 0;
		virtual VertexBufferWrapper* CreateColoredVertexBuffer(ColoredVertex*, unsigned int amountOfVertices) = 0;
		virtual IndexBufferWrapper* CreateIndexBuffer(unsigned int* indices, unsigned int amountOfIndices) = 0;
		virtual void DrawVertexBuffer(VertexBufferWrapper* vertexBuffer) = 0;
		virtual void DrawIndexedVertexBuffer(VertexBufferWrapper* vertexBuffer, IndexBufferWrapper* indexBuffer) = 0;

		virtual void ActivateRenderingToTexture(unsigned int textureIndex, int tWidth, int tHeight, RGBAColor bgColor) = 0;
		virtual void DeactivateRenderingToTexture(unsigned int textureIndex) = 0;
		virtual void SetTextureToRenderedTexture(int textureIndex) = 0;

		virtual void SetFontTexture(BinaryData* texture) = 0;
		/*!
		Draws the given text in the world using the currently active matrix as center.
		It uses the currently set fontTexure as texture.
		Note: every character is 1x1 in object space.
		Unknown characters are replaced with ?
		Undefined behaviour if the font texture isn't set/loaded.
		*/
		virtual void DrawString(std::string text, DWORD color) = 0;

		/*!
		Allows you to put a texture in the renderer's cache, failing to do
		this for a texture will result in undefined behaviour!
		Fortunately, the PEngine will do this for every texture loaded
		by the resource manager.
		*/
		virtual void CacheTexture(BinaryData* textureInRam) = 0;

		/*!
		Caches the given shader in text to the renderer.
		This will (depending on the renderer) compile the shader for the specific
		graphics card.
		*/
		virtual void CacheShader(std::string* shaderInTextInRam) = 0;

		/*!
		Sets the current shader to the given shader.
		Note that you still have to call 'BeginRenderingWithshader'.
		*/
		virtual void SetShader(std::string* shader) = 0;

		/*!
		Getting a parameter handle once speeds things up when you need to set
		the value for the parameter.
		*/
		virtual PENGINEHANDLE GetShaderParameterHandle(char* parameterName) = 0;

		/*!
		Getting a technique handle once speeds things up when you need to set
		the techique.
		*/
		virtual PENGINEHANDLE GetShaderTechniqueHandle(char* techniqueName) = 0;

		/*!
		Sets the active technique to the given technique
		*/
		virtual void SetShaderTechnique(PENGINEHANDLE technique) = 0;

		/*!
		The 'passes' parameter will be filled with the amount of passes in the
		currently active technique. It's up to you if you want to render with
		all the passes.
		*/
		virtual void BeginRenderingWithShader(unsigned int* passes) = 0;

		/*!
		Begins rendering with the specified pass.
		*/
		virtual void BeginRenderingWithPass(unsigned int pass) = 0;

		/*!
		Throws the given data in the parameter of the given shader.
		*/
		virtual void SetShaderValue(PENGINEHANDLE handleToParameter, PENGINEVOID data, unsigned int sizeInBytes) = 0;

		/*!
		Throws the given matrix in the parameter of the given shader, you can get
		the parameter handle to the desired matrix with GetShaderParameterHandle.
		*/
		virtual void SetShaderMatrix(PENGINEHANDLE handleToParameter, Matrix* data) = 0;

		/*!
		Updates changes to any 'set' calls in the pass. This should be called before
		any drawing call and after you have set all changes for the current pass.
		Basically, you do not need to call CommitChanges if you are not setting any parameters
		between the BeginRenderingWithPass and EndRenderingPass.
		*/
		virtual void CommitChanges() = 0;

		/*!
		Ends rendering with the specified pass, should be called before beginning
		with a new pass.
		*/
		virtual void EndRenderingPass() = 0;

		virtual void EndRenderingWithShader() = 0;

	protected:
		Logger* logger;
		BinaryData* fontTexture;
	};
}
#endif