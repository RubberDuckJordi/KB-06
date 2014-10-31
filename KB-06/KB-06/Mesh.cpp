#include "Mesh.h"

namespace pengine
{
	Mesh::Mesh()
	{
		//Vertices
		nVertices = 0;
		_FirstVertex = 0;
		vertices = NULL;
		//Texture Coords for each vertex
		nTextureCoords = 0;
		firstTextureCoord = 0;
		textureCoords = NULL;
		//Faces
		nFaces = 0;
		firstFace = 0;
		faces = NULL;
		//Subset of a mesh: there is one subset for each material used
		//subsets = 0;
		//Normals
		nNormals = 0;
		firstNormal = 0;
		normals = NULL;
		faceNormals = NULL;
		//Material index for each face
		nMaterials = 0;
		firstMaterial = 0;
		faceMaterials = NULL;
		name = "Undefined";
	}

	Mesh::~Mesh()
	{
		if (vertices != NULL)
		{
			delete[] vertices;
		}
		if (faces != NULL)
		{
			delete[] faces;
		}
		if (normals != NULL)
		{
			delete[] normals;
		}
		if (textureCoords != NULL)
		{
			delete[] textureCoords;
		}
		while (!materials.empty())
		{
			delete materials.back();
			materials.pop_back();
		}
		if (faceMaterials != NULL)
		{
			delete[] faceMaterials;
		}
		while (!subsets.empty())
		{
			delete[] subsets.back()->Faces;
			delete subsets.back();
			subsets.pop_back();
		}
	}

	Mesh* Mesh::IsName(std::string &MeshName)
	{
		if (strcmp(name.c_str(), MeshName.c_str()) == 0)
		{
			return this;
		}
		return 0;
	}

	void Mesh::UpdateIndices()
	{
		for (uint32 i = 0; i < nFaces; i++)
		{
			faces[i][0] += _FirstVertex;
			faces[i][1] += _FirstVertex;
			faces[i][2] += _FirstVertex;

			faceMaterials[i] += firstMaterial;
		}

		if (nNormals != 0)
		{
			for (uint32 i = 0; i < nFaces; i++)
			{
				faceNormals[i][0] += firstNormal;
				faceNormals[i][1] += firstNormal;
				faceNormals[i][2] += firstNormal;
			}
		}
	}

	void Mesh::CreateSubsets()
	{
		uint32 FaceCount;
		Subset* MeshSubset;

		//For each material
		for (unsigned int i = 0; i < materials.size(); i++)
		{
			//We count the number of faces using this material
			FaceCount = 0;
			for (unsigned int j = 0; j < nFaces; ++j)
			{
				if (faceMaterials[j] == i)
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
			for (unsigned int j = 0; j < nFaces; ++j)
			{
				if (faceMaterials[j] == i)
				{
					MeshSubset->Faces[k++] = faces[j];
				}
			}
			//And we add that subset to the list
			subsets.push_back(MeshSubset);
		}
	}
}