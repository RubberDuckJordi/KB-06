#ifndef _PENGINE_MATERIALWRAPPER_H_
#define _PENGINE_MATERIALWRAPPER_H_

#include <d3dx9.h>

/*
Wrapper to wrap directX specific implementation
*/

namespace pengine
{
	class MaterialWrapper
	{
	public:
		MaterialWrapper(D3DMATERIAL9* _material);
		~MaterialWrapper();
		void SetMaterial(D3DMATERIAL9* _material);
		D3DMATERIAL9* GetMaterial();
	private:
		D3DMATERIAL9* material;
	};
}
#endif