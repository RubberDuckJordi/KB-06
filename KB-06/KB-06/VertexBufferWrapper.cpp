#include "VertexBufferWrapper.h"

namespace pengine
{
	VertexBufferWrapper::VertexBufferWrapper()
	{
		numVertices = 0;
	}

	VertexBufferWrapper::~VertexBufferWrapper()
	{
		vertexBuffer->Release();
		vertexBuffer = NULL;
	}

	void VertexBufferWrapper::SetVertexBuffer(IDirect3DVertexBuffer9* _VertexBuffer, unsigned int _numVertices)
	{
		vertexBuffer = _VertexBuffer;
		numVertices = _numVertices;
	}

	IDirect3DVertexBuffer9* VertexBufferWrapper::GetVertexBuffer()
	{
		return vertexBuffer;
	}

	unsigned int VertexBufferWrapper::GetNumVertices()
	{
		return numVertices;
	}

	void VertexBufferWrapper::SetFVF(int _fvf)
	{
		fvf = _fvf;
	}

	int VertexBufferWrapper::GetFVF()
	{
		return fvf;
	}
}