#ifndef _PENGINE_INDEXBUFFERWRAPPER_H_
#define _PENGINE_INDEXBUFFERWRAPPER_H_

#include <d3dx9.h>

namespace pengine
{
	class IndexBufferWrapper
	{
	public:
		IndexBufferWrapper();
		~IndexBufferWrapper();
		void SetIndexBuffer(IDirect3DIndexBuffer9** _IndexBuffer);
		IDirect3DIndexBuffer9** GetIndexBuffer();

	private:
		IDirect3DIndexBuffer9** IndexBuffer;
	};
}
#endif