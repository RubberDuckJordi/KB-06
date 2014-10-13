#include "QuadNode.h"

namespace pengine
{
	QuadNode::QuadNode()
	{
		children = NULL;
	}

	QuadNode::~QuadNode()
	{
		if (children != NULL)
		{
			delete[] children;
		}
		if (vertices != NULL)
		{
			delete[] vertices;
		}
	}

	void QuadNode::GetAllChildrenVertices(D3DCustomVertex*& vertices, int& amountOfVertices)
	{
		if (isLeaf)
		{
			vertices = this->vertices;
			amountOfVertices = this->amountOfVertices;
		}
		else
		{
			D3DCustomVertex* node0Vertices;
			int node0AmountOfVertices;
			children[0].GetAllChildrenVertices(node0Vertices, node0AmountOfVertices);
			D3DCustomVertex* node1Vertices;
			int node1AmountOfVertices;
			children[1].GetAllChildrenVertices(node1Vertices, node1AmountOfVertices);
			D3DCustomVertex* node2Vertices;
			int node2AmountOfVertices;
			children[2].GetAllChildrenVertices(node2Vertices, node2AmountOfVertices);
			D3DCustomVertex* node3Vertices;
			int node3AmountOfVertices;
			children[3].GetAllChildrenVertices(node3Vertices, node3AmountOfVertices);

			// Add arrays together
			amountOfVertices = node0AmountOfVertices + node1AmountOfVertices + node2AmountOfVertices + node3AmountOfVertices;
			vertices = new D3DCustomVertex[amountOfVertices];

			int offset = 0;
			for (int i = 0; i < node0AmountOfVertices; ++i)
			{
				vertices[offset + i] = node0Vertices[i];
			}

			offset += node0AmountOfVertices;
			for (int i = 0; i < node1AmountOfVertices; ++i)
			{
				vertices[offset + i] = node1Vertices[i];
			}

			offset += node1AmountOfVertices;
			for (int i = 0; i < node2AmountOfVertices; ++i)
			{
				vertices[offset + i] = node2Vertices[i];
			}

			offset += node2AmountOfVertices;
			for (int i = 0; i < node3AmountOfVertices; ++i)
			{
				vertices[offset + i] = node3Vertices[i];
			}
		}
	}
}
