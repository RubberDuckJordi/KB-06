#ifndef _GROUND_H_
#define _GROUND_H_

#include "CustomD3DVertex.h"
#include "Renderer.h"
#include "LoggerPool.h"

namespace pengine
{
	class Ground
	{

	public:
		Ground();
		~Ground();
		long GetHeight();
		long GetWidth();
		void SetHeight(long);
		void SetCellSize(float);
		float GetCellSize();
		void SetWidth(long);
		
		void SetAmountOfIndices(int);
		int GetAmountOfIndices();
		void SetVertices(D3DCustomVertex* vertex);
		D3DCustomVertex* GetVertices();

		void Render(Renderer* renderer);

	private:
		Logger* logger;
		int amountOfIndices;
		D3DCustomVertex* vertices;
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

		long height;
		long width;

		float cellSize;
	};
}

#endif