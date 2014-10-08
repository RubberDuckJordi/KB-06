#ifndef _PENGINE_SHADER_H_
#define _PENGINE_SHADER_H_

#include <d3dx9.h>
#include "Renderer.h"
#include "DirectXRenderer.h"
//#include "DXUT.h"

#define VERTS_PER_EDGE 64

namespace pengine
{
	class Shader
	{
	public:
		Shader();
		~Shader();
		void InitShader(Renderer* renderer);
		void DrawShader(Renderer* renderer);
		
	private:
		LPDIRECT3DVERTEXBUFFER9         g_pVB = NULL;
		LPDIRECT3DINDEXBUFFER9          g_pIB = NULL;
		DWORD                           g_dwNumVertices = VERTS_PER_EDGE * VERTS_PER_EDGE;
		DWORD                           g_dwNumIndices = 6 * (VERTS_PER_EDGE - 1) * (VERTS_PER_EDGE - 1);
		LPDIRECT3DVERTEXSHADER9         g_pVertexShader = NULL;
		LPD3DXCONSTANTTABLE             g_pConstantTable = NULL;
		LPDIRECT3DVERTEXDECLARATION9    g_pVertexDeclaration = NULL;
	};
}


#endif