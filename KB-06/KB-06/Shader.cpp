#include "Shader.h"

namespace pengine
{
	Shader::Shader()
	{

	}

	Shader::~Shader()
	{

	}



	void Shader::DrawShader(Renderer* renderer)
	{
		(*((DirectXRenderer*)renderer)->GetDevice())->SetVertexDeclaration(g_pVertexDeclaration);
		(*((DirectXRenderer*)renderer)->GetDevice())->SetVertexShader(g_pVertexShader);
		
	}

	LPDIRECT3DVERTEXSHADER9 Shader::GetVertexShader()
	{
		return g_pVertexShader;
	}

	PDIRECT3DPIXELSHADER9 Shader::GetPixelShader()
	{
		return g_pPixelShader;
	}

	LPDIRECT3DVERTEXDECLARATION9 Shader::GetVertexDeclaration()
	{
		return g_pVertexDeclaration;
	}

	LPD3DXCONSTANTTABLE Shader::GetConstantTable()
	{
		return g_pConstantTable;
	}

	void Shader::SetVertexShader(LPDIRECT3DVERTEXSHADER9 NewVertexShader)
	{
		g_pVertexShader = NewVertexShader;
	}

	void Shader::SetPixelShader(PDIRECT3DPIXELSHADER9 NewPixelShader)
	{
		g_pPixelShader = NewPixelShader;
	}

	void Shader::SetVertexDeclaration(LPDIRECT3DVERTEXDECLARATION9 NewVertexDeclaration)
	{
		g_pVertexDeclaration = NewVertexDeclaration;
	}

	void Shader::SetConstantTable(LPD3DXCONSTANTTABLE NewConstantTable)
	{
		g_pConstantTable = NewConstantTable;
	}

}