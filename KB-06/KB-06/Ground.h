#ifndef _GROUND_H_
#define _GROUND_H_

#include "CustomD3DVertex.h"
#include "Renderer.h"
#include "LoggerPool.h"
#include "QuadNode.h"

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

		Material* GetMaterial();
		void SetMaterial(Material* material);
		// Creates a quad tree based on the terrain
		QuadNode* CreateQuadTree(unsigned short depth);

		void Render(Renderer* renderer);

	private:
		void CreateQuadTreeChildren(QuadNode* parent, unsigned short remainingDepth);

		Logger* logger;
		int amountOfIndices;
		D3DCustomVertex* vertices;
		VertexBufferWrapper* vertexBuffer;
		Material* material;
		RenderMatrix* location;

		long height;
		long width;

		float cellSize;
	};
}

#endif