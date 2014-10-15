#ifndef _PENGINE_SHADER_H_
#define _PENGINE_SHADER_H_

#include <d3dx9.h>
#include "Renderer.h"
#include "DirectXRenderer.h"
//#include "DXUT.h"

//#define VERTS_PER_EDGE 64

namespace pengine
{
	class Shader
	{
	public:
		Shader();
		~Shader();
		//void InitShader(Renderer* renderer);
		void SetShader(Renderer* renderer);

		IDirect3DVertexShader9* GetVertexShader();
		IDirect3DPixelShader9* GetPixelShader();
		IDirect3DVertexDeclaration9* GetVertexDeclaration();
		ID3DXConstantTable* GetVertexShaderConstantTable();
		ID3DXConstantTable* GetPixelShaderConstantTable();

		void SetVertexShader(IDirect3DVertexShader9* NewVertexShader);
		void SetPixelShader(IDirect3DPixelShader9* NewPixelShader);
		void SetVertexDeclaration(IDirect3DVertexDeclaration9* NewVertexDeclaration);
		void SetVertexShaderConstantTable(ID3DXConstantTable* NewConstantTable);
		void SetPixelShaderConstantTable(ID3DXConstantTable* NewConstantTable);
		
	private:
		
		IDirect3DVertexShader9*         g_pVertexShader;
		IDirect3DPixelShader9*			g_pPixelShader;
		IDirect3DVertexDeclaration9*    g_pVertexDeclaration;
		ID3DXConstantTable*				g_pVertexShaderConstantTable;
		ID3DXConstantTable*				g_pPixelShaderConstantTable;
		
	};
}


#endif