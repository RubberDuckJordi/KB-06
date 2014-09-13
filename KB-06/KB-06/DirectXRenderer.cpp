#include "DirectXRenderer.h"
#include "CustomD3DVertex.h"

Renderer::DirectXRenderer::DirectXRenderer()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
	g_pD3D = NULL;
	g_pd3dDevice = NULL;
};

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
};

void Renderer::DirectXRenderer::InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		logger->Log(Logger::Logger::ERR, "Failed to instantiate Direct3DCreate9");
		return;
		//return E_FAIL; -> when switching from void to H_RESULT return type
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
		logger->Log(Logger::Logger::ERR, "Failed to instantiate Direct3D9 CreateDevice");
		return;
		//return E_FAIL; -> when switching from void to H_RESULT return type
	}

	//return S_OK; -> when switching from void to H_RESULT return type
};

void Renderer::DirectXRenderer::SetRenderState()
{
	this->g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//Counter Clockwise Cullmode
	this->g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE); //No lightning
	this->g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE); //Z buffer on
	this->g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff); //Ambient is white
	this->g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true); //Turn Alphablending on
	this->g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //Type alphablending
	this->g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //Type alphablending
};

//Matrixen
void Renderer::DirectXRenderer::SetWorldMatrix(MatrixWrapper* WorldMatrix)
{
	this->g_pd3dDevice->SetTransform(D3DTS_WORLD, &(WorldMatrix->GetMatrix()));
};

void Renderer::DirectXRenderer::SetViewMatrix(MatrixWrapper* ViewMatrix)
{
	this->g_pd3dDevice->SetTransform(D3DTS_VIEW, &(ViewMatrix->GetMatrix()));
};

void Renderer::DirectXRenderer::SetProjectionMatrix(MatrixWrapper* ProjectionMatrix)
{
	this->g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &(ProjectionMatrix->GetMatrix()));
};


//Scene
void Renderer::DirectXRenderer::BeginScene()
{
	this->g_pd3dDevice->BeginScene();
};

void Renderer::DirectXRenderer::ClearScene(DWORDWrapper* count, DWORDWrapper* flags, ColorWrapper* color, float z, DWORDWrapper* stencil)
{

	this->g_pd3dDevice->Clear(count->GetDWORD(), NULL, flags->GetDWORD(), color->GetColor(), z, stencil->GetDWORD());

};

void Renderer::DirectXRenderer::PresentScene(HWND hWnd)
{
	this->g_pd3dDevice->Present(NULL, NULL, hWnd, NULL);
};

void Renderer::DirectXRenderer::StopScene()
{
	this->g_pd3dDevice->EndScene();
};


//Buffers
void Renderer::DirectXRenderer::CreateVertexBuffer(int heightmapvertex, DWORDWrapper* usage, DWORDWrapper* fvf, PoolWrapper* pool, VertexBufferWrapper* vertexbuffer, HANDLE handle)
{
	this->g_pd3dDevice->CreateVertexBuffer(heightmapvertex, usage->GetDWORD(), fvf->GetDWORD(), pool->GetPool(), vertexbuffer->GetVertexBuffer(), &handle);
};

void Renderer::DirectXRenderer::CreateIndexBuffer(int length, DWORDWrapper* usage, FormatWrapper* format, PoolWrapper* pool, IndexBufferWrapper* Indexbuffer, HANDLE* handle)
{
	this->g_pd3dDevice->CreateIndexBuffer(length, usage->GetDWORD(), format->GetFormat(), pool->GetPool(), Indexbuffer->GetIndexBuffer(), NULL);
};

//Set stuff
void Renderer::DirectXRenderer::SetMaterial(MaterialWrapper* wrapper)
{
	g_pd3dDevice->SetMaterial(&wrapper->GetMaterial());
	//return g_pd3dDevice->SetMaterial(&wrapper->GetMaterial()); when H_RESULT as return type
};

void Renderer::DirectXRenderer::SetTexture(TextureWrapper* wrapper)
{
	g_pd3dDevice->SetTexture(0, wrapper->GetTexture());
	// return g_pd3dDevice->SetTexture(0, wrapper->GetTexture()); when H_RESULT as return type
};

