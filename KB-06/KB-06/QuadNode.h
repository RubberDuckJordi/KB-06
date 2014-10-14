#ifndef _PENGINE_QUADNODE_H_
#define _PENGINE_QUADNODE_H_

#include "Vertex.h"
#include "CustomD3DVertex.h"
#include "LoggerPool.h"

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

		// Sets Level of detail for this node and all children
		// Quality is divided by level of detail
		void SetLevelOfDetail(unsigned short levelOfDetail);
		unsigned short GetLevelOfDetail();

		QuadNode* GetChildren();
		void SetChildren(QuadNode* children);

		D3DCustomVertex* GetVertices();
		void SetVertices(D3DCustomVertex* vertices);

		unsigned int GetAmountOfVertices();
		void SetAmountOfVertices(unsigned int amountOfVertices);

		int GetWidth();
		int GetDepth();
		void SetWidth(int width);
		void SetDepth(int depth);

		// Returns terrain vertices of all children
		void GetAllChildrenVertices(D3DCustomVertex*& vertices, int& amountOfVertices);

	private:
		QuadNode* parent;
		bool isLeaf;
		unsigned short levelOfDetail;
		// Only uses x and z. Y is omitted because we are using a 2d tree.
		float minX;
		float maxX;
		float minZ;
		float maxZ;

		int width;
		int depth;

		// Only for branches and root node
		QuadNode* children;

		// Only for leaves
		// Terrain vertices
		D3DCustomVertex* vertices;
		unsigned int amountOfVertices;

		Logger* logger;
	};
}


#endif