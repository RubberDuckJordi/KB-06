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
		d2dRenderTarget->BeginDraw();
		D2D1_RECT_F test = D2D1::RectF(0, 0, 200, 200);
		d2dRenderTarget->DrawBitmap(d2dBmp, test);
		d2dRenderTarget->EndDraw();
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
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		//d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;//The higher you can set this, the more accurate the z-buffer is, current seems to be the highest working.
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		//d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;//The higher you can set this, the more accurate the z-buffer is, current seems to be the highest working.

		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pd3dDevice)))
		{
			logger->Log(Logger::ERR, "Failed to instantiate Direct3D9 CreateDevice");
			return;
		}
	}

	void DirectXRenderer::SetDefaultRenderStates()
	{
		this->g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//Counter Clockwise Cullmode
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

	void DirectXRenderer::SetActiveCamera(CameraData camera)
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
	}

	void DirectXRenderer::SetTexture(TextureWrapper* wrapper)
	{
		g_pd3dDevice->SetTexture(0, *wrapper->GetTexture());
	}

	void DirectXRenderer::SetFvF(PENGINEDWORD* fvf)
	{
		g_pd3dDevice->SetFVF(*fvf);
	}

	/*void DirectXRenderer::DrawPrimitive(Mesh mesh)
{
//g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh.vertices.size, 0, mesh.faceDefinitions.size * 3);
}*/

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

	/*void DirectXRenderer::Draw(Mesh* mesh)
{
if (meshCache.find(mesh) == meshCache.end())
{
logger->Log(Logger::DEBUG, "Mesh \"" + mesh->fileName + "\" not converted to LPD3DXMESH yet.");

LPD3DXMESH d3dMesh;
int	amountOfVertices = 0;
int amountOfIndices = 0;
for (unsigned int i = 0; i < mesh->subsets.size(); ++i)
{
amountOfVertices += mesh->subsets.at(i).vertices.size();
amountOfIndices += mesh->subsets.at(i).faceDefinitions.size();
}
if (FAILED(D3DXCreateMeshFVF(amountOfIndices, amountOfVertices, 0, D3DCustomVertexFVF, g_pd3dDevice, &d3dMesh)))
{
logger->Log(Logger::ERR, "Failed to create a D3DXCreateMeshFVF. Generating a cube");
D3DXCreateBox(g_pd3dDevice, 1.0f, 1.0f, 1.0f, &d3dMesh, NULL);
}
else
{
D3DCustomVertex* d3dVertices = new D3DCustomVertex[amountOfVertices];
unsigned short* indices = new unsigned short[amountOfIndices * 3];

int vertexCount = -1;
int indexCount = -1;
for (unsigned int i = 0; i < mesh->subsets.size(); ++i)
{
for (unsigned int j = 0; j < mesh->subsets.at(i).vertices.size(); ++j)
{
D3DCustomVertex newVertex;
newVertex.x = mesh->subsets.at(i).vertices.at(j).x;
newVertex.y = mesh->subsets.at(i).vertices.at(j).y;
newVertex.z = mesh->subsets.at(i).vertices.at(j).z;
newVertex.tu = mesh->subsets.at(i).textureCoordinates.at(j).u;
newVertex.tv = mesh->subsets.at(i).textureCoordinates.at(j).v;
d3dVertices[++vertexCount] = newVertex;
}
for (unsigned int j = 0; j < mesh->subsets.at(i).faceDefinitions.size(); ++j)
{
indices[++indexCount] = mesh->subsets.at(i).faceDefinitions.at(j).v1;
indices[++indexCount] = mesh->subsets.at(i).faceDefinitions.at(j).v2;
indices[++indexCount] = mesh->subsets.at(i).faceDefinitions.at(j).v3;
int test = 10;
}
}
VOID* pVoid;

LPDIRECT3DVERTEXBUFFER9 v_buffer;
d3dMesh->GetVertexBuffer(&v_buffer);
// lock v_buffer and load the vertices into it
v_buffer->Lock(0, 0, (void**)&pVoid, 0);
memcpy(pVoid, d3dVertices, amountOfVertices*sizeof(D3DCustomVertex));
v_buffer->Unlock();

LPDIRECT3DINDEXBUFFER9 i_buffer;
d3dMesh->GetIndexBuffer(&i_buffer);
// lock i_buffer and load the indices into it
i_buffer->Lock(0, 0, (void**)&pVoid, 0);
memcpy(pVoid, indices, amountOfIndices * 3 * sizeof(unsigned short));
i_buffer->Unlock();

logger->Log(Logger::DEBUG, "Mesh \"" + mesh->fileName + "\" converted to LPD3DXMESH.");

if (mesh->fileName == "resources/cubeClone.obj.mesh")
{
//D3DXCreateBox(g_pd3dDevice, 1.0f, 1.0f, 1.0f, &d3dMesh, NULL);
D3DXCreateSphere(g_pd3dDevice, 1.0f, 10, 10, &d3dMesh, NULL);
logger->Log(3, "The meow is great in this one.");
}
if (mesh->fileName == "resources/cubeCloneClone.obj.mesh")
{
D3DXCreateTeapot(g_pd3dDevice, &d3dMesh, NULL);
logger->Log(3, "The meow is greater in this one.");
}
}
meshCache[mesh] = d3dMesh;
//D3DXSaveMeshToX(L"test.x", d3dMesh, NULL, NULL, NULL, 0, 1); //save mesh to xfile to debug
}

for (unsigned int i = 0; i < mesh->subsets.size(); ++i){ // So we start at 1 instead of 0
SetMaterial(&mesh->subsets.at(i).defaultMaterial);
SetTexture(&mesh->subsets.at(i).defaultMaterial.defaultTexture);
meshCache[mesh]->DrawSubset(i);
}
}*/


	void DirectXRenderer::SetActiveMatrix(PEngineMatrix* matrix)
	{
		SetMatrixCache(matrix);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, matrixCache);
	}

	void DirectXRenderer::SetLights()
	{
		D3DXVECTOR3 vecDir;
		D3DLIGHT9 light;
		D3DMATERIAL9 material;    // create the material struct
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Diffuse.r = 1.0f;
		light.Diffuse.g = 1.0f;
		light.Diffuse.b = 1.0f;
		vecDir = D3DXVECTOR3(cosf(timeGetTime() / 350.0f),
			1.0f,
			sinf(timeGetTime() / 350.0f));
		D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

		light.Range = 1000.0f;
		light.Direction = vecDir;

		g_pd3dDevice->SetLight(0, &light);
		g_pd3dDevice->LightEnable(0, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		// Finally, turn on some ambient light.
		g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
		material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

		g_pd3dDevice->SetMaterial(&material);    // set the globably-used material to &material

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

	VertexBufferWrapper* DirectXRenderer::CreateVertexBuffer(D3DCustomVertex* p_vertices, int amountOfIndices, int fvf)
	{
		IDirect3DVertexBuffer9** buffer = new LPDIRECT3DVERTEXBUFFER9();
		VertexBufferWrapper* vertexBufferWrapper = new VertexBufferWrapper();
		vertexBufferWrapper->SetVertexBuffer(buffer);

		if (FAILED(g_pd3dDevice->CreateVertexBuffer(amountOfIndices * sizeof(D3DCustomVertex),
			0, fvf, D3DPOOL_DEFAULT, vertexBufferWrapper->GetVertexBuffer(), NULL)))
		{
			logger->Log(Logger::ERR, "DirectXRenderer::CreateVertexBuffer() vertexbuffer create failed");
		}

		void* verticesBuffer;
		int size = sizeof(D3DCustomVertex)*amountOfIndices;

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
}