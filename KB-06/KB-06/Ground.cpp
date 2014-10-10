#include "Ground.h"
#include "DirectXRenderer.h"

namespace pengine
{
	Ground::Ground()
	{
		logger = LoggerPool::GetInstance().GetLogger();

		location = new RenderMatrix();
		location->CreateMatrix(0, 0, 0, 0, 0, 0, 1, 1, 1, location->theMatrix);
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

	Material* Ground::GetMaterial()
	{
		return material;
	}

	void Ground::SetMaterial(Material* p_material)
	{
		material = p_material;
	}

	void Ground::Render(Renderer* renderer)
	{
		if (vertexBuffer != NULL)
		{
			delete vertexBuffer;
		}
		
		vertexBuffer = renderer->CreateVertexBuffer(vertices, amountOfIndices, D3DCustomVertexFVF);

		renderer->SetActiveMatrix(location->theMatrix);
		renderer->SetMaterial(material);
		
		renderer->DrawVertexBuffer(vertexBuffer, amountOfIndices);
	}
}