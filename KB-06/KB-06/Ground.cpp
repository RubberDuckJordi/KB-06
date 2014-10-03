#include "Ground.h"

namespace pengine
{
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

	Vertex* Ground::GetVertices()
	{
		return vertices;
	}

	void Ground::SetVertices(Vertex* vertex)
	{
		vertices = vertex;
	}

	void Ground::Render(Renderer& renderer)
	{

	}
}