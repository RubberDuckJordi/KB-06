#include "DirectXRenderer.h"
#include "CustomD3DVertex.h"
#include "BinaryData.h"
#include <math.h>

#include <algorithm>

namespace pengine
{
	DirectXRenderer::DirectXRenderer()
	{
		logger = LoggerPool::GetInstance().GetLogger();
		g_pD3D = NULL;
		g_pd3dDevice = NULL;
		matrixCache = new D3DXMATRIX();
		//d2dBmp = NULL;
	}

	DirectXRenderer::~DirectXRenderer()
	{
		if (g_pd3dDevice != NULL)
		{
			g_pd3dDevice->Release();
		}

		if (g_pD3D != NULL)
		{
			g_pD3D->Release();
		}
		logger->Log(Logger::INFO, "DirectXRenderer destructed");
	}

	void DirectXRenderer::CreateD2DFactory()
	{
		//D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);
	}

	void DirectXRenderer::CreateRenderTarget(HWND hWnd)
	{
		/*D3DXCreateTexture(g_pd3dDevice, 500, 500, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &surfaceTexture); //LPDIRECT3DTEXTURE9
		surfaceTexture->GetSurfaceLevel(0, &surfaceLevel); //IDirect3DSurface9
		g_pd3dDevice->GetRenderTarget(0, &backbuffer); //IDirect3DSurface9

		GetClientRect(hWnd, &rectangle);

		D2D1_SIZE_U size = D2D1::SizeU(rectangle.right - rectangle.left, rectangle.bottom - rectangle.top);

		d2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, size),
		&d2dRenderTarget
		);*/
	}

	void DirectXRenderer::CreateWICImagingFactory()
	{
		//CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, __uuidof(IWICImagingFactory), (void**)(&iwicFactory));
	}

	void DirectXRenderer::CreateDecoder(std::string path)
	{
		/*size_t newSize = strlen(path.c_str()) + 1;

		wchar_t* wPath = new wchar_t[newSize];

		size_t convertedCharacters = 0;

		mbstowcs_s(&convertedCharacters, wPath, newSize, path.c_str(), _TRUNCATE);

		iwicBmpDecoder = NULL;
		iwicFactory->CreateDecoderFromFilename(
		wPath,                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&iwicBmpDecoder                      // Pointer to the decoder
		);*/
	}

	void DirectXRenderer::CreateFormatConverter()
	{
		//iwicFactory->CreateFormatConverter(&iwicFormatConverter);
	}

	void DirectXRenderer::GetBitmapFrame()
	{
		//bitmapFrame = NULL;

		//iwicBmpDecoder->GetFrame(0, &bitmapFrame);
	}

	void DirectXRenderer::InitializeBMP()
	{
		//iwicFormatConverter->Initialize(bitmapFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
	}

	void DirectXRenderer::CreateBitmapFromWIC()
	{
		//d2dRenderTarget->CreateBitmapFromWicBitmap(iwicFormatConverter, NULL, &d2dBmp);
	}

	void DirectXRenderer::D2DDraw()
	{
		/*g_pd3dDevice->SetRenderTarget(0, surfaceLevel);
		d2dRenderTarget->BeginDraw();
		D2D1_RECT_F test = D2D1::RectF(0, 0, 200, 200);
		//d2dRenderTarget->DrawBitmap(d2dBmp, test);

		d2dRenderTarget->EndDraw();
		g_pd3dDevice->SetRenderTarget(0, backbuffer);*/
	}

