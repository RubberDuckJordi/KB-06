#include "Skybox.h"
#include "logger.h"

pengine::Skybox::Skybox(Renderer* renderer, std::string textureString)
{
	amountOfVertices = 24;
	amountOfIndices = 36;

	aSkyboxVertices = new D3DCustomVertex[amountOfVertices];
	aSkyboxVertices[0] = { -50.0f, -50.0f, 50.0f, 0.25f, 0.6666f };//front
	aSkyboxVertices[1] = { 50.0f, -50.0f, 50.0f, 0.50f, 0.6666f };
	aSkyboxVertices[2] = { 50.0f, 50.0f, 50.0f, 0.50f, 0.3333f };
	aSkyboxVertices[3] = { -50.0f, 50.0f, 50.0f, 0.25f, 0.3333f };
	aSkyboxVertices[4] = { 50.0f, -50.0f, 50.0f, 0.50f, 0.6666f };//right
	aSkyboxVertices[5] = { 50.0f, -50.0f, -50.0f, 0.75f, 0.6666f };
	aSkyboxVertices[6] = { 50.0f, 50.0f, -50.0f, 0.75f, 0.3333f };
	aSkyboxVertices[7] = { 50.0f, 50.0f, 50.0f, 0.50f, 0.3333f };
	aSkyboxVertices[8] = { 50.0f, -50.0f, -50.0f, 0.75f, 0.6666f };//back
	aSkyboxVertices[9] = { -50.0f, -50.0f, -50.0f, 1.0f, 0.6666f };
	aSkyboxVertices[10] = { -50.0f, 50.0f, -50.0f, 1.0f, 0.3333f };
	aSkyboxVertices[11] = { 50.0f, 50.0f, -50.0f, 0.75f, 0.3333f };
	aSkyboxVertices[12] = { -50.0f, -50.0f, -50.0f, 0.0f, 0.6666f };//left
	aSkyboxVertices[13] = { -50.0f, -50.0f, 50.0f, 0.25f, 0.6666f };
	aSkyboxVertices[14] = { -50.0f, 50.0f, 50.0f, 0.25f, 0.3333f };
	aSkyboxVertices[15] = { -50.0f, 50.0f, -50.0f, 0.0f, 0.3333f };
	aSkyboxVertices[16] = { -50.0f, 50.0f, 50.0f, 0.25f, 0.3333f };//top
	aSkyboxVertices[17] = { 50.0f, 50.0f, 50.0f, 0.50f, 0.3333f };
	aSkyboxVertices[18] = { 50.0f, 50.0f, -50.0f, 0.50f, 0.0f };
	aSkyboxVertices[19] = { -50.0f, 50.0f, -50.0f, 0.25f, 0.0f };
	aSkyboxVertices[20] = { -50.0f, -50.0f, 50.0f, 0.25f, 0.6666f };//bottom
	aSkyboxVertices[21] = { 50.0f, -50.0f, 50.0f, 0.50f, 0.6666f };
	aSkyboxVertices[22] = { 50.0f, -50.0f, -50.0f, 0.50f, 1.0f };
	aSkyboxVertices[23] = { -50.0f, -50.0f, -50.0f, 0.25f, 1.0f };

	aSkyboxIndices = new int[amountOfIndices];
	
	aSkyboxIndices[0] = 0; aSkyboxIndices[1] = 1; aSkyboxIndices[2] = 2;//front
	aSkyboxIndices[3] = 0; aSkyboxIndices[4] = 2; aSkyboxIndices[5] = 3;
	aSkyboxIndices[6] = 4; aSkyboxIndices[8] = 5; aSkyboxIndices[7] = 6;//right
	aSkyboxIndices[9] = 4; aSkyboxIndices[11] = 6; aSkyboxIndices[10] = 7;
	aSkyboxIndices[12] = 8; aSkyboxIndices[14] = 9; aSkyboxIndices[13] = 10;//back
	aSkyboxIndices[15] = 8; aSkyboxIndices[17] = 10; aSkyboxIndices[16] = 11;
	aSkyboxIndices[18] = 12; aSkyboxIndices[20] = 13; aSkyboxIndices[19] = 14;//left
	aSkyboxIndices[21] = 12; aSkyboxIndices[23] = 14; aSkyboxIndices[22] = 15;
	aSkyboxIndices[24] = 16; aSkyboxIndices[26] = 17; aSkyboxIndices[25] = 18;//top
	aSkyboxIndices[27] = 16; aSkyboxIndices[29] = 18; aSkyboxIndices[28] = 19;
	aSkyboxIndices[30] = 20; aSkyboxIndices[31] = 21; aSkyboxIndices[32] = 22;//bottom
	aSkyboxIndices[33] = 20; aSkyboxIndices[34] = 22; aSkyboxIndices[35] = 23;
	

	/*
	aSkyboxIndices[0] = 16; aSkyboxIndices[2] = 17; aSkyboxIndices[1] = 18;//front
	aSkyboxIndices[3] = 16; aSkyboxIndices[5] = 18; aSkyboxIndices[4] = 19;
	aSkyboxIndices[6] = 4; aSkyboxIndices[8] = 5; aSkyboxIndices[7] = 6;//right
	aSkyboxIndices[9] = 4; aSkyboxIndices[11] = 6; aSkyboxIndices[10] = 7;
	aSkyboxIndices[12] = 8; aSkyboxIndices[14] = 9; aSkyboxIndices[13] = 10;//back
	aSkyboxIndices[15] = 8; aSkyboxIndices[17] = 10; aSkyboxIndices[16] = 11;
	aSkyboxIndices[18] = 12; aSkyboxIndices[20] = 13; aSkyboxIndices[19] = 14;//left
	aSkyboxIndices[21] = 12; aSkyboxIndices[23] = 14; aSkyboxIndices[22] = 15;
	aSkyboxIndices[24] = 16; aSkyboxIndices[26] = 17; aSkyboxIndices[25] = 18;//top
	aSkyboxIndices[27] = 16; aSkyboxIndices[29] = 18; aSkyboxIndices[28] = 19;
	aSkyboxIndices[30] = 20; aSkyboxIndices[31] = 21; aSkyboxIndices[32] = 22;//bottom
	aSkyboxIndices[33] = 20; aSkyboxIndices[34] = 22; aSkyboxIndices[35] = 23;

	*/
	


	LPDIRECT3DDEVICE9 g_pd3dDevice = *((pengine::DirectXRenderer*)renderer)->GetDevice();

	

	if (FAILED(D3DXCreateMeshFVF(amountOfIndices, amountOfVertices, 0, D3DCustomVertexFVF, g_pd3dDevice, &d3dMesh)))
	{
		//logger->Log(pengine::Logger::ERR, "Failed to create a D3DXCreateMeshFVF. Generating a cube");
		D3DXCreateBox(g_pd3dDevice, 1.0f, 1.0f, 1.0f, &d3dMesh, NULL);
	}
	else
	{
		void* pVoid;




		d3dMesh->GetVertexBuffer(&v_buffer);
		// lock v_buffer and load the vertices into it
		v_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, aSkyboxVertices, amountOfVertices * sizeof(D3DCustomVertex));
		v_buffer->Unlock();




		d3dMesh->GetIndexBuffer(&i_buffer);
		// lock i_buffer and load the indices into it
		i_buffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, aSkyboxIndices, amountOfIndices * sizeof(int));
		i_buffer->Unlock();



	}


	LPDIRECT3DTEXTURE9* textureNew = new LPDIRECT3DTEXTURE9();
	HRESULT result = D3DXCreateTextureFromFileA(g_pd3dDevice, textureString.c_str(), textureNew);
	texture = new TextureWrapper(textureNew);

}

