#include "QuadNode.h"

namespace pengine
{
	QuadNode::QuadNode()
	{
		logger = LoggerPool::GetInstance().GetLogger();
		children = NULL;
		minX = 0.0f;
		maxX = 0.0f;
		minZ = 0.0f;
		maxZ = 0.0f;
		levelOfDetail = 1;
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
			if (levelOfDetail == 1)
			{
				// No changes
				vertices = this->vertices;
				amountOfVertices = this->amountOfVertices;
			}
			else
			{
				amountOfVertices = this->amountOfVertices / (levelOfDetail * levelOfDetail);

				int newWidth = width / levelOfDetail;
				int newDepth = depth / levelOfDetail;

				vertices = new D3DCustomVertex[amountOfVertices];
				// Divide the vertices by level of detail
				for (int x = 0; x < newWidth; ++x)
				{
					for (int z = 0; z < newDepth; ++z)
					{
						int offset = x * newWidth * 6;
						int skippedTiles = levelOfDetail - 1;

						vertices[offset + z * 6] = this->vertices[(x * levelOfDetail + skippedTiles) * width * 6 + (z + z * skippedTiles) * 6];
						vertices[offset + z * 6 + 1] = this->vertices[(x + x * skippedTiles) * width * 6 + (z * levelOfDetail + skippedTiles) * 6 + 1];
						vertices[offset + z * 6 + 2] = this->vertices[(x + x * skippedTiles) * width * 6 + (z + z * skippedTiles) * 6 + 2];
						vertices[offset + z * 6 + 3] = this->vertices[(x * levelOfDetail + skippedTiles) * width * 6 + (z * levelOfDetail + skippedTiles) * 6 + 3];
						vertices[offset + z * 6 + 4] = this->vertices[(x + x * skippedTiles) * width * 6 + (z * levelOfDetail + skippedTiles) * 6 + 4];
						vertices[offset + z * 6 + 5] = this->vertices[(x * levelOfDetail + skippedTiles) * width * 6 + (z + z * skippedTiles) * 6 + 5];
					}
				}
			}
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

	QuadNode* QuadNode::GetParent()
	{
		return parent;
	}

	void QuadNode::SetParent(QuadNode* parent)
	{
		this->parent = parent;
	}

	bool QuadNode::IsLeaf()
	{
		return isLeaf;
	}

	void QuadNode::SetIsLeaf(bool isLeaf)
	{
		this->isLeaf = isLeaf;
	}

	float QuadNode::GetMinX()
	{
		return minX;
	}

	float QuadNode::GetMaxX()
	{
		return maxX;
	}

	float QuadNode::GetMinZ()
	{
		return minZ;
	}

	float QuadNode::GetMaxZ()
	{
		return maxZ;
	}

	void QuadNode::SetMinX(float p_minX)
	{
		this->minX = p_minX;
	}

	void QuadNode::SetMaxX(float p_maxX)
	{
		this->maxX = p_maxX;
	}

	void QuadNode::SetMinZ(float p_minZ)
	{
		this->minZ = p_minZ;
	}

	void QuadNode::SetMaxZ(float p_maxZ)
	{
		this->maxZ = p_maxZ;
	}

	QuadNode* QuadNode::GetChildren()
	{
		return children;
	}

	void QuadNode::SetChildren(QuadNode* children)
	{
		this->children = children;
	}

	D3DCustomVertex* QuadNode::GetVertices()
	{
		return vertices;
	}

	void QuadNode::SetVertices(D3DCustomVertex* vertices)
	{
		this->vertices = vertices;
	}

	unsigned int QuadNode::GetAmountOfVertices()
	{
		return amountOfVertices;
	}

	void QuadNode::SetAmountOfVertices(unsigned int amountOfVertices)
	{
		this->amountOfVertices = amountOfVertices;
	}

	void QuadNode::SetLevelOfDetail(unsigned short levelOfDetail)
	{
		if (levelOfDetail == 0)
		{

			levelOfDetail = 1;
		}
		this->levelOfDetail = levelOfDetail;

		if (!isLeaf)
		{
			children[0].SetLevelOfDetail(levelOfDetail);
			children[1].SetLevelOfDetail(levelOfDetail);
			children[2].SetLevelOfDetail(levelOfDetail);
			children[3].SetLevelOfDetail(levelOfDetail);
		}
	}

	unsigned short QuadNode::GetLevelOfDetail()
	{
		return levelOfDetail;
	}

	int QuadNode::GetWidth()
	{
		return width;
	}

	int QuadNode::GetDepth()
	{
		return depth;
	}

	void QuadNode::SetWidth(int width)
	{
		this->width = width;
	}

	void QuadNode::SetDepth(int depth)
	{
		this->depth = depth;
	}
}