#include "IndexBufferWrapper.h"

namespace pengine
{
	IndexBufferWrapper::IndexBufferWrapper()
	{
		numIndices = 0;
	}

	IndexBufferWrapper::~IndexBufferWrapper()
	{
		indexBuffer->Release();
	}

	void IndexBufferWrapper::SetIndexBuffer(IDirect3DIndexBuffer9* _IndexBuffer, unsigned int _numIndices)
	{
		indexBuffer = _IndexBuffer;
		numIndices = _numIndices;
	}

	unsigned int IndexBufferWrapper::GetNumIndices()
	{
		return numIndices;
	}

	IDirect3DIndexBuffer9* IndexBufferWrapper::GetIndexBuffer()
	{
		return indexBuffer;
	}
}