	void DirectXRenderer::InitD3D(HWND hWnd)
	{
		if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		{
			logger->Log(Logger::ERR, "Failed to instantiate Direct3DCreate9");
			return;
		}

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));

		d3dpp.Windowed = true;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		//d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;//The higher you can set this, the more accurate the z-buffer is, current seems to be the highest working.
		d3dpp.EnableAutoDepthStencil = true;
		//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;//The higher you can set this, the more accurate the z-buffer is, current seems to be the highest working.

		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pd3dDevice)))
		{
			logger->Log(Logger::ERR, "Failed to instantiate Direct3D9 CreateDevice");
			return;
		}
		g_pd3dDevice->GetRenderTarget(0, &MainSurface);//keeping a copy of the original rendering surface...
	}

	void DirectXRenderer::SetDefaultRenderStates()
	{
		this->g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//Counter Clockwise Cullmode
		this->g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, true); //Z buffer on
		this->g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true); //Turn Alphablending on
		this->g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //Type alphablending
		this->g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //Type alphablending
		//this->g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	};

	void DirectXRenderer::SetCulling(CULLINGTYPE cullingType)
	{
		this->g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, static_cast<D3DCULL>(cullingType));
	}

	void DirectXRenderer::SetZBuffer(bool param)
	{
		this->g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, param);
	}

	void DirectXRenderer::SetFillMode(FILLMODE fillmode)
	{
		this->g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, static_cast<D3DFILLMODE>(fillmode));
	}

	void DirectXRenderer::SetActiveCamera(CameraData camera, bool orthographic)
	{
		if (orthographic)
		{
			D3DXMatrixOrthoLH(matrixCache, 1.0f, 1.0f, 1.0f, 200.0f);
			//g_pd3dDevice->SetTransform(D3DTS_WORLD, matrixCache);//isn't needed...
			g_pd3dDevice->SetTransform(D3DTS_PROJECTION, matrixCache);
			//g_pd3dDevice->SetTransform(D3DTS_VIEW, matrixCache);
		}
		else
		{
			// Set up our view matrix. A view matrix can be defined given an eye point,
			// a point to lookat, and a direction for which way is up. Here, we set the
			// eye 0.5 units back along the z-axis and up 0 units, look at the 
			// origin + 0.5 on the z-axis, and define "up" to be in the y-direction.
			D3DXVECTOR3 vEyePt(camera.x, camera.y, camera.z);
			D3DXVECTOR3 vLookatPt(camera.lookAtX, camera.lookAtY, camera.lookAtZ);
			D3DXVECTOR3 vUpVec(camera.upVecX, camera.upVecY, camera.upVecZ);
			D3DXMatrixLookAtLH(matrixCache, &vEyePt, &vLookatPt, &vUpVec);
			g_pd3dDevice->SetTransform(D3DTS_VIEW, matrixCache);
		}
	}

	void DirectXRenderer::SetViewMatrix(Matrix* viewMatrix)
	{
		// Set up our view matrix. A view matrix can be defined given an eye point,
		// a point to lookat, and a direction for which way is up. Here, we set the
		// eye 0.5 units back along the z-axis and up 0 units, look at the 
		// origin + 0.5 on the z-axis, and define "up" to be in the y-direction.

		SetMatrixCache(viewMatrix);
		g_pd3dDevice->SetTransform(D3DTS_VIEW, matrixCache);
	}

	void DirectXRenderer::SetProjectionMatrix(Matrix* projectionMatrix)
	{
		SetMatrixCache(projectionMatrix);
		this->g_pd3dDevice->SetTransform(D3DTS_PROJECTION, matrixCache);
	}

	void DirectXRenderer::SetProjectionMatrix(float FOV, float farClippingPlane)
	{
		// For the projection matrix, we set up a perspective transform (which
		// transforms geometry from 3D view space to 2D viewport space, with
		// a perspective divide making objects smaller in the distance). To build
		// a perpsective transform, we need the field of view (1/4 pi is common),
		// the aspect ratio, and the near and far clipping planes (which define at
		// what distances geometry should be no longer be rendered).
		D3DXMatrixPerspectiveFovLH(&projectionMatix, FOV, 1.0f, 1.0f, farClippingPlane);
		g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &projectionMatix);
	}

	void DirectXRenderer::BeginScene()
	{
		this->g_pd3dDevice->BeginScene();
	}

	void DirectXRenderer::ClearScene(PENGINEDWORD* count, PENGINEDWORD* flags, PENGINECOLOR* color, float z, PENGINEDWORD* stencil)
	{
		this->g_pd3dDevice->Clear(*count, NULL, *flags, *color, z, *stencil);
	}

	void DirectXRenderer::ClearScene(unsigned long count, unsigned long flags, RGBAColor color, float z, unsigned long stencil){
		flags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
		g_pd3dDevice->Clear(PENGINEDWORD(count), NULL, PENGINEDWORD(flags),
			D3DCOLOR_COLORVALUE(color.r, color.g, color.b, color.a), z, PENGINEDWORD(stencil));
	}

	void DirectXRenderer::PresentScene(HWND hWnd)
	{
		this->g_pd3dDevice->Present(NULL, NULL, hWnd, NULL);
	}

	void DirectXRenderer::EndScene()
	{
		this->g_pd3dDevice->EndScene();
	}

	void DirectXRenderer::SetMaterialWrapper(MaterialWrapper* wrapper)
	{
		g_pd3dDevice->SetMaterial(wrapper->GetMaterial());
	}

	void DirectXRenderer::SetMaterial(Material* material)
	{
		D3DMATERIAL9 mat;
		mat.Ambient.r = material->ambient.r;
		mat.Ambient.g = material->ambient.g;
		mat.Ambient.b = material->ambient.b;

		mat.Diffuse.r = material->diffuse.r;
		mat.Diffuse.g = material->diffuse.g;
		mat.Diffuse.b = material->diffuse.b;

		mat.Specular.r = material->specular.r;
		mat.Specular.g = material->specular.g;
		mat.Specular.b = material->specular.b;
		mat.Power = material->power;

		g_pd3dDevice->SetMaterial(&mat);

		if (material->texture != NULL)
		{
			if (textureCache.find(material->texture) == textureCache.end())
			{
				//logger->LogAll(Logger::DEBUG, "Texture \"", material->texturePath, "\" not converted to LPDIRECT3DTEXTURE9 yet.");
				LPDIRECT3DTEXTURE9 d3DTexture;

				HRESULT result = D3DXCreateTextureFromFileInMemory(g_pd3dDevice, material->texture->rawData, material->texture->size, &d3DTexture);
				textureCache[material->texture] = d3DTexture;
				//logger->LogAll(Logger::DEBUG, "Texture \"", material->texturePath, "\" converted to LPDIRECT3DTEXTURE9.");
			}
			g_pd3dDevice->SetTexture(0, textureCache[material->texture]);
		}
		else
		{
			g_pd3dDevice->SetTexture(0, NULL);
		}
	}

	void DirectXRenderer::SetTexture(TextureWrapper* wrapper)
	{
		g_pd3dDevice->SetTexture(0, *wrapper->GetTexture());
	}

	void DirectXRenderer::SetFvF(PENGINEDWORD* fvf)
	{
		g_pd3dDevice->SetFVF(*fvf);
	}

	void DirectXRenderer::DrawSubset(MeshWrapper* wrapper, int subset)
	{
		(*wrapper->GetMesh())->DrawSubset(subset);
	}

	LPDIRECT3DDEVICE9* DirectXRenderer::GetDevice()
	{
		return &g_pd3dDevice;
	}

	void DirectXRenderer::SetActiveMatrix(Matrix* matrix)
	{
		SetMatrixCache(matrix);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, matrixCache);
	}

	void DirectXRenderer::SetLights()
	{
		g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);//we don't do anything with special lights
		g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);//a nice shining white
	}

	void DirectXRenderer::SetMatrixCache(Matrix* matrix)
	{
		matrixCache->_11 = (*matrix)[0];
		matrixCache->_12 = (*matrix)[1];
		matrixCache->_13 = (*matrix)[2];
		matrixCache->_14 = (*matrix)[3];

		matrixCache->_21 = (*matrix)[4];
		matrixCache->_22 = (*matrix)[5];
		matrixCache->_23 = (*matrix)[6];
		matrixCache->_24 = (*matrix)[7];

		matrixCache->_31 = (*matrix)[8];
		matrixCache->_32 = (*matrix)[9];
		matrixCache->_33 = (*matrix)[10];
		matrixCache->_34 = (*matrix)[11];

		matrixCache->_41 = (*matrix)[12];
		matrixCache->_42 = (*matrix)[13];
		matrixCache->_43 = (*matrix)[14];
		matrixCache->_44 = (*matrix)[15];
	}

	VertexBufferWrapper* DirectXRenderer::CreateVertexBuffer(D3DCustomVertex* p_vertices, int amountOfVertices)
	{
		IDirect3DVertexBuffer9** buffer = new LPDIRECT3DVERTEXBUFFER9();
		VertexBufferWrapper* vertexBufferWrapper = new VertexBufferWrapper();
		vertexBufferWrapper->SetVertexBuffer(buffer);
		vertexBufferWrapper->SetFVF(D3DCustomVertexFVF);

		if (FAILED(g_pd3dDevice->CreateVertexBuffer(amountOfVertices * sizeof(D3DCustomVertex),
			0, D3DCustomVertexFVF, D3DPOOL_DEFAULT, vertexBufferWrapper->GetVertexBuffer(), NULL)))
		{
			logger->Log(Logger::ERR, "DirectXRenderer::CreateVertexBuffer() vertexbuffer create failed");
		}

		void* verticesBuffer;
		int size = sizeof(D3DCustomVertex)*amountOfVertices;

		if (FAILED((*vertexBufferWrapper->GetVertexBuffer())->Lock(0, size, (void**)&verticesBuffer, 0)))
		{
			logger->Log(Logger::ERR, "DirectXRenderer::CreateVertexBuffer() vertexbuffer lock failed");
		}
		memcpy(verticesBuffer, p_vertices, size);
		(*vertexBufferWrapper->GetVertexBuffer())->Unlock();

		return vertexBufferWrapper;
	}

	VertexBufferWrapper* DirectXRenderer::CreateColoredVertexBuffer(D3DCustomColoredVertex* p_vertices, int amountOfVertices)
	{
		IDirect3DVertexBuffer9** buffer = new LPDIRECT3DVERTEXBUFFER9();
		VertexBufferWrapper* vertexBufferWrapper = new VertexBufferWrapper();
		vertexBufferWrapper->SetVertexBuffer(buffer);
		vertexBufferWrapper->SetFVF(D3DCustomColoredVertexFVF);

		if (FAILED(g_pd3dDevice->CreateVertexBuffer(amountOfVertices * sizeof(D3DCustomColoredVertex),
			0, D3DCustomColoredVertexFVF, D3DPOOL_DEFAULT, vertexBufferWrapper->GetVertexBuffer(), NULL)))
		{
			logger->Log(Logger::ERR, "DirectXRenderer::CreateVertexBuffer() vertexbuffer create failed");
		}

		void* verticesBuffer;
		int size = sizeof(D3DCustomColoredVertex)*amountOfVertices;

		if (FAILED((*vertexBufferWrapper->GetVertexBuffer())->Lock(0, size, (void**)&verticesBuffer, 0)))
		{
			logger->Log(Logger::ERR, "DirectXRenderer::CreateVertexBuffer() vertexbuffer lock failed");
		}
		memcpy(verticesBuffer, p_vertices, size);
		(*vertexBufferWrapper->GetVertexBuffer())->Unlock();

		return vertexBufferWrapper;
	}

	IndexBufferWrapper* DirectXRenderer::CreateIndexBuffer(int* indices, int amountOfIndices)
	{
		IndexBufferWrapper* wrapper = new IndexBufferWrapper();
		LPDIRECT3DINDEXBUFFER9* indexBuffer = new LPDIRECT3DINDEXBUFFER9();
		wrapper->SetIndexBuffer(indexBuffer);

		g_pd3dDevice->CreateIndexBuffer(amountOfIndices * sizeof(int), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, indexBuffer, NULL);

		void* pVoid;

		//d3dMesh->GetIndexBuffer(&i_buffer);
		// lock i_buffer and load the indices into it
		(*indexBuffer)->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, indices, amountOfIndices * sizeof(int));
		(*indexBuffer)->Unlock();

		return wrapper;
	}

	void DirectXRenderer::DrawVertexBuffer(VertexBufferWrapper* vertexBuffer, int amountOfIndices)
	{
		g_pd3dDevice->SetFVF(vertexBuffer->GetFVF());
		if (vertexBuffer->GetFVF() == D3DCustomVertexFVF)
		{
			g_pd3dDevice->SetStreamSource(0, *vertexBuffer->GetVertexBuffer(), 0, sizeof(D3DCustomVertex));
		}
		else
		{
			g_pd3dDevice->SetStreamSource(0, *vertexBuffer->GetVertexBuffer(), 0, sizeof(D3DCustomColoredVertex));
		}

		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, amountOfIndices / 3);
	}

	void DirectXRenderer::DrawIndexedVertexBuffer(VertexBufferWrapper* v_buffer, IndexBufferWrapper* i_buffer, int amountOfVertices, int amountOfFaces)
	{
		if (v_buffer->GetFVF() == D3DCustomVertexFVF)
		{
			g_pd3dDevice->SetStreamSource(0, *v_buffer->GetVertexBuffer(), 0, sizeof(D3DCustomVertex));
			g_pd3dDevice->SetFVF(D3DCustomVertexFVF);
		}
		else
		{
			g_pd3dDevice->SetStreamSource(0, *v_buffer->GetVertexBuffer(), 0, sizeof(D3DCustomColoredVertex));
			g_pd3dDevice->SetFVF(D3DCustomColoredVertexFVF);
		}
		g_pd3dDevice->SetIndices(*i_buffer->GetIndexBuffer());
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,// PrimitiveType
			0,// BaseVertexIndex
			0,// MinIndex
			amountOfVertices,// NumVertices
			0,// StartIndex
			amountOfFaces);// PrimitiveCount
	}

	void DirectXRenderer::ActivateRenderingToTexture(int textureIndex, int tWidth, int tHeight, RGBAColor bgColor)
	{
		//actually both while loops should probably move away from here...
		while (RenderTextures.size() != 0)
		{
			//this is probably not needed because of clearscene?
			//actually, we really only need to make the textures once...
			RenderTextures.back()->Release();
			RenderTextures.pop_back();

			RenderSurfaces.back()->Release();
			RenderSurfaces.pop_back();
		}

		while (textureIndex + 1 > RenderTextures.size())
		{
			//Create our render target, making it the same size as the screen. Usually DX would resize it to a 2^x size, but
			//we're creating it as a "D3DUSAGE_RENDERTARGET" so it can set it the same as the screen's size.
			LPDIRECT3DTEXTURE9 toAdd;
			g_pd3dDevice->CreateTexture(tWidth, tHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &toAdd, NULL);
			//g_pd3dDevice->CreateTexture(tWidth, tHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &RenderTextures[textureIndex], NULL);
			RenderTextures.push_back(toAdd);

			LPDIRECT3DSURFACE9 addToo;
			//Here we grab a pointer to the surface so we can pass it to SetRenderTarget
			toAdd->GetSurfaceLevel(0, &addToo);
			RenderSurfaces.push_back(addToo);
		}

		//Change our rendering target to our created surface.
		g_pd3dDevice->SetRenderTarget(0, RenderSurfaces[textureIndex]);
		//Clear it too, with a different color to make sure we're getting it.
		ClearScene(0, 0, bgColor, 1.0f, 0);
		//Start the renderer to render to the texture scene
		BeginScene();
	}

	void DirectXRenderer::DeactivateRenderingToTexture(int textureIndex)
	{
		//We're done rendering to the texture scene
		EndScene();
		//PresentScene(NULL);//maybe needed if stuff doesn't work?
		//D3DXSaveTextureToFile(L"test.bmp", D3DXIFF_BMP, RenderTextures[textureIndex], NULL);
		//And we change back to the actual backbuffer
		g_pd3dDevice->SetRenderTarget(0, MainSurface);
		//SetProjectionMatrix(M_PI / 4, 100.0f);
	}

	void DirectXRenderer::SetTextureToRenderedTexture(int textureIndex)
	{
		//Set the texture we're using to the texture we just rendered to. (Neat huh? :D)
		g_pd3dDevice->SetTexture(0, RenderTextures[textureIndex]);
	}

	void DirectXRenderer::SetFontTexture(BinaryData* texture)
	{
		fontTexture = texture;
	}

	void DirectXRenderer::DrawString(std::string text, DWORD color)
	{
		/*g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSW, D3DTADDRESS_CLAMP);
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);*/
		unsigned int amountOfCharacters = 47;
		float textureWidthPerCharacter = 1.0f / amountOfCharacters;
		int maxWidth = 0;
		unsigned int width = 0;
		unsigned int height = 1;
		unsigned int characters = 0;
		for (int i = 0; i < text.size(); ++i)
		{
			switch (text[i])
			{
			case '\n':
			case '\r':
				++height;
				if (width > maxWidth)
				{
					maxWidth = width;
				}
				width = 0;
				break;
			default:
				++width;
				++characters;
				break;
			}
		}
		if (width > maxWidth)
		{
			maxWidth = width;
		}

		std::transform(text.begin(), text.end(), text.begin(), ::tolower);

		D3DCustomColoredVertex* vertices = new D3DCustomColoredVertex[characters * 4];//4 vertices per character
		int* indices = new int[characters * 6];//6 indices per character, to make 2 faces to make a square

		float minWidth = -((maxWidth * 1.1f - 0.1f) / 2.0f);
		float maxHeight = (height * 1.1f - 0.1f) / 2.0f - 1.0f;
		int currentX = 0;
		int currentY = 0;
		int iOffset = 0;

		for (int i = 0; i < text.size(); ++i)
		{
			int charIndex = 0;
			bool makeChar = true;
			switch (text[i])
			{
			case 'a':
				charIndex = 0;
				break;
			case 'b':
				charIndex = 1;
				break;
			case 'c':
				charIndex = 2;
				break;
			case 'd':
				charIndex = 3;
				break;
			case 'e':
				charIndex = 4;
				break;
			case 'f':
				charIndex = 5;
				break;
			case 'g':
				charIndex = 6;
				break;
			case 'h':
				charIndex = 7;
				break;
			case 'i':
				charIndex = 8;
				break;
			case 'j':
				charIndex = 9;
				break;
			case 'k':
				charIndex = 10;
				break;
			case 'l':
				charIndex = 11;
				break;
			case 'm':
				charIndex = 12;
				break;
			case 'n':
				charIndex = 13;
				break;
			case 'o':
				charIndex = 14;
				break;
			case 'p':
				charIndex = 15;
				break;
			case 'q':
				charIndex = 16;
				break;
			case 'r':
				charIndex = 17;
				break;
			case 's':
				charIndex = 18;
				break;
			case 't':
				charIndex = 19;
				break;
			case 'u':
				charIndex = 20;
				break;
			case 'v':
				charIndex = 21;
				break;
			case 'w':
				charIndex = 22;
				break;
			case 'x':
				charIndex = 23;
				break;
			case 'y':
				charIndex = 24;
				break;
			case 'z':
				charIndex = 25;
				break;
			case '0':
				charIndex = 26;
				break;
			case '1':
				charIndex = 27;
				break;
			case '2':
				charIndex = 28;
				break;
			case '3':
				charIndex = 29;
				break;
			case '4':
				charIndex = 30;
				break;
			case '5':
				charIndex = 31;
				break;
			case '6':
				charIndex = 32;
				break;
			case '7':
				charIndex = 33;
				break;
			case '8':
				charIndex = 34;
				break;
			case '9':
				charIndex = 35;
				break;
			case '!':
				charIndex = 36;
				break;
			case '?':
				charIndex = 37;
				break;
			case '#':
				charIndex = 38;
				break;
			case '+':
				charIndex = 39;
				break;
			case '-':
				charIndex = 40;
				break;
			case '$':
				charIndex = 41;
				break;
			case ' ':
				charIndex = 42;
				break;
			case '(':
				charIndex = 43;
				break;
			case ')':
				charIndex = 44;
				break;
			case '.':
				charIndex = 45;
				break;
			case '\'':
				charIndex = 46;
				break;
			case '\n':
			case '\r':
				currentX = 0;
				++currentY;
				makeChar = false;
				iOffset++;
				break;
			default:
				charIndex = 37;//replace unknown characters with a ?
				break;
			}

			if (makeChar)
			{
				vertices[(i - iOffset) * 4 + 0] = { minWidth + (currentX * 1.1f), maxHeight - (currentY * 1.1f), 0.0f, color, textureWidthPerCharacter, 1.0f };//BL
				vertices[(i - iOffset) * 4 + 1] = { minWidth + (currentX * 1.1f) + 1, maxHeight - (currentY * 1.1f), 0.0f, color, textureWidthPerCharacter, 1.0f };//BR
				vertices[(i - iOffset) * 4 + 2] = { minWidth + (currentX * 1.1f), maxHeight - (currentY * 1.1f) + 1.0f, 0.0f, color, textureWidthPerCharacter, 0.0f };//TL
				vertices[(i - iOffset) * 4 + 3] = { minWidth + (currentX * 1.1f) + 1, maxHeight - (currentY * 1.1f) + 1.0f, 0.0f, color, textureWidthPerCharacter, 0.0f };//TR

				indices[(i - iOffset) * 6 + 0] = (i - iOffset) * 4 + 0;
				indices[(i - iOffset) * 6 + 1] = (i - iOffset) * 4 + 1;
				indices[(i - iOffset) * 6 + 2] = (i - iOffset) * 4 + 2;//BL->BR->TL
				indices[(i - iOffset) * 6 + 3] = (i - iOffset) * 4 + 2;
				indices[(i - iOffset) * 6 + 4] = (i - iOffset) * 4 + 1;
				indices[(i - iOffset) * 6 + 5] = (i - iOffset) * 4 + 3;//TL->BR->TR

				vertices[(i - iOffset) * 4 + 0].tu *= charIndex;
				vertices[(i - iOffset) * 4 + 1].tu *= charIndex;
				vertices[(i - iOffset) * 4 + 2].tu *= charIndex;
				vertices[(i - iOffset) * 4 + 3].tu *= charIndex;

				vertices[(i - iOffset) * 4 + 1].tu += textureWidthPerCharacter;
				vertices[(i - iOffset) * 4 + 3].tu += textureWidthPerCharacter;
				++currentX;
			}
		}

		VertexBufferWrapper* v_buffer = CreateColoredVertexBuffer(vertices, characters * 4);
		IndexBufferWrapper* i_buffer = CreateIndexBuffer(indices, characters * 6);

		Material mat;
		mat.texture = fontTexture;
		mat.ambient = { 1.0f, 1.0f, 1.0f };
		mat.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		mat.emissive = { 1.0f, 1.0f, 1.0f };
		mat.specular = { 1.0f, 1.0f, 1.0f };
		mat.power = 10.0f;
		SetMaterial(&mat);
		DrawIndexedVertexBuffer(v_buffer, i_buffer, characters * 4, characters * 2);

		delete[] vertices;
		delete[] indices;
		delete v_buffer;
		delete i_buffer;
	}
}