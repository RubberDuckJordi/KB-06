#include "QuadNode.h"

namespace pengine
{
	QuadNode::QuadNode()
	{
		logger = LoggerPool::GetInstance().GetLogger();

		minX = 0.0f;
		maxX = 0.0f;
		minZ = 0.0f;
		maxZ = 0.0f;
		levelOfDetail = 1;
	}

	QuadNode::~QuadNode()
	{
		if (vertices != NULL)
		{
			delete[] vertices;
		}
	}

	void QuadNode::GetAllChildrenVertices(D3DCustomVertex*& vertices, int& amountOfVertices)
	{
		if (isLeaf)
		{
			int newWidth = width / levelOfDetail;
			int newDepth = depth / levelOfDetail;

			if (levelOfDetail == 1)
			{
				// No changes
				vertices = this->vertices;
				amountOfVertices = this->amountOfVertices;

				// Restitching
				if (neighbors[1] != NULL)
				{
					unsigned short neighborLevelOfDetail = neighbors[1]->GetLevelOfDetail();
					int skippedTiles = neighborLevelOfDetail - 1;

					if (neighborLevelOfDetail > levelOfDetail)
					{
						int z = depth;
						for (int x = 0; x < newWidth; ++x)
						{
							int offset = x * newWidth * 6;
							vertices[offset + z * 6 + 1] = this->vertices[(x + x * skippedTiles) * width * 6 + (z * neighborLevelOfDetail + skippedTiles) * 6 + 1];
							vertices[offset + z * 6 + 3] = this->vertices[(x * neighborLevelOfDetail + skippedTiles) * width * 6 + (z * neighborLevelOfDetail + skippedTiles) * 6 + 3];
							vertices[offset + z * 6 + 4] = this->vertices[(x + x * skippedTiles) * width * 6 + (z * neighborLevelOfDetail + skippedTiles) * 6 + 4];
						}
					}
				}
			}
			else
			{
				amountOfVertices = this->amountOfVertices / (levelOfDetail * levelOfDetail);
				
				int skippedTiles = levelOfDetail - 1;

				vertices = new D3DCustomVertex[amountOfVertices];
				// Divide the vertices by level of detail
				for (int x = 0; x < newWidth; ++x)
				{
					int offset = x * newWidth * 6;

					for (int z = 0; z < newDepth; ++z)
					{
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
			children[0]->GetAllChildrenVertices(node0Vertices, node0AmountOfVertices);
			D3DCustomVertex* node1Vertices;
			int node1AmountOfVertices;
			children[1]->GetAllChildrenVertices(node1Vertices, node1AmountOfVertices);
			D3DCustomVertex* node2Vertices;
			int node2AmountOfVertices;
			children[2]->GetAllChildrenVertices(node2Vertices, node2AmountOfVertices);
			D3DCustomVertex* node3Vertices;
			int node3AmountOfVertices;
			children[3]->GetAllChildrenVertices(node3Vertices, node3AmountOfVertices);

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

	std::array<QuadNode*, 4>* QuadNode::GetChildren()
	{
		return &children;
	}

	void QuadNode::SetChildren(std::array<QuadNode*, 4>* children)
	{
		this->children = *children;
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
			children[0]->SetLevelOfDetail(levelOfDetail);
			children[1]->SetLevelOfDetail(levelOfDetail);
			children[2]->SetLevelOfDetail(levelOfDetail);
			children[3]->SetLevelOfDetail(levelOfDetail);
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

	char QuadNode::GetLocation()
	{
		return location;
	}

	void QuadNode::SetLocation(char location)
	{
		this->location = location;
	}

	std::map<char, QuadNode*>* QuadNode::GetNeighbors()
	{
		return &neighbors;
	}

	void QuadNode::CalculateNeighbors(unsigned short recursionLevel)
	{
		if (recursionLevel == 0)
		{
			std::map<char, QuadNode*>* neighbors = this->GetNeighbors();

			switch (location)
			{
			case 0:
				// top left
				(*neighbors)[1] = (*this->GetParent()->GetChildren())[3];
				(*neighbors)[2] = (*this->GetParent()->GetChildren())[1];
				if (this->GetParent()->GetNeighbors()->size() > 0)
				{
					SetNeighbor(neighbors, 0, 1);
					SetNeighbor(neighbors, 3, 3);
				}
				break;
			case 1:
				// bottom left
				(*neighbors)[0] = (*this->GetParent()->GetChildren())[0];
				(*neighbors)[1] = (*this->GetParent()->GetChildren())[2];
				if (this->GetParent()->GetNeighbors()->size() > 0)
				{
					SetNeighbor(neighbors, 2, 0);
					SetNeighbor(neighbors, 3, 2);
				}
				break;
			case 2:
				// bottom right
				(*neighbors)[3] = (*this->GetParent()->GetChildren())[1];
				(*neighbors)[0] = (*this->GetParent()->GetChildren())[3];
				if (this->GetParent()->GetNeighbors()->size() > 0)
				{
					SetNeighbor(neighbors, 2, 3);
					SetNeighbor(neighbors, 1, 1);
				}
				break;
			case 3:
				// top right
				(*neighbors)[2] = (*this->GetParent()->GetChildren())[2];
				(*neighbors)[3] = (*this->GetParent()->GetChildren())[0];
				if (this->GetParent()->GetNeighbors()->size() > 0)
				{
					SetNeighbor(neighbors, 1, 0);
					SetNeighbor(neighbors, 0, 2);
				}
				break;
			}
		}
		else
		{
			if (!this->IsLeaf())
			{
				(*this->GetChildren())[0]->CalculateNeighbors(recursionLevel - 1);
				(*this->GetChildren())[1]->CalculateNeighbors(recursionLevel - 1);
				(*this->GetChildren())[2]->CalculateNeighbors(recursionLevel - 1);
				(*this->GetChildren())[3]->CalculateNeighbors(recursionLevel - 1);
			}
		}
	}

	void QuadNode::SetNeighbor(std::map<char, QuadNode*>* neighbors, char direction, char nephewLocation)
	{
		auto i = this->GetParent()->GetNeighbors()->find(direction);
		if (i != this->GetParent()->GetNeighbors()->end())
		{
			(*neighbors)[direction] = (*i->second->GetChildren())[nephewLocation];
		}
	}

}