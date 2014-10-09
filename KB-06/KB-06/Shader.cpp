#include "Shader.h"

namespace pengine
{
	Shader::Shader()
	{

	}

	Shader::~Shader()
	{

	}

	void Shader::InitShader(Renderer* renderer)
	{
		HRESULT hr;

		// Create and initialize index buffer
		WORD* pIndices;

		(*((DirectXRenderer*)renderer)->GetDevice())->CreateIndexBuffer(g_dwNumIndices * sizeof(WORD),
			0, D3DFMT_INDEX16,
			D3DPOOL_DEFAULT, &g_pIB, NULL);


		g_pIB->Lock(0, 0, (void**)&pIndices, 0);


		DWORD y;
		for (y = 1; y < VERTS_PER_EDGE; y++)
		{
			for (DWORD x = 1; x < VERTS_PER_EDGE; x++)
			{
				*pIndices++ = (WORD)((y - 1) * VERTS_PER_EDGE + (x - 1));
				*pIndices++ = (WORD)((y - 0) * VERTS_PER_EDGE + (x - 1));
				*pIndices++ = (WORD)((y - 1) * VERTS_PER_EDGE + (x - 0));

				*pIndices++ = (WORD)((y - 1) * VERTS_PER_EDGE + (x - 0));
				*pIndices++ = (WORD)((y - 0) * VERTS_PER_EDGE + (x - 1));
				*pIndices++ = (WORD)((y - 0) * VERTS_PER_EDGE + (x - 0));
			}
		}

		g_pIB->Unlock();

		// Create and initialize vertex buffer
		(*((DirectXRenderer*)renderer)->GetDevice())->CreateVertexBuffer(g_dwNumVertices * sizeof(D3DXVECTOR2),
			0, 0,
			D3DPOOL_DEFAULT, &g_pVB, NULL);

		D3DXVECTOR2* pVertices;
		g_pVB->Lock(0, 0, (void**)&pVertices, 0);

		for (y = 0; y < VERTS_PER_EDGE; y++)
		{
			for (DWORD x = 0; x < VERTS_PER_EDGE; x++)
			{
				*pVertices++ = D3DXVECTOR2(((float)x / (float)(VERTS_PER_EDGE - 1) - 0.5f) * D3DX_PI,
					((float)y / (float)(VERTS_PER_EDGE - 1) - 0.5f) * D3DX_PI);
			}
		}

		hr = g_pVB->Unlock();







		// Create vertex shader
		
		LPD3DXBUFFER pCode;

		D3DVERTEXELEMENT9 decl[] =
		{
			{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			D3DDECL_END()
		};

		((*((DirectXRenderer*)renderer)->GetDevice())->CreateVertexDeclaration(decl, &g_pVertexDeclaration));

		// Find the vertex shader file
		//DXUTFindDXSDKMediaFileCch(strPath, 512, L"HLSLwithoutEffects.vsh");



		DWORD dwShaderFlags = 0;

		LPCWSTR strPath;

		std::wstring strPathNew = L"resources/HLSLwithoutEffects.vsh";

		strPath = strPathNew.c_str();

		// Assemble the vertex shader from the file
		D3DXCompileShaderFromFile(strPath, NULL, NULL, "Ripple",
			"vs_2_0", dwShaderFlags, &pCode,
			NULL, &g_pConstantTable);

		// Create the vertex shader
		hr = (*((DirectXRenderer*)renderer)->GetDevice())->CreateVertexShader((DWORD*)pCode->GetBufferPointer(),
			&g_pVertexShader);
		pCode->Release();
		if (FAILED(hr));
			//return DXTRACE_ERR(TEXT("CreateVertexShader"), hr);
	}

	void Shader::DrawShader(Renderer* renderer)
	{
		(*((DirectXRenderer*)renderer)->GetDevice())->SetVertexDeclaration(g_pVertexDeclaration);
		(*((DirectXRenderer*)renderer)->GetDevice())->SetVertexShader(g_pVertexShader);
		(*((DirectXRenderer*)renderer)->GetDevice())->SetStreamSource(0, g_pVB, 0, sizeof(D3DXVECTOR2));
		(*((DirectXRenderer*)renderer)->GetDevice())->SetIndices(g_pIB);

		(*((DirectXRenderer*)renderer)->GetDevice())->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_dwNumVertices,
			0, g_dwNumIndices / 3);
	}
}