void Renderer::DirectXRenderer::SetFvF(DWORDWrapper* fvf)
{
	g_pd3dDevice->SetFVF(fvf->GetDWORD());
};

void Renderer::DirectXRenderer::SetTransform(int type, MatrixWrapper* wrapper)
{
	g_pd3dDevice->SetTransform((D3DTRANSFORMSTATETYPE)type, &(wrapper->GetMatrix()));
};

//Draw functions
void Renderer::DirectXRenderer::DrawPrimitive(Resource::Mesh mesh)
{
	//g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh.vertices.size, 0, mesh.faceDefinitions.size * 3);
};

void Renderer::DirectXRenderer::DrawSubset(MeshWrapper* wrapper, int subset)
{
	(wrapper->GetMesh())->DrawSubset(subset);
};

//??
void Renderer::DirectXRenderer::SetStreamSource() //??
{

};

void Renderer::DirectXRenderer::SetIndices() //??
{

};

//GetDevice
LPDIRECT3DDEVICE9* Renderer::DirectXRenderer::GetDevice()
{
	return &g_pd3dDevice;
};

void Renderer::DirectXRenderer::Draw(Resource::MeshResource* mesh){
	if (meshCache.find(mesh) == meshCache.end()){
		logger->Log(Logger::Logger::DEBUG, "Mesh not converted to LPD3DXMESH yet.");

		LPD3DXMESH d3dMesh;
		if (FAILED(D3DXCreateMeshFVF(mesh->GetFaceDefinitions()->size(), mesh->GetVertices()->size(), D3DXMESH_MANAGED, D3DFVF_MESH, g_pd3dDevice, &d3dMesh))){
			logger->Log(Logger::Logger::ERR, "Failed to create a D3DXCreateMeshFVF");
		}

		const int amountOfVertices = mesh->GetVertices()->size();
		D3DXVECTOR3 vertices[16384];
		logger->Log(Logger::Logger::WARNING, "@todo; Remove limit to 16384 vertices.");
		for (unsigned int i = 0; i < mesh->GetVertices()->size(); ++i){
			vertices[i] = D3DXVECTOR3(mesh->GetVertices()->at(i).x, mesh->GetVertices()->at(i).y, mesh->GetVertices()->at(i).z);
		}

		const int amountOfIndices = mesh->GetFaceDefinitions()->size();
		unsigned int* indices = new unsigned int[amountOfIndices];
		int index = -1;
		for (unsigned int i = 0; i < mesh->GetVertices()->size(); ++i){
			indices[++index] = mesh->GetFaceDefinitions()->at(i).v1;
			indices[++index] = mesh->GetFaceDefinitions()->at(i).v2;
			indices[++index] = mesh->GetFaceDefinitions()->at(i).v3;
		}

		//create buffers
		LPDIRECT3DVERTEXBUFFER9 v_buffer;
		g_pd3dDevice->CreateVertexBuffer(amountOfVertices*sizeof(D3DXVECTOR3),
			0,
			D3DFVF_MESH,
			D3DPOOL_MANAGED,
			&v_buffer,
			NULL);

		LPDIRECT3DINDEXBUFFER9 i_buffer;
		g_pd3dDevice->CreateIndexBuffer(amountOfIndices*sizeof(unsigned int),
			0,
			D3DFMT_INDEX32,
			D3DPOOL_MANAGED,
			&i_buffer,
			NULL);

		VOID* pVoid;
		// lock v_buffer and load the vertices into it
		v_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, vertices, amountOfVertices*sizeof(D3DXVECTOR3));
		v_buffer->Unlock();
	
		// lock i_buffer and load the indices into it
		i_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, indices, amountOfIndices*sizeof(unsigned int));
		i_buffer->Unlock();
		meshCache[mesh] = d3dMesh;
		logger->Log(Logger::Logger::DEBUG, "Mesh converted to LPD3DXMESH.");
	}

	logger->Log(Logger::Logger::WARNING, "@todo; specify subsets.");
	meshCache[mesh]->DrawSubset(0);
}
