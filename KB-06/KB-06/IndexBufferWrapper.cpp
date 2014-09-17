#include "IndexBufferWrapper.h"

	Renderer::IndexBufferWrapper::IndexBufferWrapper(IDirect3DIndexBuffer9** _IndexBuffer)
	{
		IndexBuffer = _IndexBuffer;
	};

	Renderer::IndexBufferWrapper::~IndexBufferWrapper()
	{

	};

	void Renderer::IndexBufferWrapper::SetIndexBuffer(IDirect3DIndexBuffer9** _IndexBuffer)
	{
		IndexBuffer = _IndexBuffer;
	};


	IDirect3DIndexBuffer9** Renderer::IndexBufferWrapper::GetIndexBuffer()
	{
		return IndexBuffer;
	};


