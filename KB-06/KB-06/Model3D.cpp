#include "Model3D.h"

namespace pengine
{
	Model3D::Model3D(Bone* skeleton)
	{
		logger = LoggerPool::GetInstance().GetLogger("SuperXLoader");
		_Skeleton = skeleton;
	};

	Model3D::~Model3D(void)
	{
		if (_Skeleton != 0)
		{
			delete _Skeleton;
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

	Mesh* Model3D::IsMeshName(std::string &pText)
	{
		for (std::list<Mesh*>::iterator i = _Meshes.begin(); i != _Meshes.end(); i++)
		{
			if ((*i)->IsName(pText) != 0)
			{
				return (*i)->IsName(pText);
			}
		}
		return 0;
	}

	void Model3D::ConcatenateMeshes()
	{
		//We only concatenate when there are at least two meshes
		if (_Meshes.size() < 2)
		{
			return;
		}

		logger->Log(Logger::DEBUG, "Model3D: Concatenating Meshes...");


		Mesh* concatenatedMesh = new Mesh();
		Mesh* LastMesh = _Meshes.back();

		concatenatedMesh->_Name = "ConcatMesh";

		//We create the new mesh.
		//We get the dimensions of the new mesh
		concatenatedMesh->_nVertices = LastMesh->_FirstVertex + LastMesh->_nVertices;
		concatenatedMesh->_nFaces = LastMesh->_FirstFace + LastMesh->_nFaces;
		concatenatedMesh->_nTextureCoords = LastMesh->_FirstTextureCoord + LastMesh->_nTextureCoords;
		concatenatedMesh->_nNormals = LastMesh->_FirstNormal + LastMesh->_nNormals;

		//Here we have a check:
		//Texture coordinates must be as numerous as Vertices or there must be none
		//Normal vectors must be as numerous as Vertices or there must be none
		if ((concatenatedMesh->_nTextureCoords < concatenatedMesh->_nVertices) && (concatenatedMesh->_nTextureCoords != 0))
		{
			concatenatedMesh->_nTextureCoords = concatenatedMesh->_nVertices;
		}
		if ((concatenatedMesh->_nNormals < concatenatedMesh->_nVertices) && (concatenatedMesh->_nNormals != 0))
		{
			concatenatedMesh->_nNormals = concatenatedMesh->_nVertices;
		}

		logger->Log(Logger::DEBUG, "Model3D: Final number of Vertices: " + std::to_string(concatenatedMesh->_nVertices));
		logger->Log(Logger::DEBUG, "Model3D: Final number of Faces: " + std::to_string(concatenatedMesh->_nFaces));
		logger->Log(Logger::DEBUG, "Model3D: Final number of TextureCoords: " + std::to_string(concatenatedMesh->_nTextureCoords));
		logger->Log(Logger::DEBUG, "Model3D: Final number of Normals: " + std::to_string(concatenatedMesh->_nNormals));
		logger->Log(Logger::DEBUG, "Model3D: Final number of Materials: " + std::to_string(concatenatedMesh->_nMaterials));

		//We create all the arrays:
		// - Vertices and Faces
		// - Material indices per face
		// - Texture Coords
		// - Normal vectors and Face Allocation of Normal vectors
		concatenatedMesh->_Vertices = new Vertex[concatenatedMesh->_nVertices]();
		memset(concatenatedMesh->_Vertices, 0, concatenatedMesh->_nVertices * sizeof(Vertex));
		concatenatedMesh->_Faces = new Face[concatenatedMesh->_nFaces];
		memset(concatenatedMesh->_Faces, 0, concatenatedMesh->_nFaces * sizeof(Face));
		concatenatedMesh->_FaceMaterials = new uint16[concatenatedMesh->_nFaces];
		memset(concatenatedMesh->_FaceMaterials, 0, concatenatedMesh->_nFaces * sizeof(uint16));
		if (concatenatedMesh->_nTextureCoords != 0)
		{
			concatenatedMesh->_TextureCoords = new TCoord[concatenatedMesh->_nTextureCoords];
			memset(concatenatedMesh->_TextureCoords, 0, concatenatedMesh->_nTextureCoords * sizeof(TCoord));
		}
		if (concatenatedMesh->_nNormals != 0)
		{
			concatenatedMesh->_Normals = new Vector[concatenatedMesh->_nNormals];
			concatenatedMesh->_FaceNormals = new Face[concatenatedMesh->_nFaces];
			memset(concatenatedMesh->_Normals, 0, concatenatedMesh->_nNormals * sizeof(Vector));
			memset(concatenatedMesh->_FaceNormals, 0, concatenatedMesh->_nFaces * sizeof(Face));
		}

		//We fill up the arrays with each array from the _Meshes container
		for (std::list<Mesh*>::iterator i = _Meshes.begin(); i != _Meshes.end(); i++)
		{
			(*i)->UpdateIndices();
			memcpy(&(concatenatedMesh->_Vertices[(*i)->_FirstVertex]), (*i)->_Vertices, (*i)->_nVertices * sizeof(Vertex));
			memcpy(&(concatenatedMesh->_Faces[(*i)->_FirstFace]), (*i)->_Faces, (*i)->_nFaces * sizeof(Face));

			if ((*i)->_nTextureCoords != 0)
			{
				memcpy(&(concatenatedMesh->_TextureCoords[(*i)->_FirstTextureCoord]), (*i)->_TextureCoords, (*i)->_nTextureCoords * sizeof(TCoord));
			}
			if ((*i)->_nNormals != 0)
			{
				memcpy(&(concatenatedMesh->_Normals[(*i)->_FirstNormal]), (*i)->_Normals, (*i)->_nNormals * sizeof(Vector));
				memcpy(&(concatenatedMesh->_FaceNormals[(*i)->_FirstFace]), (*i)->_FaceNormals, (*i)->_nFaces * sizeof(Face));
			}

			if (i != _Meshes.begin())//if we don't check for this our crazy --i hack wouldn't work ;)
			{
				for (int j = 0; j < (*i)->_nFaces; j++)//(*i)->_nFaces is the amount of facematerials too, as every face has a material.
				{
					(*i)->_FaceMaterials[j] += (*--i)->_Materials.size();//crazy hacks, but always works! :D
					++i;
				}
				memcpy(&(concatenatedMesh->_FaceMaterials[(*i)->_FirstFace]), (*i)->_FaceMaterials, (*i)->_nFaces * sizeof(uint16));
			}

			while (!(*i)->_Materials.empty())
			{
				concatenatedMesh->_Materials.push_back((*i)->_Materials.front());
				(*i)->_Materials.pop_front();
			}
		}

		//OK. We now process the bone hierarchy to update the skinning indices
		logger->Log(Logger::DEBUG, "Model3D: Adapting the Bone hierarchy...");
		if (_Skeleton != 0)
		{
			UpdateBoneIndices(_Skeleton);
		}

		logger->Log(Logger::DEBUG, "Model3D: Bone hierarchy adapted.");

		//We eventually delete all the previous meshes
		while (!_Meshes.empty())
		{
			delete _Meshes.back();
			_Meshes.pop_back();
		}

		//and push the new concatenated one
		_Meshes.push_back(concatenatedMesh);

		//We create the subsets
		concatenatedMesh->CreateSubsets();

		logger->Log(Logger::DEBUG, "Model3D: All meshes are concatenated.");
	}

	void Model3D::UpdateBoneIndices(Bone* &pBone)
	{
		Mesh* BoneMesh = IsMeshName(pBone->_MeshName);
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
}