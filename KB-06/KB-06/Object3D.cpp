#include "Object3D.h"

#include "Vertex.h"

namespace pengine
{

	Object3D::Object3D() :skeleton(NULL), _SkinnedVertices(NULL), _Model(NULL), animationstep(1)
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
		memset(_SkinnedVertices, 0, _Mesh->nVertices * sizeof(Vertex));
	}

	void Object3D::SetAnimationStep(uint16 pStep)
	{
		animationstep = pStep;
	}

	void Object3D::UpdateAnimation()
	{
		if (_cAnimationSet != NULL)
		{
			ClearSkinnedVertices();
			_cKey += animationstep;
			if (_cKey > _cAnimationSet->maxKey)
			{
				_cKey = 0;
			}
			CalcAnimation(skeleton);
			ComputeBoundingBoxSphere();
			CalcAttitude(skeleton, 0);
			SkinMesh(skeleton);
		}
	}

	void Object3D::UpdateBindSpace(void)
	{
		CalcBindSpace(skeleton);
		CalcAttitude(skeleton, 0);
		SkinMesh(skeleton);
	}

	void Object3D::CalcAnimation(void)
	{
		_cKey += animationstep;
		if (_cKey > _cAnimationSet->maxKey)
		{
			_cKey = 0;
		}
		CalcAnimation(skeleton);
		ComputeBoundingBoxSphere();
	}

	void Object3D::CalcBindSpace(void)
	{
		CalcBindSpace(skeleton);
	}

	void Object3D::Update(void)
	{
		CalcAttitude(skeleton, 0);
		SkinMesh(skeleton);
	}

	void Object3D::SetupModel(Model3D* &pModel)
	{
		_Model = pModel;
		_Mesh = _Model->meshes.back();
		_SkinnedVertices = new Vertex[_Mesh->nVertices]();
		skeleton = ReplicateSkeleton(_Model->skeleton);
	}

	void Object3D::MapAnimationSet(std::string pText)
	{
		_cAnimationSet = _Model->FindAnimationSet(pText);
		_cKey = 0;
		if (_cAnimationSet != 0)
		{
			GetBoneAnimation(skeleton);
		}
	}

	void Object3D::MapAnimationSet(uint16 &index)
	{
		if (_Model->animationsets.size() == 0)
		{
			return;
		}
		if (index >= _Model->animationsets.size())
		{
			index = 0;
		}
		//logger->LogAll(Logger::INFO, "Object3D: ", _Model->animationsets.size(), " Animation Sets. Playing: ", index);

		std::list<AnimationSet*>::iterator i = _Model->animationsets.begin();
		if (index != 0)
		{
			int16 test = index;
			while (test--)
			{
				i++;
			}
		}
		_cAnimationSet = (*i);

		GetBoneAnimation(skeleton);
		_cKey = 0;
	}

	void Object3D::CacheToRenderer(Renderer* renderer)
	{
		if (indexBuffers.size() == 0)
		{
			if (_Mesh->subsets.size() == 0)
			{
				unsigned int counter = 0;
				for (auto i = _Mesh->materials.begin(); i != _Mesh->materials.end(); ++i)
				{
					std::list<Face> facesToDraw;
					for (unsigned int j = 0; j < _Mesh->nFaces; ++j)
					{
						int ffs = _Mesh->faceMaterials[j];
						if (_Mesh->faceMaterials[j] == counter)
						{
							facesToDraw.push_back(_Mesh->faces[j]);
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
				auto i = _Mesh->subsets.begin();
				auto j = _Mesh->materials.begin();

				while (j != _Mesh->materials.end())
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
		int	amountOfVertices = _Mesh->nVertices;
		Vertex* d3dVertices = new Vertex[amountOfVertices];

		if (_cAnimationSet == NULL)
		{
			for (int i = 0; i < amountOfVertices; ++i)//first do all the vertices, then set the indices to the right vertices
			{
				Vertex newVertex;
				newVertex.x = _Mesh->vertices[i].x;
				newVertex.y = _Mesh->vertices[i].y;
				newVertex.z = _Mesh->vertices[i].z;
				newVertex.tu = _Mesh->vertices[i].tu;
				newVertex.tv = _Mesh->vertices[i].tv;
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
			renderer->SetMaterial(_Mesh->materials[counter]);
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

			NBone->boneName = pBone->name;
			NBone->bone = pBone;
			NBone->transformMatrix = pBone->matrixPos;

			if (!pBone->bones.empty())
			{
				for (std::list<Bone*>::iterator i = pBone->bones.begin(); i != pBone->bones.end(); i++)
				{
					NBone->bones.push_back(ReplicateSkeleton(*i));
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
		pBone->animation = _cAnimationSet->FindAnimation(pBone->boneName);
		if (pBone->animation == 0)
		{
			//logger->LogAll(Logger::INFO, "Object3D: ", pBone->boneName, " is not linked to an animation.");
		}
		pBone->animationIndexMat = 0;
		pBone->animationIndexR = 0;
		pBone->animationIndexS = 0;
		pBone->animationIndexT = 0;
		if (!pBone->bones.empty())
		{
			for (std::list<ObjectBone*>::iterator i = pBone->bones.begin(); i != pBone->bones.end(); i++)
			{
				GetBoneAnimation(*i);
			}
		}
	}

	void Object3D::CalcAttitude(ObjectBone* pBone, ObjectBone* pParentBone)
	{
		pBone->CalcAttitude(pParentBone);
		if (!pBone->bones.empty())
		{
			for (std::list<ObjectBone*>::iterator i = pBone->bones.begin(); i != pBone->bones.end(); i++)
			{
				CalcAttitude(*i, pBone);
			}
		}
	}

	void Object3D::CalcAnimation(ObjectBone* &pBone)
	{
		pBone->CalcAnimation(_cKey);
		if (!pBone->bones.empty())
		{
			for (std::list<ObjectBone*>::iterator i = pBone->bones.begin(); i != pBone->bones.end(); i++)
			{
				CalcAnimation(*i);
			}
		}
	}

	void Object3D::CalcBindSpace(ObjectBone* &pBone)
	{
		pBone->CalcBindSpace();
		if (!pBone->bones.empty())
		{
			for (std::list<ObjectBone*>::iterator i = pBone->bones.begin(); i != pBone->bones.end(); i++)
			{
				CalcBindSpace(*i);
			}
		}
	}

	void Object3D::SkinMesh(ObjectBone* pBone)
	{
		if (!pBone->bones.empty())
		{
			//logger->LogAll(Logger::DEBUG, "Object3D: Bones is not empty");
			for (std::list<ObjectBone*>::iterator i = pBone->bones.begin(); i != pBone->bones.end(); i++)
			{
				SkinMesh(*i);
			}
		}

		Vertex* MeshVertices = _Mesh->vertices;
		uint32 nIndices = pBone->bone->nVertices;
		uint16* VertexIndices = pBone->bone->vertices;
		float* Weights = pBone->bone->weights;

		for (unsigned int i = 0; i < nIndices; i++)
		{
			_SkinnedVertices[VertexIndices[i]] = _SkinnedVertices[VertexIndices[i]] + (pBone->finalMatrix * MeshVertices[VertexIndices[i]]) * Weights[i];
		}
	}

	void Object3D::CreateCollisionBox(BEAM& rect)
	{
		float minx, miny, minz;
		float maxx, maxy, maxz;

		//Initialise at first values
		minx = this->_Mesh->vertices[0].x;
		maxx = this->_Mesh->vertices[0].x;
		miny = this->_Mesh->vertices[0].y;
		maxy = this->_Mesh->vertices[0].y;
		minz = this->_Mesh->vertices[0].z;
		maxz = this->_Mesh->vertices[0].z;

		for (int i = 0; i < this->_Mesh->nVertices; ++i)
		{
			// Check min values 
			if (this->_Mesh->vertices[i].x < minx)
			{
				minx = this->_Mesh->vertices[i].x;
			}
			if (this->_Mesh->vertices[i].y < miny)
			{
				miny = this->_Mesh->vertices[i].y;
			}
			if (this->_Mesh->vertices[i].z < minz)
			{
				minz = this->_Mesh->vertices[i].z;
			}

			// Check max values
			if (this->_Mesh->vertices[i].x > maxx)
			{
				maxx = this->_Mesh->vertices[i].x;
			}
			if (this->_Mesh->vertices[i].y > maxy)
			{
				maxy = this->_Mesh->vertices[i].y;
			}
			if (this->_Mesh->vertices[i].z > maxz)
			{
				maxz = this->_Mesh->vertices[i].z;
			}
		}

		// Calculate the rectangle 
		rect.x = skeleton->bone->matrixPos[12];
		rect.y = skeleton->bone->matrixPos[13];
		rect.z = skeleton->bone->matrixPos[14];

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

	float Object3D::GetMinZ()
	{
		float  minz;
		minz = this->_Mesh->vertices[0].z;
		for (int i = 0; i < this->_Mesh->nVertices; ++i)
		{
			if (this->_Mesh->vertices[i].z < minz)
			{
				minz = this->_Mesh->vertices[i].z;
			}
		}
		return minz;
	}

	float Object3D::GetMaxZ()
	{
		float  maxz;
		maxz = this->_Mesh->vertices[0].z;
		for (int i = 0; i < this->_Mesh->nVertices; ++i)
		{
			if (this->_Mesh->vertices[i].z > maxz)
			{
				maxz = this->_Mesh->vertices[i].z;
			}
		}
		return maxz;
	}

	float Object3D::GetMinX()
	{
		float  minx;
		minx = this->_Mesh->vertices[0].x;
		for (int i = 0; i < this->_Mesh->nVertices; ++i)
		{
			if (this->_Mesh->vertices[i].x < minx)
			{
				minx = this->_Mesh->vertices[i].x;
			}
		}
		return minx;
	}

	float Object3D::GetMaxX()
	{
		float  maxx;
		maxx = this->_Mesh->vertices[0].x;
		for (int i = 0; i < this->_Mesh->nVertices; ++i)
		{
			if (this->_Mesh->vertices[i].x > maxx)
			{
				maxx = this->_Mesh->vertices[i].x;
			}
		}
		return maxx;
	}

	float Object3D::GetMinY()
	{
		float  miny;
		miny = this->_Mesh->vertices[0].y;
		for (int i = 0; i < this->_Mesh->nVertices; ++i)
		{
			if (this->_Mesh->vertices[i].y < miny)
			{
				miny = this->_Mesh->vertices[i].y;
			}
		}
		return miny;
	}

	float Object3D::GetMaxY()
	{
		float  maxy;
		maxy = this->_Mesh->vertices[0].y;
		for (int i = 0; i < this->_Mesh->nVertices; ++i)
		{
			if (this->_Mesh->vertices[i].y > maxy)
			{
				maxy = this->_Mesh->vertices[i].y;
			}
		}
		return maxy;
	}

	void Object3D::ComputeBoundingBoxSphere()
	{
		low = Vector3();
		high = low;
		center = low;
		for (int i = 0; i < _Mesh->nVertices; i++)
		{
			if (low.x> _SkinnedVertices[i].x)
			{
				low.x = _SkinnedVertices[i].x;
			}
			if (low.y > _SkinnedVertices[i].y)
			{
				low.y = _SkinnedVertices[i].y;
			}
			if (low.z > _SkinnedVertices[i].z)
			{
				low.z = _SkinnedVertices[i].z;
			}
			if (high.x < _SkinnedVertices[i].x)
			{
				high.x = _SkinnedVertices[i].x;
			}
			if (high.y < _SkinnedVertices[i].y)
			{
				high.y = _SkinnedVertices[i].y;
			}
			if (high.z < _SkinnedVertices[i].z)
			{
				high.z = _SkinnedVertices[i].z;
			}
		}
		center.x = low.x + (high.x - low.x) * 0.5f;
		center.y = low.y + (high.y - low.y) * 0.5f;
		center.z = low.z + (high.z - low.z) * 0.5f;
	}

	float Object3D::GetMaxRadius()
	{
		float result = 0.0f;

		if (_Model->animationsets.size() > 1)
		{
			for (int i = 0; i < this->_Mesh->nVertices; ++i)
			{
				float working = sqrt(pow(_SkinnedVertices[i].x, 2) + pow(_SkinnedVertices[i].y, 2) + pow(_SkinnedVertices[i].z, 2));
				if (working > result)
				{
					result = working;
				}
			}
		}
		else
		{
			for (int i = 0; i < this->_Mesh->nVertices; ++i)
			{
				float working = sqrt(pow(_Mesh->vertices[i].x, 2) + pow(_Mesh->vertices[i].y, 2) + pow(_Mesh->vertices[i].z, 2)); if (working > result)
				{
					result = working;
				}
			}
		}
		return result;
	}
}