#ifndef _PENGINE_XMESH_H_
#define _PENGINE_XMESH_H_

#include "Types.h"
//#include "framework\frm_Quaternion.h"
#include "Material.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Vertex.h"

//#include "Toolbox\Mytrace.h"

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
		Mesh(void) :_nVertices(0), _Vertices(0),
			_nFaces(0), _Faces(0),
			_nTextureCoords(0), _TextureCoords(0),
			_FaceMaterials(0),
			_nNormals(0), _Normals(0),
			_nMaterials(0),
			_FirstVertex(0),          //The _Firstxxx series are used
			_FirstFace(0),            //for mesh concatenation
			_FirstTextureCoord(0),
			_FirstNormal(0),
			_FirstMaterial(0)
		{
		};
		~Mesh(void);
		Mesh* IsName(std::string &MeshName)
		{
			if (strcmp(_Name.c_str(), MeshName.c_str()) == 0)
			{
				return this;
			}
			return 0;
		};
		void UpdateIndices(void);
		void CreateSubsets(void);
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
		Vector<float>* _Normals;
		Face* _FaceNormals;
		//Material index for each face
		uint16 _nMaterials, _FirstMaterial;
		uint16* _FaceMaterials;
		uint16 _nFaceMaterials;//actually not needed, as it should always be the same amount as nFaces
		std::vector<int>* facesPerMaterial;//an vector of vectors containing face indices; one vector per material... this should speed things up... Yep, a 2 dimensional vector :D
		//list of Materials for that Mesh
		std::deque<Material*> _Materials;
		std::string _Name;
	};
}
#endif