pengine::Skybox::~Skybox()
{
	/*
	v_buffer->Release();
	i_buffer->Release();
	d3dMesh->Release();
	*/
	delete[] aSkyboxVertices;
	delete[] aSkyboxIndices;
}

D3DCustomVertex* pengine::Skybox::GetSkyboxVertices()
{
	return aSkyboxVertices;
}
int* pengine::Skybox::GetSkyboxIndices()
{
	return aSkyboxIndices;
}
pengine::TextureWrapper* pengine::Skybox::GetTexture()
{
	return texture;
}
void pengine::Skybox::Draw(Renderer* renderer)
{
	RenderMatrix* aMatrix = new RenderMatrix();

	aMatrix->CreateMatrix(0, 0, 0, 0, 0, 0, 1, 1, 1, aMatrix->theMatrix);

	renderer->SetActiveMatrix(aMatrix->theMatrix);


	LPDIRECT3DDEVICE9 g_pd3dDevice = *((pengine::DirectXRenderer*)renderer)->GetDevice();
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);

	//g_pd3dDevice->SetStreamSource(0, v_buffer, 0, sizeof(D3DCustomVertex));
	//g_pd3dDevice->SetFVF(D3DCustomVertexFVF);
	//renderer->SetTexture(texture);
	//g_pd3dDevice->SetIndices(i_buffer);
	//g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,// PrimitiveType
	//	0,// BaseVertexIndex
	//	0,// MinIndex
	//	amountOfVertices,// NumVertices
	//	0,// StartIndex
	//	amountOfIndices/3);// PrimitiveCount

	LPD3DXMESH d3dMesh;
	amountOfVertices = 24;
	amountOfIndices = 36;

	aSkyboxVertices = new D3DCustomVertex[amountOfVertices];
	aSkyboxVertices[0] = { -50.0f, -50.0f, 50.0f, 0.25f, 0.6666f };//front
	aSkyboxVertices[1] = { 50.0f, -50.0f, 50.0f, 0.50f, 0.6666f };
	aSkyboxVertices[2] = { 50.0f, 50.0f, 50.0f, 0.50f, 0.3333f };
	aSkyboxVertices[3] = { -50.0f, 50.0f, 50.0f, 0.25f, 0.3333f };
	aSkyboxVertices[4] = { 50.0f, -50.0f, 50.0f, 0.50f, 0.6666f };//right
	aSkyboxVertices[5] = { 50.0f, -50.0f, -50.0f, 0.75f, 0.6666f };
	aSkyboxVertices[6] = { 50.0f, 50.0f, -50.0f, 0.75f, 0.3333f };
	aSkyboxVertices[7] = { 50.0f, 50.0f, 50.0f, 0.50f, 0.3333f };
	aSkyboxVertices[8] = { 50.0f, -50.0f, -50.0f, 0.75f, 0.6666f };//back
	aSkyboxVertices[9] = { -50.0f, -50.0f, -50.0f, 1.0f, 0.6666f };
	aSkyboxVertices[10] = { -50.0f, 50.0f, -50.0f, 1.0f, 0.3333f };
	aSkyboxVertices[11] = { 50.0f, 50.0f, -50.0f, 0.75f, 0.3333f };
	aSkyboxVertices[12] = { -50.0f, -50.0f, -50.0f, 0.0f, 0.6666f };//left
	aSkyboxVertices[13] = { -50.0f, -50.0f, 50.0f, 0.25f, 0.6666f };
	aSkyboxVertices[14] = { -50.0f, 50.0f, 50.0f, 0.25f, 0.3333f };
	aSkyboxVertices[15] = { -50.0f, 50.0f, -50.0f, 0.0f, 0.3333f };
	aSkyboxVertices[16] = { -50.0f, 50.0f, 50.0f, 0.25f, 0.3333f };//top
	aSkyboxVertices[17] = { 50.0f, 50.0f, 50.0f, 0.50f, 0.3333f };
	aSkyboxVertices[18] = { 50.0f, 50.0f, -50.0f, 0.50f, 0.0f };
	aSkyboxVertices[19] = { -50.0f, 50.0f, -50.0f, 0.25f, 0.0f };
	aSkyboxVertices[20] = { -50.0f, -50.0f, 50.0f, 0.25f, 0.6666f };//bottom
	aSkyboxVertices[21] = { 50.0f, -50.0f, 50.0f, 0.50f, 0.6666f };
	aSkyboxVertices[22] = { 50.0f, -50.0f, -50.0f, 0.50f, 1.0f };
	aSkyboxVertices[23] = { -50.0f, -50.0f, -50.0f, 0.25f, 1.0f };

	aSkyboxIndices = new int[amountOfIndices];

	aSkyboxIndices[0] = 0; aSkyboxIndices[1] = 1; aSkyboxIndices[2] = 2;//front
	aSkyboxIndices[3] = 0; aSkyboxIndices[4] = 2; aSkyboxIndices[5] = 3;
	aSkyboxIndices[6] = 4; aSkyboxIndices[8] = 5; aSkyboxIndices[7] = 6;//right
	aSkyboxIndices[9] = 4; aSkyboxIndices[11] = 6; aSkyboxIndices[10] = 7;
	aSkyboxIndices[12] = 8; aSkyboxIndices[14] = 9; aSkyboxIndices[13] = 10;//back
	aSkyboxIndices[15] = 8; aSkyboxIndices[17] = 10; aSkyboxIndices[16] = 11;
	aSkyboxIndices[18] = 12; aSkyboxIndices[20] = 13; aSkyboxIndices[19] = 14;//left
	aSkyboxIndices[21] = 12; aSkyboxIndices[23] = 14; aSkyboxIndices[22] = 15;
	aSkyboxIndices[24] = 16; aSkyboxIndices[26] = 17; aSkyboxIndices[25] = 18;//top
	aSkyboxIndices[27] = 16; aSkyboxIndices[29] = 18; aSkyboxIndices[28] = 19;
	aSkyboxIndices[30] = 20; aSkyboxIndices[31] = 21; aSkyboxIndices[32] = 22;//bottom
	aSkyboxIndices[33] = 20; aSkyboxIndices[34] = 22; aSkyboxIndices[35] = 23;

	//logger->LogAll(0, "Amount of vertices: ", amountOfVertices, ", faces:", _Mesh->_nFaces, ", indices: ", amountOfIndices);

	if (FAILED(D3DXCreateMeshFVF(amountOfIndices, amountOfVertices, 0, D3DCustomVertexFVF, g_pd3dDevice, &d3dMesh)))
	{
		//logger->Log(pengine::Logger::ERR, "Failed to create a D3DXCreateMeshFVF. Generating a cube");
		D3DXCreateBox(g_pd3dDevice, 1.0f, 1.0f, 1.0f, &d3dMesh, NULL);
	}
	else
	{
		D3DCustomVertex* d3dVertices = new D3DCustomVertex[amountOfVertices];
		unsigned short* indices = new unsigned short[amountOfIndices];

		for (int i = 0; i < amountOfVertices; ++i)//first do all the vertices, then set the indices to the right vertices
		{
			D3DCustomVertex newVertex;
			newVertex.x = aSkyboxVertices[i].x;//x
			newVertex.y = aSkyboxVertices[i].y;//y
			newVertex.z = aSkyboxVertices[i].z;//z
			newVertex.tu = aSkyboxVertices[i].tu;//hopefully we got texture information for each vertex...
			newVertex.tv = aSkyboxVertices[i].tv;//hopefully we got texture information for each vertex...
			d3dVertices[i] = newVertex;
		}

		for (int i = 0; i < amountOfIndices; ++i)//now get all the indices...
		{
			indices[i] = aSkyboxIndices[i];
		}

		void* pVoid;

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
		memcpy(pVoid, indices, amountOfIndices * sizeof(unsigned short));
		i_buffer->Unlock();

		g_pd3dDevice->SetStreamSource(0, v_buffer, 0, sizeof(D3DCustomVertex));
		g_pd3dDevice->SetFVF(D3DCustomVertexFVF);
		g_pd3dDevice->SetIndices(i_buffer);
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,// PrimitiveType
			0,// BaseVertexIndex
			0,// MinIndex
			amountOfVertices,// NumVertices
			0,// StartIndex
			12);// PrimitiveCount
		v_buffer->Release();
		i_buffer->Release();
		d3dMesh->Release();
		delete[] d3dVertices;
		delete[] indices;
	}

	(*((pengine::DirectXRenderer*)renderer)->GetDevice())->SetRenderState(D3DRS_ZENABLE, true);

}