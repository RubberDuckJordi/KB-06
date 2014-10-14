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
		
		QuadNode* GetParent();
		void SetParent(QuadNode* parent);

		bool IsLeaf();
		void SetIsLeaf(bool isLeaf);
		float GetMinX();
		float GetMaxX();
		float GetMinZ();
		float GetMaxZ();
		void SetMinX(float minX);
		void SetMaxX(float maxX);
		void SetMinZ(float minZ);
		void SetMaxZ(float maxX);

		QuadNode* GetChildren();
		void SetChildren(QuadNode* children);

		D3DCustomVertex* GetVertices();
		void SetVertices(D3DCustomVertex* vertices);

		unsigned int GetAmountOfVertices();
		void SetAmountOfVertices(unsigned int amountOfVertices);

		// Returns terrain vertices of all children
		void GetAllChildrenVertices(D3DCustomVertex*& vertices, int& amountOfVertices);

	private:
		QuadNode* parent;
		bool isLeaf;
		// Only uses x and z. Y is omitted because we are using a 2d tree.
		float minX;
		float maxX;
		float minZ;
		float maxZ;

		// Only for branches and root node
		QuadNode* children;

		// Only for leaves
		// Terrain vertices
		D3DCustomVertex* vertices;
		unsigned int amountOfVertices;
	};
}


#endif