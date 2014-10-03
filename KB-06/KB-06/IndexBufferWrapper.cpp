#include "IndexBufferWrapper.h"

namespace pengine
{
	IndexBufferWrapper::IndexBufferWrapper(IDirect3DIndexBuffer9** _IndexBuffer)
	{
		IndexBuffer = _IndexBuffer;
	}

	IndexBufferWrapper::~IndexBufferWrapper()
	{

	}

	void IndexBufferWrapper::SetIndexBuffer(IDirect3DIndexBuffer9** _IndexBuffer)
	{
		IndexBuffer = _IndexBuffer;
	}

	IDirect3DIndexBuffer9** IndexBufferWrapper::GetIndexBuffer()
	{
		return IndexBuffer;
	}
}