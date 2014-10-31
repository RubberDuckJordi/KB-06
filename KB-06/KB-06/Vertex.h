#ifndef _PENGINE_CUSTOMD3DVERTEX_H_
#define _PENGINE_CUSTOMD3DVERTEX_H_

#include <d3dx9.h>

/*
Vertex implementation
Contains position (xyz), normals (nX, nY, nZ) and texture coordinates (tu,tv)
*/

struct Vertex
{
	Vertex()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		nX = 0.0f;
		nY = 0.0f;
		nZ = 0.0f;
		tu = 0.0f;
		tv = 0.0f;
	}
	Vertex(float ix, float iy, float iz, float inX, float inY, float inZ, float itu, float itv)
	{
		x = ix;
		y = iy;
		z = iz;
		nX = inX;
		nY = inY;
		nZ = inZ;
		tu = itu;
		tv = itv;
	}

	/*!
	Does NOT add normals or texture coordinates!
	*/
	Vertex operator+(Vertex pA)
	{
		Vertex result;
		result.x = x + pA.x;
		result.y = y + pA.y;
		result.z = z + pA.z;
		result.nX = pA.nX;
		result.nY = pA.nY;
		result.nY = pA.nY;
		result.tu = pA.tu;
		result.tv = pA.tv;
		return result;
	};

	/*!
	Does NOT subtract normals or texture coordinates!
	*/
	Vertex operator-(Vertex pA)
	{
		Vertex result;
		result.x = x - pA.x;
		result.y = y - pA.y;
		result.z = z - pA.z;
		result.nX = pA.nX;
		result.nY = pA.nY;
		result.nY = pA.nY;
		result.tu = pA.tu;
		result.tv = pA.tv;
		return result;
	};

	/*!
	Does NOT multiply normals or texture coordinates!
	*/
	Vertex operator*(float scalar)
	{
		Vertex result;
		result.x = x * scalar;
		result.y = y * scalar;
		result.z = z * scalar;
		result.nX = nX;
		result.nY = nY;
		result.nY = nY;
		result.tu = tu;
		result.tv = tv;
		return result;
	};

	float x, y, z;		//Vertex position
	float nX, nY, nZ;	//Vertex normal
	float tu, tv;		//Texture coordinate
};

/*
Colored Vertex implementation
Contains position (xyz), normals (nX, nY, nZ) and texture coordinates (tu,tv) and color.
*/

struct ColoredVertex
{
	ColoredVertex()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		color = 0;
		tu = 0.0f;
		tv = 0.0f;
		nX = 0.0f;
		nY = 0.0f;
		nZ = 0.0f;
	}

	ColoredVertex(float ix, float iy, float iz, float inX, float inY, float inZ, DWORD icolor, float itu, float itv)
	{
		x = ix;
		y = iy;
		z = iz;
		color = icolor;
		tu = itu;
		tv = itv;
		nX = inX;
		nY = inY;
		nZ = inZ;
	}

	/*!
	Does NOT add colors, normals or texture coordinates!
	*/
	ColoredVertex operator+(ColoredVertex pA)
	{
		ColoredVertex result;
		result.x = x + pA.x;
		result.y = y + pA.y;
		result.z = z + pA.z;
		result.nX = pA.nX;
		result.nY = pA.nY;
		result.nY = pA.nY;
		result.tu = pA.tu;
		result.tv = pA.tv;
		result.color = pA.color;
		return result;
	};

	/*!
	Does NOT subtract colors, normals or texture coordinates!
	*/
	ColoredVertex operator-(ColoredVertex pA)
	{
		ColoredVertex result;
		result.x = x - pA.x;
		result.y = y - pA.y;
		result.z = z - pA.z;
		result.nX = pA.nX;
		result.nY = pA.nY;
		result.nY = pA.nY;
		result.tu = pA.tu;
		result.tv = pA.tv;
		result.color = pA.color;
		return result;
	};

	/*!
	Does NOT multiply colors, normals or texture coordinates!
	*/
	ColoredVertex operator*(float scalar)
	{
		ColoredVertex result;
		result.x = x * scalar;
		result.y = y * scalar;
		result.z = z * scalar;
		result.nX = nX;
		result.nY = nY;
		result.nY = nY;
		result.tu = tu;
		result.tv = tv;
		result.color = color;
		return result;
	};

	float x, y, z;		//Vertex position
	float nX, nY, nZ;	//Vertex normal
	DWORD color;		//Vertex color
	float tu, tv;		//Texture coordinate
};
#define D3DCustomVertexFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )
#define D3DCustomColoredVertexFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

#endif