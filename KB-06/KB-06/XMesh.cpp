/////////////////////////////////////////////////////////
// Frm_Mesh.cpp
//
//
/////////////////////////////////////////////////////////

#include "XMesh.h"

XMesh::~XMesh(void)
{
	if (_Vertices != 0) delete[] _Vertices;
	if (_Faces != 0) delete[] _Faces;
	if (_Normals != 0) delete[] _Normals;
	if (_TextureCoords != 0) delete[] _TextureCoords;
	while (!_Materials.empty())
	{
		delete _Materials.back();
		_Materials.pop_back();
	}
	if (_FaceMaterials != 0) delete[] _FaceMaterials;
	while (!_Subsets.empty())
	{
		delete[] _Subsets.back()->Faces;
		delete _Subsets.back();
		_Subsets.pop_back();
	}
}

void XMesh::UpdateIndices(void)
{
	for (uint32 i = 0; i < _nFaces; i++)
	{
		_Faces[i].data[0] += _FirstVertex;
		_Faces[i].data[1] += _FirstVertex;
		_Faces[i].data[2] += _FirstVertex;

		_FaceMaterials[i] += _FirstMaterial;
	}

	if (_nNormals != 0)
		for (uint32 i = 0; i < _nFaces; i++)
		{
		_FaceNormals[i].data[0] += _FirstNormal;
		_FaceNormals[i].data[1] += _FirstNormal;
		_FaceNormals[i].data[2] += _FirstNormal;
		}
}

void XMesh::CreateSubsets(void){
	uint32 FaceCount;
	Subset* MeshSubset;

	//For each material
	for (int i = 0; i < _Materials.size(); i++)
	{
		//We count the number of faces using this material
		FaceCount = 0;
		for (int j = 0; j < _nFaces; j++)
			if (_FaceMaterials[j] == i)
				++FaceCount;
		//We initialise the mesh subset
		MeshSubset = new Subset;
		MeshSubset->Size = FaceCount;
		MeshSubset->Faces = new Face[FaceCount];
		int k = 0;
		//We fill in the Mesh subset
		for (int j = 0; j < _nFaces; j++)
			if (_FaceMaterials[j] == i)
				MeshSubset->Faces[k++] = _Faces[j];
		//And we add that subset to the list
		_Subsets.push_back(MeshSubset);
	}
}
/*************************************************/
