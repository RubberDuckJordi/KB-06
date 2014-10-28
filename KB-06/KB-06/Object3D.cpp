#include "Object3D.h"

#include "Vertex.h"

namespace pengine
{

	Object3D::Object3D() :_Skeleton(NULL), _SkinnedVertices(NULL), _Model(NULL), _AnimationStep(1)
	{
		Logger* logger = LoggerPool::GetInstance().GetLogger("SuperXLoader");
		logger->SetLogLevel(Logger::DEBUG);
		showWarning = true;
	}

	Object3D::~Object3D()
	{
		if (_SkinnedVertices != 0)
		{
			delete[] _SkinnedVertices;
		}
		while (indexBuffers.size() != 0)
		{
			delete indexBuffers.back();
			indexBuffers.pop_back();
		}
	}

	void Object3D::ClearSkinnedVertices(void)
	{
		memset(_SkinnedVertices, 0, _Mesh->_nVertices * sizeof(Vertex));
	}

	void Object3D::SetAnimationStep(uint16 pStep)
	{
		_AnimationStep = pStep;
	}

	void Object3D::UpdateAnimation()
	{
		if (showWarning && _cAnimationSet == NULL)
		{
			//this warning should be in the future PEngine manual instead, with just a crash...
			logger->Log(Logger::WARNING, "There are no animations, don't call UpdateAnimation!");
		}
		else if (_cAnimationSet != NULL)
		{
			ClearSkinnedVertices();
			_cKey += _AnimationStep;
			if (_cKey > _cAnimationSet->_MaxKey)
			{
				_cKey = 0;
			}
			CalcAnimation(_Skeleton);
			ComputeBoundingBoxSphere();
			CalcAttitude(_Skeleton, 0);
			SkinMesh(_Skeleton);
		}
	}

	void Object3D::UpdateBindSpace(void)
	{
		CalcBindSpace(_Skeleton);
		CalcAttitude(_Skeleton, 0);
		SkinMesh(_Skeleton);
	}

	void Object3D::CalcAnimation(void)
	{
		_cKey += _AnimationStep;
		if (_cKey > _cAnimationSet->_MaxKey)
		{
			_cKey = 0;
		}
		CalcAnimation(_Skeleton);
		ComputeBoundingBoxSphere();
	}

	void Object3D::CalcBindSpace(void)
	{
		CalcBindSpace(_Skeleton);
	}

	void Object3D::Update(void)
	{
		CalcAttitude(_Skeleton, 0);
		SkinMesh(_Skeleton);
	}

	void Object3D::SetupModel(Model3D* &pModel)
	{
		_Model = pModel;
		_Mesh = _Model->_Meshes.back();
		_SkinnedVertices = new Vertex[_Mesh->_nVertices]();
		_Skeleton = ReplicateSkeleton(_Model->_Skeleton);
	}

	void Object3D::MapAnimationSet(std::string pText)
	{
		_cAnimationSet = _Model->FindAnimationSet(pText);
		_cKey = 0;
		if (_cAnimationSet != 0)
		{
			GetBoneAnimation(_Skeleton);
		}
	}

	void Object3D::MapAnimationSet(uint16 &index)
	{
		if (_Model->_AnimationSets.size() == 0)
		{
			return;
		}
		if (index >= _Model->_AnimationSets.size())
		{
			index = 0;
		}
		//logger->LogAll(Logger::INFO, "Object3D: ", _Model->_AnimationSets.size(), " Animation Sets. Playing: ", index);

		std::list<AnimationSet*>::iterator i = _Model->_AnimationSets.begin();
		if (index != 0)
		{
			int16 test = index;
			while (test--)
			{
				i++;
			}
		}
		_cAnimationSet = (*i);

		GetBoneAnimation(_Skeleton);
		_cKey = 0;
	}

