#ifndef _RESOURCE_XMODELLOADER_H_
#define _RESOURCE_XMODELLOADER_H_

#include "XModel.h"
#include "DirectXRenderer.h"
#include "LoggerPool.h"
#include <d3d9.h>
#include <string>

namespace Resource
{
	class XModelLoader
	{
	public:
		XModelLoader();
		~XModelLoader();
		void LoadXModel(std::string filename, Renderer::DirectXRenderer* renderer, XModel* xmodel);
	private:
		Logger::Logger* logger;
	};
}

#endif