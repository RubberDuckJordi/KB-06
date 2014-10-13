#ifndef _PENGINE_QUADNODE_H_
#define _PENGINE_QUADNODE_H_

#include "Vertex.h"
#include "CustomD3DVertex.h"

namespace pengine
{
	class QuadNode
	{

	public:
		QuadNode* parent;
		bool isLeaf;
		// Only uses x and z. Y is omitted because we are using a 2d tree.
		int minX;
		int maxX;
		int minZ;
		int maxZ;

		// Only for branches and root node
		QuadNode* children[4];

		// Only for leaves
		// Terrain vertices
		D3DCustomVertex* vertices;
		unsigned int amountOfVertices;

		void GetAllChildrenVertices(D3DCustomVertex*& vertices, int& amountOfIndices);
	};
}

#endif