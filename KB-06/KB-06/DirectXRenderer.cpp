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