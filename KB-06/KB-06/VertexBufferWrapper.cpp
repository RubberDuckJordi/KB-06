#ifndef _VERTEXBUFFERWRAPPER_CPP_
#define _VERTEXBUFFERWRAPPER_CPP_

#include <d3dx9.h>

class VertexBufferWrapper
{
public:
	VertexBufferWrapper::VertexBufferWrapper(LPDIRECT3DVERTEXBUFFER9 _VertexBuffer)
	{
		VertexBuffer = _VertexBuffer;
	};

	VertexBufferWrapper::~VertexBufferWrapper()
	{

	};

	void VertexBufferWrapper::SetDWORD(LPDIRECT3DVERTEXBUFFER9 _VertexBuffer)
	{
		VertexBuffer = _VertexBuffer;
	};

	LPDIRECT3DVERTEXBUFFER9 VertexBufferWrapper::GetDWORD()
	{
		return VertexBuffer;
	};

private:
	LPDIRECT3DVERTEXBUFFER9 VertexBuffer;
};

#endif