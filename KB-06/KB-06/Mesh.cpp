#include "Mesh.h"

namespace pengine
{
	Mesh::Mesh()
	{
		//Vertices
		_nVertices = 0;
		_FirstVertex = 0;
		_Vertices = NULL;
		//Texture Coords for each vertex
		_nTextureCoords = 0;
		_FirstTextureCoord = 0;
		_TextureCoords = NULL;
		//Faces
		_nFaces = 0;
		_FirstFace = 0;
		_Faces = NULL;
		//Subset of a mesh: there is one subset for each material used
		//_Subsets = 0;
		//Normals
		_nNormals = 0;
		_FirstNormal = 0;
		_Normals = NULL;
		_FaceNormals = NULL;
		//Material index for each face
		_nMaterials = 0;
		_FirstMaterial = 0;
		_FaceMaterials = NULL;
		_Name = "Undefined";
	}

	Mesh::~Mesh()
	{
		if (_Vertices != NULL)
		{
			delete[] _Vertices;
		}
		if (_Faces != NULL)
		{
			delete[] _Faces;
		}
		if (_Normals != NULL)
		{
			delete[] _Normals;
		}
		if (_TextureCoords != NULL)
		{
			delete[] _TextureCoords;
		}
		while (!_Materials.empty())
		{
			delete _Materials.back();
			_Materials.pop_back();
		}
		if (_FaceMaterials != NULL)
		{
			delete[] _FaceMaterials;
		}
		while (!_Subsets.empty())
		{
			delete[] _Subsets.back()->Faces;
			delete _Subsets.back();
			_Subsets.pop_back();
		}
	}

	Mesh* Mesh::IsName(std::string &MeshName)
	{
		if (strcmp(_Name.c_str(), MeshName.c_str()) == 0)
		{
			return this;
		}
		return 0;
	}

	void Mesh::UpdateIndices()
	{
		for (uint32 i = 0; i < _nFaces; i++)
		{
			_Faces[i].data[0] += _FirstVertex;
			_Faces[i].data[1] += _FirstVertex;
			_Faces[i].data[2] += _FirstVertex;

			_FaceMaterials[i] += _FirstMaterial;
		}

		if (_nNormals != 0)
		{
			for (uint32 i = 0; i < _nFaces; i++)
			{
				_FaceNormals[i].data[0] += _FirstNormal;
				_FaceNormals[i].data[1] += _FirstNormal;
				_FaceNormals[i].data[2] += _FirstNormal;
			}
		}
	}

	void Mesh::CreateSubsets()
	{
		uint32 FaceCount;
		Subset* MeshSubset;

		//For each material
		for (unsigned int i = 0; i < _Materials.size(); i++)
		{
			//We count the number of faces using this material
			FaceCount = 0;
			for (unsigned int j = 0; j < _nFaces; ++j)
			{
				if (_FaceMaterials[j] == i)
				{
					++FaceCount;
				}
			}
			//We initialise the mesh subset
			MeshSubset = new Subset;
			MeshSubset->Size = (uint16)FaceCount;
			MeshSubset->Faces = new Face[FaceCount];
			int k = 0;
			//We fill in the Mesh subset
			for (unsigned int j = 0; j < _nFaces; ++j)
			{
				if (_FaceMaterials[j] == i)
				{
					MeshSubset->Faces[k++] = _Faces[j];
				}
			}
			//And we add that subset to the list
			_Subsets.push_back(MeshSubset);
		}
	}
}