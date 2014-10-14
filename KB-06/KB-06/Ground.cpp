#include "Ground.h"
#include "DirectXRenderer.h"
#include <vector>
#include "PengineDefinitions.h"
#include <math.h>

namespace pengine
{
	Ground::Ground()
	{
		logger = LoggerPool::GetInstance().GetLogger();

		location = new Matrix();
		location->Identity();
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
		renderer->SetFillMode(PENGINE_FILL_WIREFRAME);
		D3DCustomVertex* verticesX;
		int amountOfVerticesX;
		quadTreeRootNode->GetAllChildrenVertices(verticesX, amountOfVerticesX);

		if (vertexBuffer != NULL)
		{
			delete vertexBuffer;
		}

		vertexBuffer = renderer->CreateVertexBuffer(verticesX, amountOfVerticesX, D3DCustomVertexFVF);

		renderer->SetActiveMatrix(location);
		renderer->SetMaterial(material);

		renderer->DrawVertexBuffer(vertexBuffer, amountOfVerticesX);

		//delete[] verticesX;

		renderer->SetFillMode(PENGINE_FILL_SOLID);
	}

	QuadNode* Ground::CreateQuadTree(unsigned short depth)
	{
		if (depth != 0)
		{
			int powDepth = pow(depth, depth);
			if ((width - 1) % powDepth != 0)
			{
				logger->Log(Logger::ERR, "Width is not dividable by depth^depth");
				return NULL;
			}

			if ((height - 1) % powDepth != 0)
			{
				logger->Log(Logger::ERR, "Height is not dividable by depth^depth");
				return NULL;
			}
		}

		// Find dimensions of the ground
		float dimensionWidth = 0.0f;
		float dimensionDepth = 0.0f;

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
		rootNode->SetMinX(0.0f);
		rootNode->SetMinZ(0.0f);
		rootNode->SetMaxX(dimensionWidth);
		rootNode->SetMaxZ(dimensionDepth);
		rootNode->SetIsLeaf(false);

		rootNode->SetWidth(this->width - 1);
		rootNode->SetDepth(this->height - 1);

		CreateQuadTreeChildren(rootNode, depth);

		rootNode->SetLevelOfDetail(2);

		return rootNode;
	}

	void Ground::CreateQuadTreeChildren(QuadNode* parent, unsigned short remainingDepth)
	{
		if (remainingDepth > 0)
		{
			// This is a branch, create children and call this function 
			parent->SetIsLeaf(false);

			// 0 3
			// 1 2

			QuadNode* node0 = new QuadNode();
			QuadNode* node1 = new QuadNode();
			QuadNode* node2 = new QuadNode();
			QuadNode* node3 = new QuadNode();

			node0->SetParent(parent);
			node1->SetParent(parent);
			node2->SetParent(parent);
			node3->SetParent(parent);

			node0->SetMinX((parent->GetMaxX()- parent->GetMinX()) / 2 + parent->GetMinX());
			node0->SetMaxX(parent->GetMaxX());
			node0->SetMinZ(parent->GetMinZ());
			node0->SetMaxZ(parent->GetMinZ() + (parent->GetMaxZ() - parent->GetMinZ()) / 2);

			node1->SetMinX(parent->GetMinX());
			node1->SetMaxX((parent->GetMaxX() - parent->GetMinX()) / 2 + parent->GetMinX());
			node1->SetMinZ(parent->GetMinZ());
			node1->SetMaxZ(parent->GetMinZ() + (parent->GetMaxZ() - parent->GetMinZ()) / 2);

			node2->SetMinX(parent->GetMinX());
			node2->SetMaxX((parent->GetMaxX() - parent->GetMinX()) / 2 + parent->GetMinX());
			node2->SetMinZ(parent->GetMinZ() + (parent->GetMaxZ() - parent->GetMinZ()) / 2);
			node2->SetMaxZ(parent->GetMaxZ());

			node3->SetMinX((parent->GetMaxX() - parent->GetMinX()) / 2 + parent->GetMinX());
			node3->SetMaxX(parent->GetMaxX());
			node3->SetMinZ(parent->GetMinZ() + (parent->GetMaxZ() - parent->GetMinZ()) / 2);
			node3->SetMaxZ(parent->GetMaxZ());

			node0->SetWidth(parent->GetWidth() / 2);
			node0->SetDepth(parent->GetDepth() / 2);
			node1->SetWidth(parent->GetWidth() / 2);
			node1->SetDepth(parent->GetDepth() / 2);
			node2->SetWidth(parent->GetWidth() / 2);
			node2->SetDepth(parent->GetDepth() / 2);
			node3->SetWidth(parent->GetWidth() / 2);
			node3->SetDepth(parent->GetDepth() / 2);

			CreateQuadTreeChildren(node0, remainingDepth - 1);
			CreateQuadTreeChildren(node1, remainingDepth - 1);
			CreateQuadTreeChildren(node2, remainingDepth - 1);
			CreateQuadTreeChildren(node3, remainingDepth - 1);

			QuadNode* children = new QuadNode[4];
			children[0] = *node0;
			children[1] = *node1;
			children[2] = *node2;
			children[3] = *node3;

			parent->SetChildren(children);
		}
		else
		{
			// Add leaf data
			parent->SetIsLeaf(true);
			std::vector<D3DCustomVertex*> leafVertices;

			// Add all triangles within the bounds, borders included
			for (int i = 0; i < amountOfVertices - 2; i += 3)
			{
				D3DCustomVertex* vertex0 = &vertices[i];
				D3DCustomVertex* vertex1 = &vertices[i + 1];
				D3DCustomVertex* vertex2 = &vertices[i + 2];

				// if one of the points is within bounds
				if ((vertex0->x >= parent->GetMinX() && vertex0->x <= parent->GetMaxX()
					&& vertex0->z >= parent->GetMinZ() && vertex0->z <= parent->GetMaxZ())
					||
					(vertex1->x >= parent->GetMinX() && vertex1->x <= parent->GetMaxX()
					&& vertex1->z >= parent->GetMinZ() && vertex1->z <= parent->GetMaxZ())
					||
					(vertex2->x >= parent->GetMinX() && vertex2->x <= parent->GetMaxX()
					&& vertex2->z >= parent->GetMinZ() && vertex2->z <= parent->GetMaxZ()))
				{
					leafVertices.push_back(vertex0);
					leafVertices.push_back(vertex1);
					leafVertices.push_back(vertex2);
				}
			}

			int amountOfVertices = leafVertices.size();
			D3DCustomVertex* vertices = new D3DCustomVertex[amountOfVertices];
			for (int i = 0; i < amountOfVertices; ++i)
			{
				vertices[i] = *leafVertices[i];

			}
			parent->SetAmountOfVertices(amountOfVertices);
			parent->SetVertices(vertices);
		}
	}
}