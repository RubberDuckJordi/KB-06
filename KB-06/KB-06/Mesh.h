#ifndef _PENGINE_XMESH_H_
#define _PENGINE_XMESH_H_

#include "Types.h"
#include "Material.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Vertex.h"

#include <list>
#include <vector>
#include <deque>

namespace pengine
{
	struct Subset
	{
		uint16 Size;
		Face* Faces;
	};

	class Mesh
	{
	public:
		Mesh();
		~Mesh();
		Mesh* IsName(std::string &MeshName);
		void UpdateIndices();
		void CreateSubsets();
		//Vertices
		uint16 nVertices, _FirstVertex;
		Vertex* vertices;
		//Texture Coords for each vertex
		uint16 nTextureCoords, firstTextureCoord;
		TCoord* textureCoords;
		//Faces
		uint32 nFaces, firstFace;
		Face* faces;
		//Subset of a mesh: there is one subset for each material used
		std::list<Subset*> subsets;
		//Normals
		uint16 nNormals, firstNormal;
		Vector* normals;
		Face* faceNormals;
		//Material index for each face
		uint16 nMaterials, firstMaterial;
		uint16* faceMaterials;
		//list of Materials for that Mesh
		std::vector<Material*> materials;
		std::string name;
	};
}
#endif