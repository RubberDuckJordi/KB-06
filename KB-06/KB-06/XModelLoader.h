#ifndef _RESOURCE_XMODELLOADER_H_
#define _RESOURCE_XMODELLOADER_H_

#include "XModel.h"
#include "DirectXRenderer.h"
#include "LoggerPool.h"
#include <d3d9.h>
#include <string>

namespace pengine
{
	class XModelLoader
	{
	public:
		XModelLoader();
		~XModelLoader();
		void LoadXModel(std::string filename, DirectXRenderer* renderer, XModel* xmodel);

	private:
		Logger* logger;
		LPDIRECT3DTEXTURE9* texture = new LPDIRECT3DTEXTURE9();
	};
}
#endif