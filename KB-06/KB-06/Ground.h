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
		void InitQuadTree(unsigned short depth);
		long GetHeight();
		long GetWidth();
		void SetHeight(long);
		void SetCellSize(float);
		float GetCellSize();
		void SetWidth(long);
		
		void SetAmountOfVertices(int);
		int GetAmountOfVertices();
		void SetVertices(D3DCustomVertex* vertex);
		D3DCustomVertex* GetVertices();

		Material* GetMaterial();
		void SetMaterial(Material* material);
		// Creates a quad tree based on the terrain
		QuadNode* CreateQuadTree(unsigned short depth);

		void Render(Renderer* renderer);

	private:
		void CreateQuadTreeChildren(QuadNode* parent, unsigned short remainingDepth);

		QuadNode* quadTreeRootNode;
		Logger* logger;
		int amountOfVertices;
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