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

	void VertexBufferWrapper::SetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 _VertexBuffer)
	{
		VertexBuffer = _VertexBuffer;
	};

	LPDIRECT3DVERTEXBUFFER9 VertexBufferWrapper::GetVertexBuffer()
	{
		return VertexBuffer;
	};

private:
	LPDIRECT3DVERTEXBUFFER9 VertexBuffer;
};

#endif