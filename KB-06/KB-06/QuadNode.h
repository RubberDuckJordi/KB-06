#ifndef _PENGINE_QUADNODE_H_
#define _PENGINE_QUADNODE_H_

#include "Vertex.h"
#include "CustomD3DVertex.h"

namespace pengine
{
	class QuadNode
	{

	public:
		QuadNode();
		~QuadNode();
		QuadNode* parent;
		bool isLeaf;
		// Only uses x and z. Y is omitted because we are using a 2d tree.
		int minX;
		int maxX;
		int minZ;
		int maxZ;

		// Only for branches and root node
		QuadNode* children;

		// Only for leaves
		// Terrain vertices
		D3DCustomVertex* vertices;
		unsigned int amountOfVertices;

		// Returns terrain vertices of all children
		void GetAllChildrenVertices(D3DCustomVertex*& vertices, int& amountOfVertices);
	};
}


#endif