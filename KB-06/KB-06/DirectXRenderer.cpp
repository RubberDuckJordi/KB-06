#include "DirectXRenderer.h"
#include "CustomD3DVertex.h"
#include "BinaryData.h"

namespace pengine
{
	DirectXRenderer::DirectXRenderer()
	{
		logger = LoggerPool::GetInstance().GetLogger();
		g_pD3D = NULL;
		g_pd3dDevice = NULL;
		matrixCache = new D3DXMATRIX();
		d2dBmp = NULL;
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
		LoggerPool::GetInstance().ReturnLogger(logger);
	}

	void DirectXRenderer::CreateD2DFactory()
	{
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);
	}

	void DirectXRenderer::CreateRenderTarget(HWND hWnd)
	{
		D3DXCreateTexture(g_pd3dDevice, 500, 500, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &surfaceTexture); //LPDIRECT3DTEXTURE9
		surfaceTexture->GetSurfaceLevel(0, &surfaceLevel); //IDirect3DSurface9
		g_pd3dDevice->GetRenderTarget(0, &backbuffer); //IDirect3DSurface9

		GetClientRect(hWnd, &rectangle);

		D2D1_SIZE_U size = D2D1::SizeU(rectangle.right - rectangle.left, rectangle.bottom - rectangle.top);

		d2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&d2dRenderTarget
			);
	}

	void DirectXRenderer::CreateWICImagingFactory()
	{
		CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, __uuidof(IWICImagingFactory), (void**)(&iwicFactory));
	}

	void DirectXRenderer::CreateDecoder(std::string path)
	{
		size_t newSize = strlen(path.c_str()) + 1;

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
			);
	}

	void DirectXRenderer::CreateFormatConverter()
	{
		iwicFactory->CreateFormatConverter(&iwicFormatConverter);
	}

	void DirectXRenderer::GetBitmapFrame()
	{
		bitmapFrame = NULL;

		iwicBmpDecoder->GetFrame(0, &bitmapFrame);
	}

	void DirectXRenderer::InitializeBMP()
	{
		iwicFormatConverter->Initialize(bitmapFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
	}

	void DirectXRenderer::CreateBitmapFromWIC()
	{
		d2dRenderTarget->CreateBitmapFromWicBitmap(iwicFormatConverter, NULL, &d2dBmp);
	}

	void DirectXRenderer::D2DDraw()
	{
		g_pd3dDevice->SetRenderTarget(0, surfaceLevel);
		d2dRenderTarget->BeginDraw();
		D2D1_RECT_F test = D2D1::RectF(0, 0, 200, 200);
		//d2dRenderTarget->DrawBitmap(d2dBmp, test);

		d2dRenderTarget->EndDraw();
		g_pd3dDevice->SetRenderTarget(0, backbuffer);
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
		// Set up our view matrix. A view matrix can be defined given an eye point,
		// a point to lookat, and a direction for which way is up. Here, we set the
		// eye 0.5 units back along the z-axis and up 0 units, look at the 
		// origin + 0.5 on the z-axis, and define "up" to be in the y-direction.

		D3DXVECTOR3 vEyePt(camera.x, camera.y, camera.z);
		D3DXVECTOR3 vLookatPt(camera.lookAtX, camera.lookAtY, camera.lookAtZ);
		D3DXVECTOR3 vUpVec(camera.upVecX, camera.upVecY, camera.upVecZ);
		if (orthographic)
		{
			D3DXMatrixOrthoLH(matrixCache, 1.0f, 1.0f, 1.0f, 2.0f);
		} 
		else
		{
			D3DXMatrixLookAtLH(matrixCache, &vEyePt, &vLookatPt, &vUpVec);
		}
		g_pd3dDevice->SetTransform(D3DTS_VIEW, matrixCache);
	}

	void DirectXRenderer::SetProjectionMatrix(PEngineMatrix* projectionMatrix)
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
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, FOV, 1.0f, 1.0f, 1000.0f);
		g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
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

	//??
	void DirectXRenderer::SetStreamSource() //??
	{

	}

	void DirectXRenderer::SetIndices() //??
	{

	}

	LPDIRECT3DDEVICE9* DirectXRenderer::GetDevice()
	{
		return &g_pd3dDevice;
	}

	void DirectXRenderer::SetActiveMatrix(PEngineMatrix* matrix)
	{
		SetMatrixCache(matrix);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, matrixCache);
	}

	void DirectXRenderer::SetLights()
	{
		//D3DXVECTOR3 vecDir;
		//D3DLIGHT9 light;
		//D3DMATERIAL9 material;    // create the material struct
		//light.Type = D3DLIGHT_DIRECTIONAL;
		//light.Diffuse.r = 1.0f;
		//light.Diffuse.g = 1.0f;
		//light.Diffuse.b = 1.0f;
		//vecDir = D3DXVECTOR3(cosf(timeGetTime() / 350.0f), 1.0f, sinf(timeGetTime() / 350.0f));
		//D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

		//light.Range = 1000.0f;
		//light.Direction = vecDir;

		//g_pd3dDevice->SetLight(0, &light);
		//g_pd3dDevice->LightEnable(0, true);
		g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);
		// Finally, turn on some ambient light.
		g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
		//material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
		//material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

		//g_pd3dDevice->SetMaterial(&material);    // set the globably-used material to &material

		/*//Turn on ambient lighting
		g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		/*g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);*/
	}

	void DirectXRenderer::SetMatrixCache(PEngineMatrix* matrix)
	{
		//matrixCache = (D3DXMATRIX*)matrix;;
		matrixCache->_11 = matrix->_11;
		matrixCache->_12 = matrix->_12;
		matrixCache->_13 = matrix->_13;
		matrixCache->_14 = matrix->_14;

		matrixCache->_21 = matrix->_21;
		matrixCache->_22 = matrix->_22;
		matrixCache->_23 = matrix->_23;
		matrixCache->_24 = matrix->_24;

		matrixCache->_31 = matrix->_31;
		matrixCache->_32 = matrix->_32;
		matrixCache->_33 = matrix->_33;
		matrixCache->_34 = matrix->_34;

		matrixCache->_41 = matrix->_41;
		matrixCache->_42 = matrix->_42;
		matrixCache->_43 = matrix->_43;
		matrixCache->_44 = matrix->_44;

	}

	VertexBufferWrapper* DirectXRenderer::CreateVertexBuffer(D3DCustomVertex* p_vertices, int amountOfVertices, int fvf)
	{
		IDirect3DVertexBuffer9** buffer = new LPDIRECT3DVERTEXBUFFER9();
		VertexBufferWrapper* vertexBufferWrapper = new VertexBufferWrapper();
		vertexBufferWrapper->SetVertexBuffer(buffer);

		if (FAILED(g_pd3dDevice->CreateVertexBuffer(amountOfVertices * sizeof(D3DCustomVertex),
			0, fvf, D3DPOOL_DEFAULT, vertexBufferWrapper->GetVertexBuffer(), NULL)))
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
		g_pd3dDevice->SetStreamSource(0, *vertexBuffer->GetVertexBuffer(), 0, sizeof(D3DCustomVertex));
		g_pd3dDevice->SetFVF(D3DCustomVertexFVF);
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, amountOfIndices / 3);
	}

	void DirectXRenderer::DrawIndexedVertexBuffer(VertexBufferWrapper* v_buffer, IndexBufferWrapper* i_buffer, int amountOfVertices)
	{
		g_pd3dDevice->SetStreamSource(0, *v_buffer->GetVertexBuffer(), 0, sizeof(D3DCustomVertex));
		g_pd3dDevice->SetFVF(D3DCustomVertexFVF);
		g_pd3dDevice->SetIndices(*i_buffer->GetIndexBuffer());
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,// PrimitiveType
			0,// BaseVertexIndex
			0,// MinIndex
			amountOfVertices,// NumVertices
			0,// StartIndex
			12);// PrimitiveCount
	}

	void DirectXRenderer::ActivateRenderingToTexture(int tWidth, int tHeight)
	{
		if (RenderTexture != NULL)
		{
			RenderTexture->Release();
			RenderTexture = NULL;
		}
		if (RenderSurface != NULL)
		{
			RenderSurface->Release();
			RenderSurface = NULL;
		}
		//Create our render target, making it the same size as the screen. Usually DX would resize it to a 2^x size, but
		//we're creating it as a "D3DUSAGE_RENDERTARGET" so it can set it the same as the screen's size.
		g_pd3dDevice->CreateTexture(tWidth, tHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &RenderTexture, NULL);
		//Here we grab a pointer to the surface so we can pass it to SetRenderTarget
		RenderTexture->GetSurfaceLevel(0, &RenderSurface);

		//Change our rendering target to our created surface.
		g_pd3dDevice->SetRenderTarget(0, RenderSurface);
		//Clear it too, with a different color to make sure we're getting it.
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0xFF000000, 1.0f, 0);//no alpha please (for now)
		//Start the renderer to render to the texture scene
		g_pd3dDevice->BeginScene();//not sure if this has an effect or not
	}

	void DirectXRenderer::DeactivateRenderingToTexture()
	{
		//We're done rendering to the texture scene
		g_pd3dDevice->EndScene();//not sure if this has an effect or not
		//D3DXSaveTextureToFile(L"test.bmp", D3DXIFF_BMP, RenderTexture, NULL);
		//And we change back to the actual backbuffer
		g_pd3dDevice->SetRenderTarget(0, MainSurface);
	}

	void DirectXRenderer::SetTextureToRenderedTexture()
	{
		//Set the texture we're using to the texture we just rendered to. (Neat huh? :D)
		g_pd3dDevice->SetTexture(0, RenderTexture);
	}
}