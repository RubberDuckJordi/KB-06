#ifndef _PENGINE_CUSTOMD3DVERTEX_H_
#define _PENGINE_CUSTOMD3DVERTEX_H_

#include <d3dx9.h>
struct D3DCustomVertex
{
	float x, y, z; // vertex position
	float tu, tv; // Texture co-ordinate
};
#define D3DCustomVertexFVF (D3DFVF_XYZ | D3DFVF_TEX1 )

struct D3DColoredCustomVertex
{
	float x, y, z;
	DWORD color;
};
#define D3DColoredCustomVertexFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE )

#endif