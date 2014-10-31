#include "Model3D.h"

namespace pengine
{
	Model3D::Model3D(Bone* skeleton)
	{
		logger = LoggerPool::GetInstance().GetLogger("SuperXLoader");
		skeleton = skeleton;
	};

	Model3D::~Model3D(void)
	{
		if (skeleton != 0)
		{
			delete skeleton;
		}
		while (!meshes.empty())
		{
			delete meshes.back();
			meshes.pop_back();
		}
		while (!animationsets.empty())
		{
			delete animationsets.back();
			animationsets.pop_back();
		}
	}

	Mesh* Model3D::IsMeshName(std::string &pText)
	{
		for (std::list<Mesh*>::iterator i = meshes.begin(); i != meshes.end(); i++)
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
		if (meshes.size() < 2)
		{
			return;
		}

		logger->Log(Logger::DEBUG, "Model3D: Concatenating Meshes...");


		Mesh* concatenatedMesh = new Mesh();
		Mesh* LastMesh = meshes.back();

		concatenatedMesh->name = "ConcatMesh";

		//We create the new mesh.
		//We get the dimensions of the new mesh
		concatenatedMesh->nVertices = LastMesh->_FirstVertex + LastMesh->nVertices;
		concatenatedMesh->nFaces = LastMesh->firstFace + LastMesh->nFaces;
		concatenatedMesh->nTextureCoords = LastMesh->firstTextureCoord + LastMesh->nTextureCoords;
		concatenatedMesh->nNormals = LastMesh->firstNormal + LastMesh->nNormals;

		//Here we have a check:
		//Texture coordinates must be as numerous as Vertices or there must be none
		//Normal vectors must be as numerous as Vertices or there must be none
		if ((concatenatedMesh->nTextureCoords < concatenatedMesh->nVertices) && (concatenatedMesh->nTextureCoords != 0))
		{
			concatenatedMesh->nTextureCoords = concatenatedMesh->nVertices;
		}
		if ((concatenatedMesh->nNormals < concatenatedMesh->nVertices) && (concatenatedMesh->nNormals != 0))
		{
			concatenatedMesh->nNormals = concatenatedMesh->nVertices;
		}

		logger->Log(Logger::DEBUG, "Model3D: Final number of Vertices: " + std::to_string(concatenatedMesh->nVertices));
		logger->Log(Logger::DEBUG, "Model3D: Final number of Faces: " + std::to_string(concatenatedMesh->nFaces));
		logger->Log(Logger::DEBUG, "Model3D: Final number of TextureCoords: " + std::to_string(concatenatedMesh->nTextureCoords));
		logger->Log(Logger::DEBUG, "Model3D: Final number of Normals: " + std::to_string(concatenatedMesh->nNormals));
		logger->Log(Logger::DEBUG, "Model3D: Final number of Materials: " + std::to_string(concatenatedMesh->nMaterials));

		//We create all the arrays:
		// - Vertices and Faces
		// - Material indices per face
		// - Texture Coords
		// - Normal vectors and Face Allocation of Normal vectors
		concatenatedMesh->vertices = new Vertex[concatenatedMesh->nVertices]();
		memset(concatenatedMesh->vertices, 0, concatenatedMesh->nVertices * sizeof(Vertex));
		concatenatedMesh->faces = new Face[concatenatedMesh->nFaces];
		memset(concatenatedMesh->faces, 0, concatenatedMesh->nFaces * sizeof(Face));
		concatenatedMesh->faceMaterials = new uint16[concatenatedMesh->nFaces];
		memset(concatenatedMesh->faceMaterials, 0, concatenatedMesh->nFaces * sizeof(uint16));
		if (concatenatedMesh->nTextureCoords != 0)
		{
			concatenatedMesh->textureCoords = new TCoord[concatenatedMesh->nTextureCoords];
			memset(concatenatedMesh->textureCoords, 0, concatenatedMesh->nTextureCoords * sizeof(TCoord));
		}
		if (concatenatedMesh->nNormals != 0)
		{
			concatenatedMesh->normals = new Vector[concatenatedMesh->nNormals];
			concatenatedMesh->faceNormals = new Face[concatenatedMesh->nFaces];
			memset(concatenatedMesh->normals, 0, concatenatedMesh->nNormals * sizeof(Vector));
			memset(concatenatedMesh->faceNormals, 0, concatenatedMesh->nFaces * sizeof(Face));
		}

		//We fill up the arrays with each array from the meshes container
		for (std::list<Mesh*>::iterator i = meshes.begin(); i != meshes.end(); i++)
		{
			(*i)->UpdateIndices();
			memcpy(&(concatenatedMesh->vertices[(*i)->_FirstVertex]), (*i)->vertices, (*i)->nVertices * sizeof(Vertex));
			memcpy(&(concatenatedMesh->faces[(*i)->firstFace]), (*i)->faces, (*i)->nFaces * sizeof(Face));

			if ((*i)->nTextureCoords != 0)
			{
				memcpy(&(concatenatedMesh->textureCoords[(*i)->firstTextureCoord]), (*i)->textureCoords, (*i)->nTextureCoords * sizeof(TCoord));
			}
			if ((*i)->nNormals != 0)
			{
				memcpy(&(concatenatedMesh->normals[(*i)->firstNormal]), (*i)->normals, (*i)->nNormals * sizeof(Vector));
				memcpy(&(concatenatedMesh->faceNormals[(*i)->firstFace]), (*i)->faceNormals, (*i)->nFaces * sizeof(Face));
			}

			if (i != meshes.begin())//if we don't check for this our crazy --i hack wouldn't work ;)
			{
				for (uint32 j = 0; j < (*i)->nFaces; j++)//(*i)->nFaces is the amount of facematerials too, as every face has a material.
				{
					(*i)->faceMaterials[j] += (*--i)->materials.size();//crazy hacks, but always works! :D
					++i;
				}
				memcpy(&(concatenatedMesh->faceMaterials[(*i)->firstFace]), (*i)->faceMaterials, (*i)->nFaces * sizeof(uint16));
			}

			while (!(*i)->materials.empty())
			{
				concatenatedMesh->materials.push_back((*i)->materials.front());
				(*i)->materials.erase((*i)->materials.begin());
			}
		}

		//OK. We now process the bone hierarchy to update the skinning indices
		logger->Log(Logger::DEBUG, "Model3D: Adapting the Bone hierarchy...");
		if (skeleton != 0)
		{
			UpdateBoneIndices(skeleton);
		}

		logger->Log(Logger::DEBUG, "Model3D: Bone hierarchy adapted.");

		//We eventually delete all the previous meshes
		while (!meshes.empty())
		{
			delete meshes.back();
			meshes.pop_back();
		}

		//and push the new concatenated one
		meshes.push_back(concatenatedMesh);

		//We create the subsets
		concatenatedMesh->CreateSubsets();

		logger->Log(Logger::DEBUG, "Model3D: All meshes are concatenated.");
	}

	void Model3D::UpdateBoneIndices(Bone* &pBone)
	{
		Mesh* BoneMesh = IsMeshName(pBone->meshName);
		if (BoneMesh != 0)
		{
			pBone->UpdateIndices(BoneMesh->_FirstVertex);
		}
		pBone->meshName = "ConcatMesh";
		if (!pBone->bones.empty())
		{
			for (auto i = pBone->bones.begin(); i != pBone->bones.end(); i++)
			{
				UpdateBoneIndices(*i);
			}
		}
	}

	AnimationSet* Model3D::FindAnimationSet(std::string &pText)
	{
		for (auto i = animationsets.begin(); i != animationsets.end(); i++)
		{
			if ((*i)->IsName(pText) != 0)
			{
				return (*i)->IsName(pText);
			}
		}
		return NULL;
	}
}