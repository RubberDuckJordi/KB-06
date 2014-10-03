#include "Ground.h"
#include "DirectXRenderer.h"

namespace pengine
{
	Ground::Ground()
	{
		logger = LoggerPool::GetInstance().GetLogger();
	}

	Ground::~Ground()
	{
		LoggerPool::GetInstance().ReturnLogger(logger);
	}

	long Ground::GetHeight()
	{
		return height;
	}

	long Ground::GetWidth()
	{
		return width;
	}

	void Ground::SetHeight(long p_height)
	{
		height = p_height;
	}

	void Ground::SetWidth(long p_width)
	{
		width = p_width;
	}

	void Ground::SetCellSize(float p_cellSize)
	{
		cellSize = p_cellSize;
	}

	float Ground::GetCellSize()
	{
		return cellSize;
	}

	void Ground::SetAmountOfIndices(int p_amountOfIndices)
	{
		amountOfIndices = p_amountOfIndices;
	}

	int Ground::GetAmountOfIndices()
	{
		return amountOfIndices;
	}

	D3DCustomVertex* Ground::GetVertices()
	{
		return vertices;
	}

	void Ground::SetVertices(D3DCustomVertex* vertex)
	{
		vertices = vertex;
	}

	void Ground::Render(Renderer* renderer)
	{
		LPDIRECT3DDEVICE9 m_d3dDevice = *((DirectXRenderer*)renderer)->GetDevice();

		if (vertexBuffer == NULL)
		{
			if (FAILED(m_d3dDevice->CreateVertexBuffer(amountOfIndices * sizeof(D3DCustomVertex),
				0, D3DCustomVertexFVF, D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
			{
				logger->Log(Logger::ERR, "Ground::Render() vertexbuffer create failed");
			}

			void* verticesBuffer;
			int size = sizeof(D3DCustomVertex)*amountOfIndices;
			if (FAILED((vertexBuffer)->Lock(0, size, (void**)&verticesBuffer, 0)))
			{
				logger->Log(Logger::ERR, "Ground::Render() vertexbuffer lock failed");
			}

			memcpy(verticesBuffer, this->vertices, size);
			vertexBuffer->Unlock();
		}

		Material mat;
		mat.ambient = { 0.0f, 0.0f, 1.0f };
		mat.diffuse = { 0.0f, 0.0f, 1.0f, 1.0f };
		mat.emissive = { 0.0f, 0.0f, 1.0f };
		mat.power = 0;
		mat.specular = { 0.0f, 0.0f, 1.0f };

		RenderMatrix* aMatrix = new RenderMatrix();

		aMatrix->CreateMatrix(0, 0, 0, 0, 0, 0, 1, 1, 1, aMatrix->theMatrix);

		renderer->SetActiveMatrix(aMatrix->theMatrix);
		renderer->SetMaterial(&mat);

		m_d3dDevice->SetTexture(0, NULL);
		m_d3dDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(D3DCustomVertex));
		m_d3dDevice->SetFVF(D3DCustomVertexFVF);
		m_d3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, amountOfIndices / 3 );	

	}
}