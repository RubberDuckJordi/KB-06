#ifndef _GROUND_H_
#define _GROUND_H_

#include "Vertex.h"
#include "Renderer.h"
#include "LoggerPool.h"
#include "QuadNode.h"

/*
Terrain
*/

namespace pengine
{
	class Ground
	{

	public:
		Ground();
		~Ground();
		// Initialises the quad tree with specified depth
		// depth represents the amount of levels beneath the root node
		// depth = 1 means 4 child nodes under the root node
		// depth = 2 means 4 * 4 child nodes under the root node
		void InitQuadTree(unsigned short depth);
		// returns the height of the map, this represents the amount of height points in the map, not the amount of squares
		long GetHeight();
		// returns the width of the map, this represents the amount of height points in the map, not the amount of squares
		long GetWidth();

		// the 5 functions below are invoked from the heightmaploader, they should not be invoked later.
		void SetHeight(long);
		void SetCellSize(float);
		void SetWidth(long);
		void SetAmountOfVertices(int);
		void SetVertices(Vertex* vertex);

		// scaling
		float GetCellSize();
	
		int GetAmountOfVertices();
		Vertex* GetVertices();

		Material* GetMaterial();
		void SetMaterial(Material* material);
		// Creates a quad tree based on the terrain
		QuadNode* CreateQuadTree(unsigned short depth);
		// returns the root node of the quad tree
		QuadNode* GetQuadTree();
		// returns the depth of the quad tree
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