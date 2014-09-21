#ifndef _RESOURCE_SUBSET_H_
#define _RESOURCE_SUBSET_H_
#include <vector>
#include "Vertex.h"
#include "TextureCoordinate.h"
#include "normal.h"
#include "ParameterSpaceVertex.h"
#include "FaceDefinition.h"
#include "Material.h"

namespace Resource
{
	struct Subset 
	{
		std::vector<Vertex> vertices;
		std::vector<TextureCoordinate> textureCoordinates;
		std::vector<Normal> normals;
		std::vector<ParameterSpaceVertex> parameterSpaceVertices;
		std::vector<FaceDefinition> faceDefinitions;
		Material defaultMaterial;
	};
}
#endif

