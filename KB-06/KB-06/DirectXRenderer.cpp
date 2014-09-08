#include "DirectXRenderer.h"

DirectXRenderer::DirectXRenderer()
{
	g_pD3D = NULL;
	g_pd3dDevice = NULL;
};
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
};

void DirectXRenderer::InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
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
		return;
		//return E_FAIL; -> when switching from void to H_RESULT return type
	}

	//return S_OK; -> when switching from void to H_RESULT return type
};

void DirectXRenderer::SetRenderState()
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
void DirectXRenderer::SetWorldMatrix()
{

};

void DirectXRenderer::SetViewMatrix()
{

};

void DirectXRenderer::SetProjectionMatrix()
{

};

//Scene
void DirectXRenderer::BeginScene()
{

};

void DirectXRenderer::ClearScene()
{

};

void DirectXRenderer::PresentScene()
{

};

void DirectXRenderer::StopScene()
{

};


//Buffers
void DirectXRenderer::CreateVertexBuffer()
{

};

void DirectXRenderer::CreateIndexBuffer()
{

};

//Set stuff
void DirectXRenderer::SetMaterial()
{

};

void DirectXRenderer::SetTexture()
{

};

void DirectXRenderer::SetFvF()
{

};

void DirectXRenderer::SetTransform()
{

};

//Draw functions
void DirectXRenderer::DrawPrimitive()
{

};

void DirectXRenderer::DrawSubset()
{

};

//??
void DirectXRenderer::SetStreamSource() //??
{

};

void DirectXRenderer::SetIndices() //??
{

};

//GetDevice
void DirectXRenderer::GetDevice()
{

};
