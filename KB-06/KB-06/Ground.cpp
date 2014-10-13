#include "Ground.h"
#include "DirectXRenderer.h"
#include <vector>
#include "PengineDefinitions.h"

namespace pengine
{
	Ground::Ground()
	{
		logger = LoggerPool::GetInstance().GetLogger();

		location = new RenderMatrix();
		location->CreateMatrix(0, 0, 0, 0, 0, 0, 1, 1, 1, location->theMatrix);
	}

	Ground::~Ground()
	{
		LoggerPool::GetInstance().ReturnLogger(logger);
		if (quadTreeRootNode != NULL)
		{
			delete quadTreeRootNode;
		}
	}

	void Ground::InitQuadTree(unsigned short depth)
	{
		quadTreeRootNode = CreateQuadTree(depth);
	}

	long Ground::GetHeight()
	{
		return height;
	}

	long Ground::GetWidth()
	{
		return width;
	}

	void Ground::SetHeight(long p_height)
	{
		height = p_height;
	}

	void Ground::SetWidth(long p_width)
	{
		width = p_width;
	}

	void Ground::SetCellSize(float p_cellSize)
	{
		cellSize = p_cellSize;
	}

	float Ground::GetCellSize()
	{
		return cellSize;
	}

	void Ground::SetAmountOfVertices(int p_amountOfVertices)
	{
		amountOfVertices = p_amountOfVertices;
	}

	int Ground::GetAmountOfVertices()
	{
		return amountOfVertices;
	}

	D3DCustomVertex* Ground::GetVertices()
	{
		return vertices;
	}

	void Ground::SetVertices(D3DCustomVertex* vertex)
	{
		vertices = vertex;
	}

	Material* Ground::GetMaterial()
	{
		return material;
	}

	void Ground::SetMaterial(Material* p_material)
	{
		material = p_material;
	}

	void Ground::Render(Renderer* renderer)
	{
		D3DCustomVertex* verticesX;
		int amountOfVerticesX;
		quadTreeRootNode->GetAllChildrenVertices(verticesX, amountOfVerticesX);

		if (vertexBuffer != NULL)
		{
			delete vertexBuffer;
		}

		vertexBuffer = renderer->CreateVertexBuffer(verticesX, amountOfVerticesX, D3DCustomVertexFVF);

		renderer->SetActiveMatrix(location->theMatrix);
		renderer->SetMaterial(material);

		renderer->DrawVertexBuffer(vertexBuffer, amountOfVerticesX);

		delete[] verticesX;
	}

	QuadNode* Ground::CreateQuadTree(unsigned short depth)
	{
		if (depth != 0)
		{
			if (width % depth != 0)
			{
				logger->Log(Logger::ERR, "Width is not dividable by depth");
				return NULL;
			}

			if (height % depth != 0)
			{
				logger->Log(Logger::ERR, "Height is not dividable by depth");
				return NULL;
			}
		}

		// Find dimensions of the ground
		int dimensionWidth = 0;
		int dimensionDepth = 0;

		for (int i = 0; i < amountOfVertices; ++i)
		{
			D3DCustomVertex* vertex = &vertices[i];
			if (vertex->x > dimensionWidth)
			{
				dimensionWidth = vertex->x;
			}
			if (vertex->z > dimensionDepth)
			{
				dimensionDepth = vertex->z;
			}
		}

		QuadNode* rootNode = new QuadNode();
		rootNode->minX = 0;
		rootNode->minZ = 0;
		rootNode->maxX = dimensionWidth;
		rootNode->maxZ = dimensionDepth;
		rootNode->isLeaf = false;

		CreateQuadTreeChildren(rootNode, depth);

		return rootNode;
	}

	void Ground::CreateQuadTreeChildren(QuadNode* parent, unsigned short remainingDepth)
	{
		if (remainingDepth > 0)
		{
			// This is a branch, create children and call this function recursively
			parent->isLeaf = false;

			// 0 3
			// 1 2

			QuadNode* node0 = new QuadNode();
			QuadNode* node1 = new QuadNode();
			QuadNode* node2 = new QuadNode();
			QuadNode* node3 = new QuadNode();

			node0->parent = parent;
			node1->parent = parent;
			node2->parent = parent;
			node3->parent = parent;

			node0->minX = (parent->maxX - parent->minX) / 2 + parent->minX;
			node0->maxX = parent->maxX;
			node0->minZ = parent->minZ;
			node0->maxZ = parent->minZ + (parent->maxZ - parent->minZ) / 2;

			node1->minX = parent->minX;
			node1->maxX = (parent->maxX - parent->minX) / 2 + parent->minX;
			node1->minZ = parent->minZ;
			node1->maxZ = parent->minZ + (parent->maxZ - parent->minZ) / 2;

			node2->minX = parent->minX;
			node2->maxX = (parent->maxX - parent->minX) / 2 + parent->minX;
			node2->minZ = parent->minZ + (parent->maxZ - parent->minZ) / 2;
			node2->maxZ = parent->maxZ;

			node3->minX = (parent->maxX - parent->minX) / 2 + parent->minX;
			node3->maxX = parent->maxX;
			node3->minZ = parent->minZ + (parent->maxZ - parent->minZ) / 2;
			node3->maxZ = parent->maxZ;

			CreateQuadTreeChildren(node0, remainingDepth - 1);
			CreateQuadTreeChildren(node1, remainingDepth - 1);
			CreateQuadTreeChildren(node2, remainingDepth - 1);
			CreateQuadTreeChildren(node3, remainingDepth - 1);

			parent->children = new QuadNode[4];
			parent->children[0] = *node0;
			parent->children[1] = *node1;
			parent->children[2] = *node2;
			parent->children[3] = *node3;
		}
		else
		{
			// Add leaf data
			parent->isLeaf = true;
			std::vector<D3DCustomVertex*> leafVertices;

			// Add all triangles within the bounds, borders included
			for (int i = 0; i < amountOfVertices - 2; i += 3)
			{
				D3DCustomVertex* vertex0 = &vertices[i];
				D3DCustomVertex* vertex1 = &vertices[i + 1];
				D3DCustomVertex* vertex2 = &vertices[i + 2];

				// if one of the points is within bounds
				if ((vertex0->x >= parent->minX && vertex0->x <= parent->maxX
					&& vertex0->z >= parent->minZ && vertex0->z <= parent->maxZ)
					||
					(vertex1->x >= parent->minX && vertex1->x <= parent->maxX
					&& vertex1->z >= parent->minZ && vertex1->z <= parent->maxZ)
					||
					(vertex2->x >= parent->minX && vertex2->x <= parent->maxX
					&& vertex2->z >= parent->minZ && vertex2->z <= parent->maxZ))
				{
					leafVertices.push_back(vertex0);
					leafVertices.push_back(vertex1);
					leafVertices.push_back(vertex2);
				}
			}

			int amountOfVertices = leafVertices.size();
			parent->vertices = new D3DCustomVertex[amountOfVertices];
			for (int i = 0; i < amountOfVertices; ++i)
			{
				parent->vertices[i] = *leafVertices[i];

			}
			parent->amountOfVertices = amountOfVertices;
		}
	}
}