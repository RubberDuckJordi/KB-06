#ifndef _INDEXBUFFERWRAPPER_CPP_
#define _INDEXBUFFERWRAPPER_CPP_

#include <d3dx9.h>

class IndexBufferWrapper
{
public:
	IndexBufferWrapper::IndexBufferWrapper(IDirect3DIndexBuffer9** _IndexBuffer)
	{
		IndexBuffer = _IndexBuffer;
	};

	IndexBufferWrapper::~IndexBufferWrapper()
	{

	};

	void IndexBufferWrapper::SetIndexBuffer(IDirect3DIndexBuffer9** _IndexBuffer)
	{
		IndexBuffer = _IndexBuffer;
	};

	IDirect3DIndexBuffer9** IndexBufferWrapper::GetIndexBuffer()
	{
		return IndexBuffer;
	};

private:
	IDirect3DIndexBuffer9** IndexBuffer;
};

#endif