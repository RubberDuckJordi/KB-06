#include "Shader.h"

namespace pengine
{
	Shader::Shader()
	{

	}

	Shader::~Shader()
	{

	}



	void Shader::SetShader(Renderer* renderer)
	{
		if (g_pVertexDeclaration != NULL && g_pVertexShader != NULL)
		{
			(*((DirectXRenderer*)renderer)->GetDevice())->SetVertexDeclaration(g_pVertexDeclaration);
			(*((DirectXRenderer*)renderer)->GetDevice())->SetVertexShader(g_pVertexShader);
		}

		if (g_pPixelShader != NULL)
		{
			(*((DirectXRenderer*)renderer)->GetDevice())->SetPixelShader(g_pPixelShader);
		}
	}

	IDirect3DVertexShader9* Shader::GetVertexShader()
	{
		return g_pVertexShader;
	}

	IDirect3DPixelShader9* Shader::GetPixelShader()
	{
		return g_pPixelShader;
	}

	IDirect3DVertexDeclaration9* Shader::GetVertexDeclaration()
	{
		return g_pVertexDeclaration;
	}

	ID3DXConstantTable* Shader::GetConstantTable()
	{
		return g_pConstantTable;
	}

	void Shader::SetVertexShader(IDirect3DVertexShader9* NewVertexShader)
	{
		g_pVertexShader = NewVertexShader;
	}

	void Shader::SetPixelShader(IDirect3DPixelShader9* NewPixelShader)
	{
		g_pPixelShader = NewPixelShader;
	}

	void Shader::SetVertexDeclaration(IDirect3DVertexDeclaration9* NewVertexDeclaration)
	{
		g_pVertexDeclaration = NewVertexDeclaration;
	}

	void Shader::SetConstantTable(ID3DXConstantTable* NewConstantTable)
	{
		g_pConstantTable = NewConstantTable;
	}

}