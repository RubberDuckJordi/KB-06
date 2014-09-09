#ifndef _INDEXBUFFERWRAPPER_CPP_
#define _INDEXBUFFERWRAPPER_CPP_

#include <d3dx9.h>

class IndexBufferWrapper
{
public:
	IndexBufferWrapper::IndexBufferWrapper(LPDIRECT3DINDEXBUFFER9 _IndexBuffer)
	{
		IndexBuffer = _IndexBuffer;
	};

	IndexBufferWrapper::~IndexBufferWrapper()
	{

	};

	void IndexBufferWrapper::SetDWORD(LPDIRECT3DINDEXBUFFER9 _IndexBuffer)
	{
		IndexBuffer = _IndexBuffer;
	};

	LPDIRECT3DINDEXBUFFER9 IndexBufferWrapper::GetDWORD()
	{
		return IndexBuffer;
	};

private:
	LPDIRECT3DINDEXBUFFER9 IndexBuffer;
};

#endif