	void Object3D::CacheToRenderer(Renderer* renderer)
	{
		if (indexBuffers.size() == 0)
		{
			if (_Mesh->_Subsets.size() == 0)
			{
				unsigned int counter = 0;
				for (auto i = _Mesh->_Materials.begin(); i != _Mesh->_Materials.end(); ++i)
				{
					std::list<Face> facesToDraw;
					for (unsigned int j = 0; j < _Mesh->_nFaces; ++j)
					{
						int ffs = _Mesh->_FaceMaterials[j];
						if (_Mesh->_FaceMaterials[j] == counter)
						{
							facesToDraw.push_back(_Mesh->_Faces[j]);
						}
					}
					unsigned int* indices = new unsigned int[facesToDraw.size() * 3];
					unsigned int counter2 = 0;
					for (auto it = facesToDraw.begin(); it != facesToDraw.end(); ++it)
					{
						Face tempFace = (*it);
						indices[counter2 + 0] = tempFace[0];
						indices[counter2 + 1] = tempFace[1];
						indices[counter2 + 2] = tempFace[2];
						counter2 += 3;
					}
					IndexBufferWrapper* ibW = renderer->CreateIndexBuffer(indices, facesToDraw.size() * 3);
					indexBuffers.push_back(ibW);
					delete[] indices;

					counter++;
				}
			}
			else
			{
				Subset* tempSubset;
				Face tempFace;
				auto i = _Mesh->_Subsets.begin();
				auto j = _Mesh->_Materials.begin();

				while (j != _Mesh->_Materials.end())
				{
					tempSubset = *i;
					unsigned int indicesForSubset = tempSubset->Size * 3;//amount of faces * 3
					unsigned int* indices = new unsigned int[indicesForSubset];
					unsigned int currentIndex = -1;

					for (int k = 0; k < tempSubset->Size; k++)
					{
						tempFace = tempSubset->Faces[k];
						indices[++currentIndex] = tempFace[0];
						indices[++currentIndex] = tempFace[1];
						indices[++currentIndex] = tempFace[2];
					}

					IndexBufferWrapper* ibW = renderer->CreateIndexBuffer(indices, indicesForSubset);
					indexBuffers.push_back(ibW);

					delete[] indices;

					++i;
					++j;
				}
			}
		}
	}

	void Object3D::Render(Renderer* renderer)
	{
		int	amountOfVertices = _Mesh->_nVertices;

		Vertex* d3dVertices = new Vertex[amountOfVertices];

		if (_cAnimationSet == NULL)
		{
			for (int i = 0; i < amountOfVertices; ++i)//first do all the vertices, then set the indices to the right vertices
			{
				Vertex newVertex;
				newVertex.x = _Mesh->_Vertices[i].x;
				newVertex.y = _Mesh->_Vertices[i].y;
				newVertex.z = _Mesh->_Vertices[i].z;
				newVertex.tu = _Mesh->_Vertices[i].tu;
				newVertex.tv = _Mesh->_Vertices[i].tv;
				d3dVertices[i] = newVertex;
			}
		}
		else
		{
			for (int i = 0; i < amountOfVertices; ++i)//first do all the vertices, then set the indices to the right vertices
			{
				Vertex newVertex;
				newVertex.x = _SkinnedVertices[i].x;
				newVertex.y = _SkinnedVertices[i].y;
				newVertex.z = _SkinnedVertices[i].z;
				newVertex.tu = _SkinnedVertices[i].tu;
				newVertex.tv = _SkinnedVertices[i].tv;
				d3dVertices[i] = newVertex;
			}
		}

		VertexBufferWrapper* vbWrapper = renderer->CreateVertexBuffer(d3dVertices, amountOfVertices);

		unsigned int counter = 0;
		for (auto it = indexBuffers.begin(); it != indexBuffers.end(); ++it)
		{
			renderer->SetMaterial(_Mesh->_Materials[counter]);
			counter++;
			renderer->DrawIndexedVertexBuffer(vbWrapper, (*it));
		}

		delete vbWrapper;
		delete[] d3dVertices;
	}

