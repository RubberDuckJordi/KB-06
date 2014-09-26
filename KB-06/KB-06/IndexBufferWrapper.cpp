#include "IndexBufferWrapper.h"

pengine::IndexBufferWrapper::IndexBufferWrapper(IDirect3DIndexBuffer9** _IndexBuffer)
{
	IndexBuffer = _IndexBuffer;
}

pengine::IndexBufferWrapper::~IndexBufferWrapper()
{

}

void pengine::IndexBufferWrapper::SetIndexBuffer(IDirect3DIndexBuffer9** _IndexBuffer)
{
	IndexBuffer = _IndexBuffer;
}

IDirect3DIndexBuffer9** pengine::IndexBufferWrapper::GetIndexBuffer()
{
	return IndexBuffer;
}