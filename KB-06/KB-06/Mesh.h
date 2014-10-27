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
		uint16 _nVertices, _FirstVertex;
		Vertex* _Vertices;
		//Texture Coords for each vertex
		uint16 _nTextureCoords, _FirstTextureCoord;
		TCoord* _TextureCoords;
		//Faces
		uint32 _nFaces, _FirstFace;
		Face* _Faces;
		//Subset of a mesh: there is one subset for each material used
		std::list<Subset*> _Subsets;
		//Normals
		uint16 _nNormals, _FirstNormal;
		Vector* _Normals;
		Face* _FaceNormals;
		//Material index for each face
		uint16 _nMaterials, _FirstMaterial;
		uint16* _FaceMaterials;
		//list of Materials for that Mesh
		std::vector<Material*> _Materials;
		std::string _Name;
	};
}
#endif