	ObjectBone* Object3D::ReplicateSkeleton(Bone* &pBone)
	{
		if (pBone != NULL)
		{
			ObjectBone* NBone = new ObjectBone;

			NBone->_BoneName = pBone->_Name;
			NBone->_Bone = pBone;
			NBone->_TransformMatrix = pBone->_MatrixPos;

			if (!pBone->_Bones.empty())
			{
				for (std::list<Bone*>::iterator i = pBone->_Bones.begin(); i != pBone->_Bones.end(); i++)
				{
					NBone->_Bones.push_back(ReplicateSkeleton(*i));
				}
			}
			return NBone;
		}
		else
		{
			return NULL;
		}
	}

	void Object3D::GetBoneAnimation(ObjectBone* &pBone)
	{
		pBone->_Animation = _cAnimationSet->FindAnimation(pBone->_BoneName);
		if (pBone->_Animation == 0)
		{
			//logger->LogAll(Logger::INFO, "Object3D: ", pBone->_BoneName, " is not linked to an animation.");
		}
		pBone->_AnimationIndexMat = 0;
		pBone->_AnimationIndexR = 0;
		pBone->_AnimationIndexS = 0;
		pBone->_AnimationIndexT = 0;
		if (!pBone->_Bones.empty())
		{
			for (std::list<ObjectBone*>::iterator i = pBone->_Bones.begin(); i != pBone->_Bones.end(); i++)
			{
				GetBoneAnimation(*i);
			}
		}
	}

	void Object3D::CalcAttitude(ObjectBone* pBone, ObjectBone* pParentBone)
	{
		pBone->CalcAttitude(pParentBone);
		if (!pBone->_Bones.empty())
		{
			for (std::list<ObjectBone*>::iterator i = pBone->_Bones.begin(); i != pBone->_Bones.end(); i++)
			{
				CalcAttitude(*i, pBone);
			}
		}
	}

	void Object3D::CalcAnimation(ObjectBone* &pBone)
	{
		pBone->CalcAnimation(_cKey);
		if (!pBone->_Bones.empty())
		{
			for (std::list<ObjectBone*>::iterator i = pBone->_Bones.begin(); i != pBone->_Bones.end(); i++)
			{
				CalcAnimation(*i);
			}
		}
	}

	void Object3D::CalcBindSpace(ObjectBone* &pBone)
	{
		pBone->CalcBindSpace();
		if (!pBone->_Bones.empty())
		{
			for (std::list<ObjectBone*>::iterator i = pBone->_Bones.begin(); i != pBone->_Bones.end(); i++)
			{
				CalcBindSpace(*i);
			}
		}
	}

	void Object3D::SkinMesh(ObjectBone* pBone)
	{
		if (!pBone->_Bones.empty())
		{
			//logger->LogAll(Logger::DEBUG, "Object3D: Bones is not empty");
			for (std::list<ObjectBone*>::iterator i = pBone->_Bones.begin(); i != pBone->_Bones.end(); i++)
			{
				SkinMesh(*i);
			}
		}

		Vertex* MeshVertices = _Mesh->_Vertices;
		uint32 nIndices = pBone->_Bone->_nVertices;
		uint16* VertexIndices = pBone->_Bone->_Vertices;
		float* Weights = pBone->_Bone->_Weights;

		for (unsigned int i = 0; i < nIndices; i++)
		{
			_SkinnedVertices[VertexIndices[i]] = _SkinnedVertices[VertexIndices[i]] + (pBone->_FinalMatrix * MeshVertices[VertexIndices[i]]) * Weights[i];
		}

	}

