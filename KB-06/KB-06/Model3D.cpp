#include "Model3D.h"

Model3D::~Model3D(void)
{
	if (_Skeletton != 0)
	{
		delete _Skeletton;
	}
	while (!_Meshes.empty())
	{
		delete _Meshes.back();
		_Meshes.pop_back();
	}
	while (!_AnimationSets.empty())
	{
		delete _AnimationSets.back();
		_AnimationSets.pop_back();
	}
}

XMesh* Model3D::IsMeshName(std::string &pText)
{
	for (std::list<XMesh*>::iterator i = _Meshes.begin(); i != _Meshes.end(); i++)
	{
		if ((*i)->IsName(pText) != 0)
		{
			return (*i)->IsName(pText);
		}
	}
	return 0;
}

void Model3D::ConcatenateMeshes(void)
{
	//We only concatenate when there are at least two meshes
	if (_Meshes.size() < 2)
	{
		return;
	}

	logger->Log(0, "Model3D: Concatenating Meshes...");


	XMesh* ConcatMesh = new XMesh;
	XMesh* LastMesh = _Meshes.back();

	ConcatMesh->_Name = "ConcatMesh";

	//We create the new mesh.
	//We get the dimensions of the new mesh
	ConcatMesh->_nVertices = LastMesh->_FirstVertex + LastMesh->_nVertices;
	ConcatMesh->_nFaces = LastMesh->_FirstFace + LastMesh->_nFaces;
	ConcatMesh->_nTextureCoords = LastMesh->_FirstTextureCoord + LastMesh->_nTextureCoords;
	ConcatMesh->_nNormals = LastMesh->_FirstNormal + LastMesh->_nNormals;

	//Here we have a control:
	//Texture coordinates must be as numerous as Vertices or there must be none
	//Normal vectors must be as numerous as Vertices or there must be none
	if ((ConcatMesh->_nTextureCoords < ConcatMesh->_nVertices) && (ConcatMesh->_nTextureCoords != 0))
	{
		ConcatMesh->_nTextureCoords = ConcatMesh->_nVertices;
	}
	if ((ConcatMesh->_nNormals < ConcatMesh->_nVertices) && (ConcatMesh->_nNormals != 0))
	{
		ConcatMesh->_nNormals = ConcatMesh->_nVertices;
	}

	logger->LogAll(0, "Model3D: Final number of Vertices:", ConcatMesh->_nVertices);
	logger->LogAll(0, "Model3D: Final number of Faces:", ConcatMesh->_nFaces);
	logger->LogAll(0, "Model3D: Final number of TextureCoords:", ConcatMesh->_nTextureCoords);
	logger->LogAll(0, "Model3D: Final number of Normals:", ConcatMesh->_nNormals);
	logger->LogAll(0, "Model3D: Final number of Materials:", ConcatMesh->_nMaterials);

	//We create all the arrays:
	// - Vertices and Faces
	// - Material indices per face
	// - Texture Coords
	// - Normal vectors and Face Allocation of Normal vectors
	ConcatMesh->_Vertices = new Vertex[ConcatMesh->_nVertices];
	memset(ConcatMesh->_Vertices, 0, ConcatMesh->_nVertices * sizeof(Vertex));
	ConcatMesh->_Faces = new Face[ConcatMesh->_nFaces];
	memset(ConcatMesh->_Faces, 0, ConcatMesh->_nFaces * sizeof(Face));
	ConcatMesh->_FaceMaterials = new uint16[ConcatMesh->_nFaces];
	memset(ConcatMesh->_FaceMaterials, 0, ConcatMesh->_nFaces * sizeof(uint16));
	if (ConcatMesh->_nTextureCoords != 0)
	{
		ConcatMesh->_TextureCoords = new TCoord[ConcatMesh->_nTextureCoords];
		memset(ConcatMesh->_TextureCoords, 0, ConcatMesh->_nTextureCoords * sizeof(TCoord));
	}
	if (ConcatMesh->_nNormals != 0)
	{
		ConcatMesh->_Normals = new Vector<float>[ConcatMesh->_nNormals];
		ConcatMesh->_FaceNormals = new Face[ConcatMesh->_nFaces];
		memset(ConcatMesh->_Normals, 0, ConcatMesh->_nNormals * sizeof(Vector<float>));
		memset(ConcatMesh->_FaceNormals, 0, ConcatMesh->_nFaces * sizeof(Face));
	}

	//We fill up the arrays with each array from the _Meshes container
	for (std::list<XMesh*>::iterator i = _Meshes.begin(); i != _Meshes.end(); i++)
	{
		(*i)->UpdateIndices();
		memcpy(&(ConcatMesh->_Vertices[(*i)->_FirstVertex]), (*i)->_Vertices, (*i)->_nVertices * sizeof(Vertex));
		memcpy(&(ConcatMesh->_Faces[(*i)->_FirstFace]), (*i)->_Faces, (*i)->_nFaces * sizeof(Face));
		memcpy(&(ConcatMesh->_FaceMaterials[(*i)->_FirstFace]), (*i)->_FaceMaterials, (*i)->_nFaces * sizeof(uint16));
		if ((*i)->_nTextureCoords != 0)
		{
			memcpy(&(ConcatMesh->_TextureCoords[(*i)->_FirstTextureCoord]), (*i)->_TextureCoords, (*i)->_nTextureCoords * sizeof(TCoord));
		}
		if ((*i)->_nNormals != 0)
		{
			memcpy(&(ConcatMesh->_Normals[(*i)->_FirstNormal]), (*i)->_Normals, (*i)->_nNormals * sizeof(Vector<float>));
			memcpy(&(ConcatMesh->_FaceNormals[(*i)->_FirstFace]), (*i)->_FaceNormals, (*i)->_nFaces * sizeof(Face));
		}
		while (!(*i)->_Materials.empty())
		{
			ConcatMesh->_Materials.push_back((*i)->_Materials.front());
			(*i)->_Materials.pop_front();
		}
	}

	////////////////////////////////////////////////////////////
	//OK. We now process the bone hierarchy to update the
	//skinning indices

	logger->Log(0, "Model3D: Adapting the Bone hierarchy...");
	if (_Skeletton != 0)
	{
		UpdateBoneIndices(_Skeletton);
	}

	logger->Log(0, "Model3D: Bone hierarchy adapted.");

	//We eventually delete all the previous meshes
	while (!_Meshes.empty()) {
		delete _Meshes.back();
		_Meshes.pop_back();
	}

	//and push the new concatenated one
	_Meshes.push_back(ConcatMesh);

	//We create the subsets
	ConcatMesh->CreateSubsets();

	logger->Log(0, "Model3D: All meshes are concatenated.");
}

void Model3D::UpdateBoneIndices(Bone* &pBone)
{
	XMesh* BoneMesh = IsMeshName(pBone->_MeshName);
	if (BoneMesh != 0)
	{
		pBone->UpdateIndices(BoneMesh->_FirstVertex);
	}
	pBone->_MeshName = "ConcatMesh";
	if (!pBone->_Bones.empty())
	{
		for (std::list<Bone*>::iterator i = pBone->_Bones.begin(); i != pBone->_Bones.end(); i++)
		{
			UpdateBoneIndices(*i);
		}
	}
}

/*************************************************
NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW*/

AnimationSet* Model3D::FindAnimationSet(std::string &pText)
{
	for (std::list<AnimationSet*>::iterator i = _AnimationSets.begin(); i != _AnimationSets.end(); i++)
	{
		if ((*i)->IsName(pText) != 0)
		{
			return (*i)->IsName(pText);
		}
	}
	return 0;
}