#ifndef _RESOURCE_MTLRRESOURCE_H_
#define _RESOURCE_MTLRRESOURCE_H_
#include "Resource.h"
namespace Resource
{
	class MTLResource : public Resource
	{
	public:
		MTLResource();
		~MTLResource();
		Material GetMaterial(char* name);
		void AddMaterial(char* name, Material mat);
		std::map<char*, Material>* GetAllMaterials();
		void SetLoaded(bool state);
	protected:
		std::map<char*, Material> materials;
	};

}
#endif