	void Object3D::CreateCollisionBox(BEAM& rect)
	{
		float minx, miny, minz;
		float maxx, maxy, maxz;

		//Initialise at first values
		minx = this->_Mesh->_Vertices[0].x;
		maxx = this->_Mesh->_Vertices[0].x;
		miny = this->_Mesh->_Vertices[0].y;
		maxy = this->_Mesh->_Vertices[0].y;
		minz = this->_Mesh->_Vertices[0].z;
		maxz = this->_Mesh->_Vertices[0].z;

		for (int i = 0; i < this->_Mesh->_nVertices; ++i)
		{
			// Check min values 
			if (this->_Mesh->_Vertices[i].x < minx)
			{
				minx = this->_Mesh->_Vertices[i].x;
			}
			if (this->_Mesh->_Vertices[i].y < miny)
			{
				miny = this->_Mesh->_Vertices[i].y;
			}
			if (this->_Mesh->_Vertices[i].z < minz)
			{
				minz = this->_Mesh->_Vertices[i].z;
			}

			// Check max values
			if (this->_Mesh->_Vertices[i].x > maxx)
			{
				maxx = this->_Mesh->_Vertices[i].x;
			}
			if (this->_Mesh->_Vertices[i].y > maxy)
			{
				maxy = this->_Mesh->_Vertices[i].y;
			}
			if (this->_Mesh->_Vertices[i].z > maxz)
			{
				maxz = this->_Mesh->_Vertices[i].z;
			}
		}

		// Calculate the rectangle 
		rect.x = _Skeleton->_Bone->_MatrixPos[12];
		rect.y = _Skeleton->_Bone->_MatrixPos[13];
		rect.z = _Skeleton->_Bone->_MatrixPos[14];

		rect.width = maxx - minx;
		rect.height = maxy - miny;
		rect.depth = maxz - minz;

		rect.frontBottomLeft = { minx, miny, maxz };
		rect.frontBottomRight = { maxx, miny, maxz };
		rect.backBottomLeft = { minx, miny, minz };
		rect.backBottomRight = { maxx, miny, minz };

		rect.frontTopLeft = { minx, maxy, maxz };
		rect.frontTopRight = { maxx, maxy, maxz };
		rect.backTopLeft = { minx, maxy, minz };
		rect.backTopRight = { maxx, maxy, minz };
	}

	void Object3D::ComputeBoundingBoxSphere(void)
	{
		_Low = _SkinnedVertices[0];
		_High = _Low;
		_Center = _Low;
		_Radius = 0.0f;
		for (int i = 0; i < _Mesh->_nVertices; i++)
		{
			if (_Low.x> _SkinnedVertices[i].x)
			{
				_Low.x = _SkinnedVertices[i].x;
			}
			if (_Low.y > _SkinnedVertices[i].y)
			{
				_Low.y = _SkinnedVertices[i].y;
			}
			if (_Low.z > _SkinnedVertices[i].z)
			{
				_Low.z = _SkinnedVertices[i].z;
			}
			if (_High.x < _SkinnedVertices[i].x)
			{
				_High.x = _SkinnedVertices[i].x;
			}
			if (_High.y < _SkinnedVertices[i].y)
			{
				_High.y = _SkinnedVertices[i].y;
			}
			if (_High.z < _SkinnedVertices[i].z)
			{
				_High.z = _SkinnedVertices[i].z;
			}
		}
		_Center.x = _Low.x + (_High.x - _Low.x)*0.5f;
		_Center.y = _Low.y + (_High.y - _Low.y)*0.5f;
		_Center.z = _Low.z + (_High.z - _Low.z)*0.5f;

		/*logger->LogAll(Logger::DEBUG, "Object3D: ", "AABB Low: ", _Low[0], "x", _Low[1], "x", _Low[2]);
		logger->LogAll(Logger::DEBUG, "Object3D: ", "AABB High: ", _High[0], "x", _High[1], "x", _High[2]);
		logger->LogAll(Logger::DEBUG, "Object3D: ", "AABB Center: ", _Center[0], "x", _Center[1], "x", _Center[2]);*/
	}
}