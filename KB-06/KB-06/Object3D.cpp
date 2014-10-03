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
		if (index >= _Model->_AnimationSets.size())
		{
			index = 0;
		}
		//logger->LogAll(0, "Object3D: ", _Model->_AnimationSets.size(), " Animation Sets. Playing: ", index);
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
	/***END*******************************************/

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
				newVertex.x = _SkinnedVertices[i].x;//x
				newVertex.y = _SkinnedVertices[i].y;//y
				newVertex.z = _SkinnedVertices[i].z;//z
				newVertex.tu = _Mesh->_TextureCoords[i].data[0];//hopefully we got texture information for each vertex...
				newVertex.tv = _Mesh->_TextureCoords[i].data[1];//hopefully we got texture information for each vertex...
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

			//for (std::list<Subset*>::iterator i = _Mesh->_Subsets.begin(); i != _Mesh->_Subsets.end(); ++i)
			//{
			//	unsigned int indicesForSubset = (*i)->Size * 3;//amount of faces * 3
			//	unsigned short* indices = new unsigned short[indicesForSubset];
			//	for (int i = 0; i < amountOfIndices; i += 3)//now get all the indices...
			//	{
			//		indices[i] = _Mesh->_Faces[i / 3].data[0];
			//		indices[i + 1] = _Mesh->_Faces[i / 3].data[1];
			//		indices[i + 2] = _Mesh->_Faces[i / 3].data[2];
			//	}


			//	LPDIRECT3DINDEXBUFFER9 i_buffer;
			//	d3dMesh->GetIndexBuffer(&i_buffer);
			//	// lock i_buffer and load the indices into it
			//	i_buffer->Lock(0, 0, (void**)&pVoid, 0);
			//	memcpy(pVoid, indices, amountOfIndices * sizeof(unsigned short));
			//	i_buffer->Unlock();

			//	g_pd3dDevice->SetIndices(i_buffer);
			//	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,// PrimitiveType
			//		0,// BaseVertexIndex
			//		0,// MinIndex
			//		amountOfVertices,// NumVertices
			//		0,// StartIndex
			//		_Mesh->_nFaces);// PrimitiveCount
			//	i_buffer->Release();
			//	delete[] indices;
			//}

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



					/*_Mesh->_TextureCoords[tempFace.data[0]].data;
					_SkinnedVertices[tempFace.data[0]].x;
					_Mesh->_TextureCoords[tempFace.data[1]].data;
					_SkinnedVertices[tempFace.data[1]].y;
					_Mesh->_TextureCoords[tempFace.data[2]].data;
					_SkinnedVertices[tempFace.data[2]].z;*/


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

			v_buffer->Release();
			d3dMesh->Release();
			delete[] d3dVertices;
		}
	}

	ObjectBone* Object3D::ReplicateSkeletton(Bone* &pBone)
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

	/*************************************************
	NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW*/
	void Object3D::GetBoneAnimation(ObjectBone* &pBone)
	{
		pBone->_Animation = _cAnimationSet->FindAnimation(pBone->_BoneName);
		if (pBone->_Animation == 0)
		{
			//logger->LogAll(0, "Object3D: ", pBone->_BoneName, " is not linked to an animation.");
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
	/***END*******************************************/

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

	/*************************************************
	NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW*/
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
	/***END*******************************************/

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
			//logger->LogAll(0, "Object3D: Bones is not empty");
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
			//RenderMatrix::PrintMatrix(pBone->_FinalMatrix);
			//LoggerPool::GetInstance().GetLogger()->LogAll(
			//	pBone->_FinalMatrix.data[0], " : ", pBone->_FinalMatrix.data[1], " : ", pBone->_FinalMatrix.data[2], " : ", pBone->_FinalMatrix.data[3], " :\n ",
			//	pBone->_FinalMatrix.data[4], " : ", pBone->_FinalMatrix.data[5], " : ", pBone->_FinalMatrix.data[6], " : ", pBone->_FinalMatrix.data[7], " :\n ", 
			//	pBone->_FinalMatrix.data[8], " : ", pBone->_FinalMatrix.data[9], " : ", pBone->_FinalMatrix.data[10], " : ", pBone->_FinalMatrix.data[11], " :\n ", 
			//	pBone->_FinalMatrix.data[12], " : ", pBone->_FinalMatrix.data[13], " : ", pBone->_FinalMatrix.data[14], " : ", pBone->_FinalMatrix.data[15], " :\n ");
		}

	}/**/

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

		/*logger->LogAll(0, "Object3D: ", "AABB Low: ", _Low[0], "x", _Low[1], "x", _Low[2]);
		logger->LogAll(0, "Object3D: ", "AABB High: ", _High[0], "x", _High[1], "x", _High[2]);
		logger->LogAll(0, "Object3D: ", "AABB Center: ", _Center[0], "x", _Center[1], "x", _Center[2]);*/
	}
}