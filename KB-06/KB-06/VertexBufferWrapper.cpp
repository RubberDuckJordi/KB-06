#ifndef _VERTEXBUFFERWRAPPER_CPP_
#define _VERTEXBUFFERWRAPPER_CPP_

#include <d3dx9.h>

class VertexBufferWrapper
{
public:
	VertexBufferWrapper::VertexBufferWrapper(IDirect3DVertexBuffer9** _VertexBuffer)
	{
		VertexBuffer = _VertexBuffer;
	};

	VertexBufferWrapper::~VertexBufferWrapper()
	{

	};

	void VertexBufferWrapper::SetVertexBuffer(IDirect3DVertexBuffer9** _VertexBuffer)
	{
		VertexBuffer = _VertexBuffer;
	};

	IDirect3DVertexBuffer9** VertexBufferWrapper::GetVertexBuffer()
	{
		return VertexBuffer;
	};

private:
	IDirect3DVertexBuffer9** VertexBuffer;
};

#endif