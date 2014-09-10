#ifndef _MESH_H_
#define _MESH_H_
#include <vector>
#include "Vertex.h"
#include "TextureCoordinate.h"
#include "normal.h"
#include "ParameterSpaceVertex.h"
#include "FaceDefinition.h"

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<TextureCoordinate> textureCoordinates;
	std::vector<Normal> normals;
	std::vector<ParameterSpaceVertex> parameterSpaceVertices;
	std::vector<FaceDefinition> faceDefinitions;
};
#endif

