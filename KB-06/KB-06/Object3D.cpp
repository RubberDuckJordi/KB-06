////////////////////////////////////////////////////////////////
// Object3D_GL.cpp
// OpenGL 3DObject implmentation
//
////////////////////////////////////////////////////////////////

#include "Object3D.h"

#include "DirectXRenderer.h"//HACKING
#include "CustomD3DVertex.h"

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
	logger->LogAll(0, "Object3D:", _Model->_AnimationSets.size(), "Animation Sets. Playing:", index);
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

void Object3D::Draw(pengine::Renderer* renderer)
{
	Face TempFace;

	//pengine::DirectXRenderer meow;
	LPDIRECT3DDEVICE9 g_pd3dDevice = *((pengine::DirectXRenderer*)renderer)->GetDevice();

	/*while (j != _Mesh->_Materials.end())
	{
	//renderer->SetMaterial(*j);
	TempSubset = *i;
	//glBegin(GL_TRIANGLES);
	for (int k = 0; k < TempSubset->Size; k++)
	{
	TempFace = TempSubset->Faces[k];
	glTexCoord2fv(_Mesh->_TextureCoords[TempFace.data[0]].data);
	glVertex3fv(_SkinnedVertices[TempFace.data[0]].data);
	//glTexCoord2fv(_Mesh->_TextureCoords[TempFace.data[1]].data);
	//glVertex3fv(_SkinnedVertices[TempFace.data[1]].data);
	//glTexCoord2fv(_Mesh->_TextureCoords[TempFace.data[2]].data);
	//glVertex3fv(_SkinnedVertices[TempFace.data[2]].data);
	}
	//glEnd();
	i++;
	j++;
	}*/


	//logger->Log(Logger::DEBUG, "Mesh \"" + mesh->fileName + "\" not converted to LPD3DXMESH yet.");

	LPD3DXMESH d3dMesh;
	int	amountOfVertices = 0;
	int amountOfIndices = 0;

	amountOfVertices = _Mesh->_nVertices;
	amountOfIndices = _Mesh->_nVertices * 3;

	if (FAILED(D3DXCreateMeshFVF(amountOfIndices, amountOfVertices, 0, D3DCustomVertexFVF, g_pd3dDevice, &d3dMesh)))
	{
		logger->Log(pengine::Logger::ERR, "Failed to create a D3DXCreateMeshFVF. Generating a cube");
		D3DXCreateBox(g_pd3dDevice, 1.0f, 1.0f, 1.0f, &d3dMesh, NULL);
	}
	else
	{
		D3DCustomVertex* d3dVertices = new D3DCustomVertex[amountOfVertices];
		unsigned short* indices = new unsigned short[amountOfIndices * 3];

		int vertexCount = -1;
		int indexCount = -1;
		/*for (unsigned int i = 0; i < mesh->subsets.size(); ++i)
		{
		for (unsigned int j = 0; j < mesh->subsets.at(i).vertices.size(); ++j)
		{
		D3DCustomVertex newVertex;
		newVertex.x = mesh->subsets.at(i).vertices.at(j).x;
		newVertex.y = mesh->subsets.at(i).vertices.at(j).y;
		newVertex.z = mesh->subsets.at(i).vertices.at(j).z;
		newVertex.tu = mesh->subsets.at(i).textureCoordinates.at(j).u;
		newVertex.tv = mesh->subsets.at(i).textureCoordinates.at(j).v;
		d3dVertices[++vertexCount] = newVertex;
		}
		for (unsigned int j = 0; j < mesh->subsets.at(i).faceDefinitions.size(); ++j)
		{
		indices[++indexCount] = mesh->subsets.at(i).faceDefinitions.at(j).v1;
		indices[++indexCount] = mesh->subsets.at(i).faceDefinitions.at(j).v2;
		indices[++indexCount] = mesh->subsets.at(i).faceDefinitions.at(j).v3;
		int test = 10;
		}
		}*/
		//logger->LogAll(0, "MEOW", _Mesh->_nVertices);
		for (int i = 0; i < _Mesh->_nVertices; ++i)
		{
			/*logger->LogAll(0, "GARGAR", _Mesh->_Vertices[i].data[0]);
			logger->LogAll(0, "GARGAR2", _Mesh->_Vertices[i].data[1]);
			logger->LogAll(0, "GARGAR3", _Mesh->_Vertices[i].data[2]);*/

			D3DCustomVertex newVertex;
			TempFace = _Mesh->_Faces[i];
			newVertex.x = _Mesh->_Vertices[i].data[0];// _SkinnedVertices[TempFace.data[0]].data[0];//just hoping this is x...
			newVertex.y = _Mesh->_Vertices[i].data[1];// _SkinnedVertices[TempFace.data[0]].data[1];//just hoping this is y...
			newVertex.z = _Mesh->_Vertices[i].data[2];// _SkinnedVertices[TempFace.data[0]].data[2];//just hoping this is z...
			newVertex.tu = _Mesh->_TextureCoords[TempFace.data[0]].data[0];//just hoping this is tu...
			newVertex.tv = _Mesh->_TextureCoords[TempFace.data[0]].data[1];//just hoping this is tv...

			/*newVertex.x = _SkinnedVertices[TempFace.data[1]].data[0];//just hoping this is x...
			newVertex.y = _SkinnedVertices[TempFace.data[1]].data[1];//just hoping this is y...
			newVertex.z = _SkinnedVertices[TempFace.data[1]].data[2];//just hoping this is z...
			newVertex.tu = _Mesh->_TextureCoords[TempFace.data[1]].data[0];//just hoping this is tu...
			newVertex.tv = _Mesh->_TextureCoords[TempFace.data[1]].data[1];//just hoping this is tv...

			newVertex.x = _SkinnedVertices[TempFace.data[2]].data[0];//just hoping this is x...
			newVertex.y = _SkinnedVertices[TempFace.data[2]].data[1];//just hoping this is y...
			newVertex.z = _SkinnedVertices[TempFace.data[2]].data[2];//just hoping this is z...
			newVertex.tu = _Mesh->_TextureCoords[TempFace.data[2]].data[0];//just hoping this is tu...
			newVertex.tv = _Mesh->_TextureCoords[TempFace.data[2]].data[1];//just hoping this is tv...*/

			indices[++indexCount] = indexCount;//not sure...
			indices[++indexCount] = indexCount;//not sure...
			indices[++indexCount] = indexCount;//not sure...


			d3dVertices[++vertexCount] = newVertex;
		}
		//std::list<Subset*>::iterator i = _Mesh->_Subsets.begin();
		//std::list<XMaterial*>::iterator j = _Mesh->_Materials.begin();

		/*while (i != _Mesh->_Subsets.end())
		{
			Subset* TempSubset = *i;

			for (int k = 0; k < TempSubset->Size; k++)
			{
				D3DCustomVertex newVertex;
				TempFace = TempSubset->Faces[k];
				//glTexCoord2fv(_Mesh->_TextureCoords[TempFace.data[0]].data);
				//glVertex3fv(_SkinnedVertices[TempFace.data[0]].data);
				//glTexCoord2fv(_Mesh->_TextureCoords[TempFace.data[1]].data);
				//glVertex3fv(_SkinnedVertices[TempFace.data[1]].data);
				//glTexCoord2fv(_Mesh->_TextureCoords[TempFace.data[2]].data);
				//glVertex3fv(_SkinnedVertices[TempFace.data[2]].data);
				newVertex.x = _SkinnedVertices[TempFace.data[0]].data[0];//just hoping this is x...
				newVertex.y = _SkinnedVertices[TempFace.data[0]].data[1];//just hoping this is y...
				newVertex.z = _SkinnedVertices[TempFace.data[0]].data[2];//just hoping this is z...
				newVertex.tu = _Mesh->_TextureCoords[TempFace.data[0]].data[0];//just hoping this is tu...
				newVertex.tv = _Mesh->_TextureCoords[TempFace.data[0]].data[1];//just hoping this is tv...

				newVertex.x = _SkinnedVertices[TempFace.data[1]].data[0];//just hoping this is x...
				newVertex.y = _SkinnedVertices[TempFace.data[1]].data[1];//just hoping this is y...
				newVertex.z = _SkinnedVertices[TempFace.data[1]].data[2];//just hoping this is z...
				newVertex.tu = _Mesh->_TextureCoords[TempFace.data[1]].data[0];//just hoping this is tu...
				newVertex.tv = _Mesh->_TextureCoords[TempFace.data[1]].data[1];//just hoping this is tv...

				newVertex.x = _SkinnedVertices[TempFace.data[2]].data[0];//just hoping this is x...
				newVertex.y = _SkinnedVertices[TempFace.data[2]].data[1];//just hoping this is y...
				newVertex.z = _SkinnedVertices[TempFace.data[2]].data[2];//just hoping this is z...
				newVertex.tu = _Mesh->_TextureCoords[TempFace.data[2]].data[0];//just hoping this is tu...
				newVertex.tv = _Mesh->_TextureCoords[TempFace.data[2]].data[1];//just hoping this is tv...

				indices[++indexCount] = indexCount;//not sure...
				indices[++indexCount] = indexCount;//not sure...
				indices[++indexCount] = indexCount;//not sure...


				d3dVertices[++vertexCount] = newVertex;
			}

			++i;
			++j;

		}*/

		VOID* pVoid;

		LPDIRECT3DVERTEXBUFFER9 v_buffer;
		d3dMesh->GetVertexBuffer(&v_buffer);
		// lock v_buffer and load the vertices into it
		v_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, d3dVertices, amountOfVertices*sizeof(D3DCustomVertex));
		v_buffer->Unlock();

		LPDIRECT3DINDEXBUFFER9 i_buffer;
		d3dMesh->GetIndexBuffer(&i_buffer);
		// lock i_buffer and load the indices into it
		i_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, indices, amountOfIndices * 3 * sizeof(unsigned short));
		i_buffer->Unlock();

		//logger->Log(pengine::Logger::DEBUG, "Mesh \"" + mesh->fileName + "\" converted to LPD3DXMESH.");

		/*if (mesh->fileName == "resources/cubeClone.obj.mesh")
		{
		//D3DXCreateBox(g_pd3dDevice, 1.0f, 1.0f, 1.0f, &d3dMesh, NULL);
		D3DXCreateSphere(g_pd3dDevice, 1.0f, 10, 10, &d3dMesh, NULL);
		logger->Log(3, "The meow is great in this one.");
		}
		if (mesh->fileName == "resources/cubeCloneClone.obj.mesh")
		{
		D3DXCreateTeapot(g_pd3dDevice, &d3dMesh, NULL);
		logger->Log(3, "The meow is greater in this one.");
		}*/

		g_pd3dDevice->SetStreamSource(0, v_buffer, 0, sizeof(D3DCustomVertex));
		g_pd3dDevice->SetFVF(D3DCustomVertexFVF);
		g_pd3dDevice->SetIndices(i_buffer);
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,// PrimitiveType
			0,// BaseVertexIndex
			0,// MinIndex
			amountOfVertices,// NumVertices
			0,// StartIndex
			amountOfVertices / 3);// PrimitiveCount
	}
	//meshCache[mesh] = d3dMesh;
	//D3DXSaveMeshToX(L"test.x", d3dMesh, NULL, NULL, NULL, 0, 1); //save mesh to xfile to debug


	/*for (unsigned int i = 0; i < mesh->subsets.size(); ++i){ // So we start at 1 instead of 0
		SetMaterial(&mesh->subsets.at(i).defaultMaterial);
		SetTexture(&mesh->subsets.at(i).defaultMaterial.defaultTexture);
		meshCache[mesh]->DrawSubset(i);

		}*/
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
		logger->LogAll(0, "Object3D:", pBone->_BoneName, "is not linked to an animation.");
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
		//for (std::list<ObjectBone*>::iterator i = pBone->_Bones.begin(); i != pBone->_Bones.end(); i++)
		//{
		//SkinMesh(pBone->_Bones.pop_front());/**/
		//}
	}

	Vertex* MeshVertices = _Mesh->_Vertices;
	uint32 nIndices = pBone->_Bone->_nVertices;
	uint16* VertexIndices = pBone->_Bone->_Vertices;
	float* Weights = pBone->_Bone->_Weights;

	for (int i = 0; i < nIndices; i++)
	{
		_SkinnedVertices[VertexIndices[i]] = _SkinnedVertices[VertexIndices[i]] + (pBone->_FinalMatrix * MeshVertices[VertexIndices[i]]) * Weights[i];
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
		if (_Low[0]> _SkinnedVertices[i][0])
		{
			_Low[0] = _SkinnedVertices[i][0];
		}
		if (_Low[1] > _SkinnedVertices[i][1])
		{
			_Low[1] = _SkinnedVertices[i][1];
		}
		if (_Low[2] > _SkinnedVertices[i][2])
		{
			_Low[2] = _SkinnedVertices[i][2];
		}
		if (_High[0] < _SkinnedVertices[i][0])
		{
			_High[0] = _SkinnedVertices[i][0];
		}
		if (_High[1] < _SkinnedVertices[i][1])
		{
			_High[1] = _SkinnedVertices[i][1];
		}
		if (_High[2] < _SkinnedVertices[i][2])
		{
			_High[2] = _SkinnedVertices[i][2];
		}
	}
	_Center[0] = _Low[0] + (_High[0] - _Low[0])*0.5f;
	_Center[1] = _Low[1] + (_High[1] - _Low[1])*0.5f;
	_Center[2] = _Low[2] + (_High[2] - _Low[2])*0.5f;

	logger->LogAll(0, "Object3D:", "AABB Low:", _Low[0], "x", _Low[1], "x", _Low[2]);
	logger->LogAll(0, "Object3D:", "AABB High:", _High[0], "x", _High[1], "x", _High[2]);
	logger->LogAll(0, "Object3D:", "AABB Center:", _Center[0], "x", _Center[1], "x", _Center[2]);

}
