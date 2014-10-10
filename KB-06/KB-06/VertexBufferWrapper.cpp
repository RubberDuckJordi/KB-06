#include "VertexBufferWrapper.h"

namespace pengine
{
	VertexBufferWrapper::VertexBufferWrapper()
	{

	}

	VertexBufferWrapper::~VertexBufferWrapper()
	{
		(*VertexBuffer)->Release();
		delete VertexBuffer;
	}

	void VertexBufferWrapper::SetVertexBuffer(IDirect3DVertexBuffer9** _VertexBuffer)
	{
		VertexBuffer = _VertexBuffer;
	}

	IDirect3DVertexBuffer9** VertexBufferWrapper::GetVertexBuffer()
	{
		return VertexBuffer;
	}
}