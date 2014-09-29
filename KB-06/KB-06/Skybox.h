#ifndef _RESOURCE_MESH_H_
#define _RESOURCE_MESH_H_

#include "TextureWrapper.h"
#include "CustomD3DVertex.h"

namespace pengine
{ 
class Skybox
{
public:
	Skybox(TextureWrapper* texture);
	~Skybox();


private:
	D3DCustomVertex* aSkyboxVertices;
	int* aSkyboxIndices;
	TextureWrapper* texture;

};

}


#endif