#include "DirectXRenderer.h"
#include "CustomD3DVertex.h"
#include "BinaryData.h"

Renderer::DirectXRenderer::DirectXRenderer()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
	g_pD3D = NULL;
	g_pd3dDevice = NULL;
	matrixCache = new D3DXMATRIX();
}

Renderer::DirectXRenderer::~DirectXRenderer()
{
	if (g_pd3dDevice != NULL)
	{
		g_pd3dDevice->Release();
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
	}
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}

void Renderer::DirectXRenderer::InitD3D(HWND hWnd)
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
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		logger->Log(Logger::ERR, "Failed to instantiate Direct3D9 CreateDevice");
		return;
	}
}

void Renderer::DirectXRenderer::SetDefaultRenderStates()
{
	this->g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//Counter Clockwise Cullmode
	this->g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE); //Z buffer on
	this->g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true); //Turn Alphablending on
	this->g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //Type alphablending
	this->g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //Type alphablending
};

void Renderer::DirectXRenderer::SetRenderState(PENGINERENDERSTATETYPE* state, PENGINEDWORD* dword)
{
	this->g_pd3dDevice->SetRenderState(static_cast<D3DRENDERSTATETYPE>(*state), static_cast<DWORD>(*dword));
}

void Renderer::DirectXRenderer::SetActiveCamera(CameraData camera)
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

void Renderer::DirectXRenderer::SetProjectionMatrix(PEngineMatrix* projectionMatrix)
{
	SetMatrixCache(projectionMatrix);
	this->g_pd3dDevice->SetTransform(D3DTS_PROJECTION, matrixCache);
}

void Renderer::DirectXRenderer::SetProjectionMatrix(float FOV, float farClippingPlane)
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

void Renderer::DirectXRenderer::BeginScene()
{
	this->g_pd3dDevice->BeginScene();
}

void Renderer::DirectXRenderer::ClearScene(PENGINEDWORD* count, PENGINEDWORD* flags, PENGINECOLOR* color, float z, PENGINEDWORD* stencil)
{
	this->g_pd3dDevice->Clear(*count, NULL, *flags, *color, z, *stencil);
}

void Renderer::DirectXRenderer::ClearScene(unsigned long count, unsigned long flags, Resource::RGBAColor color, float z, unsigned long stencil){
	flags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
	g_pd3dDevice->Clear(PENGINEDWORD(count), NULL, PENGINEDWORD(flags),
		D3DCOLOR_COLORVALUE(color.r, color.g, color.b, color.a), z, PENGINEDWORD(stencil));
}

void Renderer::DirectXRenderer::PresentScene(HWND hWnd)
{
	this->g_pd3dDevice->Present(NULL, NULL, hWnd, NULL);
}

void Renderer::DirectXRenderer::EndScene()
{
	this->g_pd3dDevice->EndScene();
}

void Renderer::DirectXRenderer::CreateVertexBuffer(int heightmapvertex, PENGINEDWORD* usage, PENGINEDWORD* fvf, PENGINEPOOL* pool, VertexBufferWrapper* vertexbuffer, HANDLE handle)
{
	this->g_pd3dDevice->CreateVertexBuffer(heightmapvertex, *usage, *fvf, static_cast<D3DPOOL>(*pool), vertexbuffer->GetVertexBuffer(), &handle);
};

void Renderer::DirectXRenderer::CreateIndexBuffer(int length, PENGINEDWORD* usage, PENGINEFORMAT* format, PENGINEPOOL* pool, IndexBufferWrapper* Indexbuffer, HANDLE* handle)
{
	this->g_pd3dDevice->CreateIndexBuffer(length, *usage, static_cast<D3DFORMAT>(*format), static_cast<D3DPOOL>(*pool), Indexbuffer->GetIndexBuffer(), NULL);
}

void Renderer::DirectXRenderer::SetMaterial(MaterialWrapper* wrapper)
{
	g_pd3dDevice->SetMaterial(wrapper->GetMaterial());
}

void Renderer::DirectXRenderer::SetTexture(TextureWrapper* wrapper)
{
	g_pd3dDevice->SetTexture(0, *wrapper->GetTexture());
}

void Renderer::DirectXRenderer::SetFvF(PENGINEDWORD* fvf)
{
	g_pd3dDevice->SetFVF(*fvf);
}

void Renderer::DirectXRenderer::DrawPrimitive(Resource::Mesh mesh)
{
	//g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh.vertices.size, 0, mesh.faceDefinitions.size * 3);
}

void Renderer::DirectXRenderer::DrawSubset(MeshWrapper* wrapper, int subset)
{
	(*wrapper->GetMesh())->DrawSubset(subset);
}

//??
void Renderer::DirectXRenderer::SetStreamSource() //??
{

}

void Renderer::DirectXRenderer::SetIndices() //??
{

}

LPDIRECT3DDEVICE9* Renderer::DirectXRenderer::GetDevice()
{
	return &g_pd3dDevice;
}

void Renderer::DirectXRenderer::Draw(Resource::Mesh* mesh)
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
}

void Renderer::DirectXRenderer::SetTexture(Resource::BinaryData* texture)
{
	if (textureCache.find(texture) == textureCache.end())
	{
		logger->Log(Logger::DEBUG, "Texture \"" + texture->fileName + "\" not converted to LPDIRECT3DTEXTURE9 yet.");
		LPDIRECT3DTEXTURE9 d3DTexture;

		D3DXCreateTextureFromFileInMemory(g_pd3dDevice, texture->rawData, texture->size, &d3DTexture);
		textureCache[texture] = d3DTexture;
		logger->Log(Logger::DEBUG, "Texture \"" + texture->fileName + "\" converted to LPDIRECT3DTEXTURE9.");
	}
	g_pd3dDevice->SetTexture(0, textureCache[texture]);
}

void Renderer::DirectXRenderer::SetMaterial(Resource::Material* material)
{
	D3DMATERIAL9 mat;
	mat.Ambient.r = material->ambientColor.r;
	mat.Ambient.g = material->ambientColor.g;
	mat.Ambient.b = material->ambientColor.b;

	mat.Diffuse.r = material->diffuseColor.r;
	mat.Diffuse.g = material->diffuseColor.g;
	mat.Diffuse.b = material->diffuseColor.b;

	mat.Specular.r = material->SpecularColor.r;
	mat.Specular.g = material->SpecularColor.g;
	mat.Specular.b = material->SpecularColor.b;
	mat.Power = material->specularWeight;

	g_pd3dDevice->SetMaterial(&mat);
}

void Renderer::DirectXRenderer::SetActiveMatrix(PEngineMatrix* matrix)
{
	SetMatrixCache(matrix);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, matrixCache);
}

void Renderer::DirectXRenderer::SetLights()
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
	g_pd3dDevice->SetLight(0, &light);
	g_pd3dDevice->LightEnable(0, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// Finally, turn on some ambient light.
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

	g_pd3dDevice->SetMaterial(&material);    // set the globably-used material to &material
}

void Renderer::DirectXRenderer::SetMatrixCache(PEngineMatrix* matrix)
{
	matrixCache = (D3DXMATRIX*)matrix;;
}