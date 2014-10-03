#ifndef _GROUND_H_
#define _GROUND_H_

#include "Vertex.h"
#include "Renderer.h"

namespace pengine
{
	class Ground
	{

	public:
		long GetHeight();
		long GetWidth();
		void SetHeight(long);
		void SetCellSize(float);
		float GetCellSize();
		void SetWidth(long);
		
		void SetAmountOfIndices(int);
		int GetAmountOfIndices();
		void SetVertices(Vertex* vertex);
		Vertex* GetVertices();

		void Render(Renderer& renderer);

	private:
		int amountOfIndices;
		Vertex* vertices;

		long height;
		long width;

		float cellSize;
	};
}

#endif