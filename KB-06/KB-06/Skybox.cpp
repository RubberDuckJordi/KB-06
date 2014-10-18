#include "Skybox.h"
#include "logger.h"
#include "DirectXRenderer.h"

namespace pengine
{

	Skybox::Skybox()
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

		aSkyboxIndices[0] = 0; aSkyboxIndices[2] = 1; aSkyboxIndices[1] = 2;//front
		aSkyboxIndices[3] = 0; aSkyboxIndices[5] = 2; aSkyboxIndices[4] = 3;
		aSkyboxIndices[6] = 4; aSkyboxIndices[8] = 5; aSkyboxIndices[7] = 6;//right
		aSkyboxIndices[9] = 4; aSkyboxIndices[11] = 6; aSkyboxIndices[10] = 7;
		aSkyboxIndices[12] = 8; aSkyboxIndices[14] = 9; aSkyboxIndices[13] = 10;//back
		aSkyboxIndices[15] = 8; aSkyboxIndices[17] = 10; aSkyboxIndices[16] = 11;
		aSkyboxIndices[18] = 12; aSkyboxIndices[20] = 13; aSkyboxIndices[19] = 14;//left
		aSkyboxIndices[21] = 12; aSkyboxIndices[23] = 14; aSkyboxIndices[22] = 15;
		aSkyboxIndices[24] = 16; aSkyboxIndices[26] = 17; aSkyboxIndices[25] = 18;//top
		aSkyboxIndices[27] = 16; aSkyboxIndices[29] = 18; aSkyboxIndices[28] = 19;
		aSkyboxIndices[30] = 20; aSkyboxIndices[32] = 21; aSkyboxIndices[31] = 22;//bottom
		aSkyboxIndices[33] = 20; aSkyboxIndices[35] = 22; aSkyboxIndices[34] = 23;
	}

	Skybox::~Skybox()
	{
		//d3dMesh->Release();

		delete[] aSkyboxVertices;
		delete[] aSkyboxIndices;
	}

	D3DCustomVertex* Skybox::GetSkyboxVertices()
	{
		return aSkyboxVertices;
	}

	int* Skybox::GetSkyboxIndices()
	{
		return aSkyboxIndices;
	}

	Material* Skybox::GetMaterial()
	{
		return material;
	}

	void Skybox::SetMaterial(Material* p_material)
	{
		material = p_material;
	}

	void Skybox::Draw(Renderer* renderer, Vector3* position)
	{
		// initialise
		if (i_buffer == NULL)
		{
			i_buffer = renderer->CreateIndexBuffer(aSkyboxIndices, amountOfIndices);
			v_buffer = renderer->CreateVertexBuffer(aSkyboxVertices, amountOfIndices);
		}

		Matrix* aMatrix = new Matrix();

		aMatrix->CreateMatrix(position->x, position->y, position->z, 0, 0, 0, 1, 1, 1, aMatrix);

		renderer->SetActiveMatrix(aMatrix);
		renderer->SetMaterial(material);

		renderer->SetZBuffer(false);
		renderer->DrawIndexedVertexBuffer(v_buffer, i_buffer, amountOfVertices, 12);
		renderer->SetZBuffer(true);
	}
}