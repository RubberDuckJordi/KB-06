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
		void DrawShader(Renderer* renderer);

		LPDIRECT3DVERTEXSHADER9 GetVertexShader();
		PDIRECT3DPIXELSHADER9 GetPixelShader();
		LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclaration();
		LPD3DXCONSTANTTABLE GetConstantTable();

		void SetVertexShader(LPDIRECT3DVERTEXSHADER9 NewVertexShader);
		void SetPixelShader(PDIRECT3DPIXELSHADER9 NewPixelShader);
		void SetVertexDeclaration(LPDIRECT3DVERTEXDECLARATION9 NewVertexDeclaration);
		void SetConstantTable(LPD3DXCONSTANTTABLE NewConstantTable);
		
	private:
		
		LPDIRECT3DVERTEXSHADER9         g_pVertexShader;
		PDIRECT3DPIXELSHADER9			g_pPixelShader;
		LPDIRECT3DVERTEXDECLARATION9    g_pVertexDeclaration;
		LPD3DXCONSTANTTABLE				g_pConstantTable;
		
	};
}


#endif