////////////////////////////////////////////////////////////////
// Object3D_GL.cpp
// OpenGL 3DObject implmentation
//
////////////////////////////////////////////////////////////////

#include "Object3D.h"

#include "DirectXRenderer.h"//HACKING
#include "CustomD3DVertex.h"

namespace pengine
{
	void Object3D::MapAnimationSet(std::string pText)
	{
		_cAnimationSet = _Model->FindAnimationSet(pText);
		_cKey = 0;
		if (_cAnimationSet != 0)
		{
			GetBoneAnimation(_Skeletton);
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

		GetBoneAnimation(_Skeletton);
		_cKey = 0;
	}

	void Object3D::Draw(Renderer* renderer)
	{
		LPDIRECT3DDEVICE9 g_pd3dDevice = *((DirectXRenderer*)renderer)->GetDevice();

		LPD3DXMESH d3dMesh;
		int	amountOfVertices = _Mesh->_nVertices;

		if (FAILED(D3DXCreateMeshFVF(_Mesh->_nFaces * 3, amountOfVertices, 0, D3DCustomVertexFVF, g_pd3dDevice, &d3dMesh)))
		{
			logger->Log(Logger::ERR, "Failed to create a D3DXCreateMeshFVF. Generating a cube");
			D3DXCreateBox(g_pd3dDevice, 1.0f, 1.0f, 1.0f, &d3dMesh, NULL);
		}
		else
		{
			D3DCustomVertex* d3dVertices = new D3DCustomVertex[amountOfVertices];

			for (int i = 0; i < amountOfVertices; ++i)//first do all the vertices, then set the indices to the right vertices
			{
				D3DCustomVertex newVertex;
				newVertex.x = _Mesh->_Vertices[i].x;//x
				newVertex.y = _Mesh->_Vertices[i].y;//y
				newVertex.z = _Mesh->_Vertices[i].z;//z
				newVertex.tu = _Mesh->_Vertices[i].tu;
				newVertex.tv = _Mesh->_Vertices[i].tv;
				d3dVertices[i] = newVertex;
			}

			void* pVoid;
			LPDIRECT3DVERTEXBUFFER9 v_buffer;
			d3dMesh->GetVertexBuffer(&v_buffer);
			// lock v_buffer and load the vertices into it
			v_buffer->Lock(0, 0, (void**)&pVoid, 0);
			memcpy(pVoid, d3dVertices, amountOfVertices*sizeof(D3DCustomVertex));
			v_buffer->Unlock();

			g_pd3dDevice->SetStreamSource(0, v_buffer, 0, sizeof(D3DCustomVertex));
			g_pd3dDevice->SetFVF(D3DCustomVertexFVF);
			_Model->_Meshes;

			if (_Mesh->_Subsets.size() == 0)
			{
				//				logger->Log(Logger::DEBUG, "Object3D: We have no subsets to render!");
				Face tempFace;
				std::list<Material*>::iterator j = _Mesh->_Materials.begin();

				renderer->SetMaterial(_Mesh->_Materials.front());//We have one mesh, that can only have 1 texture... not true at all, needs fix

				unsigned int indicesForSubset = _Mesh->_nFaces * 3;//amount of faces * 3
				unsigned short* indices = new unsigned short[indicesForSubset];
				unsigned int currentIndex = -1;

				for (int k = 0; k < _Mesh->_nFaces; k++)
				{
					tempFace = _Mesh->_Faces[k];
					indices[++currentIndex] = tempFace.data[0];
					indices[++currentIndex] = tempFace.data[1];
					indices[++currentIndex] = tempFace.data[2];
				}

				LPDIRECT3DINDEXBUFFER9 i_buffer;
				d3dMesh->GetIndexBuffer(&i_buffer);
				// lock i_buffer and load the indices into it
				i_buffer->Lock(0, 0, (void**)&pVoid, 0);
				memcpy(pVoid, indices, indicesForSubset * sizeof(unsigned short));
				i_buffer->Unlock();

				g_pd3dDevice->SetIndices(i_buffer);
				g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,// PrimitiveType
					0,// BaseVertexIndex, adds +arg to every vertex number in the index buffer
					0,// MinIndex
					amountOfVertices,// NumVertices
					0,// StartIndex
					_Mesh->_nFaces);// PrimitiveCount
				i_buffer->Release();
				delete[] indices;
				j++;
			}
			else
			{
				Subset* tempSubset;
				Face tempFace;
				std::list<Subset*>::iterator i = _Mesh->_Subsets.begin();
				std::list<Material*>::iterator j = _Mesh->_Materials.begin();

				while (j != _Mesh->_Materials.end())
				{
					renderer->SetMaterial(*j);

					tempSubset = *i;
					unsigned int indicesForSubset = tempSubset->Size * 3;//amount of faces * 3
					unsigned short* indices = new unsigned short[indicesForSubset];
					unsigned int currentIndex = -1;

					for (int k = 0; k < tempSubset->Size; k++)
					{
						tempFace = tempSubset->Faces[k];
						indices[++currentIndex] = tempFace.data[0];
						indices[++currentIndex] = tempFace.data[1];
						indices[++currentIndex] = tempFace.data[2];
					}

					LPDIRECT3DINDEXBUFFER9 i_buffer;
					d3dMesh->GetIndexBuffer(&i_buffer);
					// lock i_buffer and load the indices into it
					i_buffer->Lock(0, 0, (void**)&pVoid, 0);
					memcpy(pVoid, indices, indicesForSubset * sizeof(unsigned short));
					i_buffer->Unlock();

					g_pd3dDevice->SetIndices(i_buffer);
					g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,// PrimitiveType
						0,// BaseVertexIndex, adds +arg to every vertex number in the index buffer
						0,// MinIndex
						amountOfVertices,// NumVertices
						0,// StartIndex
						tempSubset->Size);// PrimitiveCount
					i_buffer->Release();
					delete[] indices;

					i++;
					j++;
				}
			}

			v_buffer->Release();
			d3dMesh->Release();
			delete[] d3dVertices;
		}
	}

	ObjectBone* Object3D::ReplicateSkeletton(Bone* &pBone)
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
					NBone->_Bones.push_back(ReplicateSkeletton(*i));
				}
			}
			return NBone;
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

	void Object3D::CreateCollisionBox(RECTANGLE& rect)
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
		rect.x = minx;
		rect.y = miny;
		rect.z = minz;

		// In our first iteration of collision, we only work with cubes, no rectangles
		float largestMeasurement = maxx - minx;
		if (maxy - miny > largestMeasurement)
		{
			largestMeasurement = maxy - miny;
		}
		if (maxz - minz > largestMeasurement)
		{
			largestMeasurement = maxz - minz;
		}

		rect.width = largestMeasurement;
		rect.height = largestMeasurement;
		rect.depth = largestMeasurement;
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