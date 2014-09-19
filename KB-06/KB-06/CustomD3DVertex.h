#ifndef _CUSTOMD3DVERTEX_H_
#define _CUSTOMD3DVERTEX_H_

#include <d3dx9.h>
#include <d3dx9.h>
struct D3DCustomVertex
{
	float x, y, z; // vertex position
	//float tu, tv; // Texture co-ordinate
};

#define D3DCustomVertexFVF (D3DFVF_XYZ )
//#define D3DCustomVertexFVF (D3DFVF_XYZ | D3DFVF_TEX1 )
#endif