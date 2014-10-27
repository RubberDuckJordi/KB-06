#ifndef _GROUND_H_
#define _GROUND_H_

#include "Vertex.h"
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
		void SetVertices(Vertex* vertex);
		Vertex* GetVertices();

		Material* GetMaterial();
		void SetMaterial(Material* material);
		// Creates a quad tree based on the terrain
		QuadNode* CreateQuadTree(unsigned short depth);
		QuadNode* GetQuadTree();
		unsigned short GetQuadTreeDepth();

		void CacheToRenderer(Renderer* renderer);
		void Render(Renderer* renderer);

	private:
		void CreateQuadTreeChildren(QuadNode* parent, unsigned short remainingDepth);
		
		QuadNode* quadTreeRootNode;
		unsigned short quadTreeDepth;

		Logger* logger;
		int amountOfVertices;
		Vertex* vertices;
		VertexBufferWrapper* vertexBuffer;
		Material* material;
		Matrix* location;

		long height;
		long width;

		float cellSize;
	};
}

#endif