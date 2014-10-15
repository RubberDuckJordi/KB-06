#include "Collidable.h"

namespace pengine
{
	BEAM* Collidable::GetCollisionBox()
	{
		return &collisionBox;
	}

	bool Collidable::CheckCollision(Collidable* collidable)
	{
		BEAM* other = collidable->GetCollisionBox();

		if (collisionBox.x + collisionBox.width < other->x) return false;
		if (collisionBox.x > other->x + other->width) return false;
		if (collisionBox.y + collisionBox.height <  other->y) return false;
		if (collisionBox.y > other->y + other->height) return false;
		if (collisionBox.z + collisionBox.depth <  other->z) return false;
		if (collisionBox.z > other->z + other->depth) return false;

		return true;
	}

	void Collidable::DrawCollidable(Renderer* renderer)
	{
		// For drawing
		int amountOfVertices = 8;
		int amountOfIndices = 36;
		D3DCustomVertex* vertices;
		int* indices = new int[amountOfIndices];
		VertexBufferWrapper* vertexBuffer;
		IndexBufferWrapper* indexBuffer;

		vertices = new D3DCustomVertex[amountOfVertices];

		vertices[0].x = collisionBox.rotFrontBottomLeft.x;
		vertices[0].y = collisionBox.rotFrontBottomLeft.y;
		vertices[0].z = collisionBox.rotFrontBottomLeft.z;
		vertices[0].tu = 0.0f;
		vertices[0].tv = 0.0f;

		vertices[1].x = collisionBox.rotFrontBottomRight.x;
		vertices[1].y = collisionBox.rotFrontBottomRight.y;
		vertices[1].z = collisionBox.rotFrontBottomRight.z;
		vertices[1].tu = 0.0f;
		vertices[1].tv = 0.0f;

		vertices[2].x = collisionBox.rotBackBottomLeft.x;
		vertices[2].y = collisionBox.rotBackBottomLeft.y;
		vertices[2].z = collisionBox.rotBackBottomLeft.z;
		vertices[2].tu = 0.0f;
		vertices[2].tv = 0.0f;

		vertices[3].x = collisionBox.rotBackBottomRight.x;
		vertices[3].y = collisionBox.rotBackBottomRight.y;
		vertices[3].z = collisionBox.rotBackBottomRight.z;
		vertices[3].tu = 0.0f;
		vertices[3].tv = 0.0f;

		vertices[4].x = collisionBox.rotFrontTopLeft.x;
		vertices[4].y = collisionBox.rotFrontTopLeft.y;
		vertices[4].z = collisionBox.rotFrontTopLeft.z;
		vertices[4].tu = 0.0f;
		vertices[4].tv = 0.0f;

		vertices[5].x = collisionBox.rotFrontTopRight.x;
		vertices[5].y = collisionBox.rotFrontTopRight.y;
		vertices[5].z = collisionBox.rotFrontTopRight.z;
		vertices[5].tu = 0.0f;
		vertices[5].tv = 0.0f;

		vertices[6].x = collisionBox.rotBackTopLeft.x;
		vertices[6].y = collisionBox.rotBackTopLeft.y;
		vertices[6].z = collisionBox.rotBackTopLeft.z;
		vertices[6].tu = 0.0f;
		vertices[6].tv = 0.0f;

		vertices[7].x = collisionBox.rotBackTopRight.x;
		vertices[7].y = collisionBox.rotBackTopRight.y;
		vertices[7].z = collisionBox.rotBackTopRight.z;
		vertices[7].tu = 0.0f;
		vertices[7].tv = 0.0f;

		vertexBuffer = renderer->CreateVertexBuffer(vertices, amountOfVertices, D3DCustomVertexFVF);

		indices[0] = 0; indices[1] = 1; indices[2] = 2;//bottom
		indices[3] = 2; indices[4] = 1; indices[5] = 3;
		indices[6] = 0; indices[7] = 4; indices[8] = 6;//left
		indices[9] = 0; indices[10] = 2; indices[11] = 6;
		indices[12] = 0; indices[13] = 1; indices[14] = 5;//front
		indices[15] = 0; indices[16] = 4; indices[17] = 5;
		indices[18] = 1; indices[19] = 3; indices[20] = 7;//right
		indices[21] = 5; indices[22] = 7; indices[23] = 1;
		indices[24] = 2; indices[25] = 3; indices[26] = 7;//back
		indices[27] = 2; indices[28] = 6; indices[29] = 7;
		indices[30] = 4; indices[31] = 5; indices[32] = 7;//top
		indices[33] = 4; indices[34] = 6; indices[35] = 7;

		indexBuffer = renderer->CreateIndexBuffer(indices, amountOfIndices);
		
		Matrix* renderMatrix = new Matrix();
		Matrix::CreateMatrix(collisionBox.x, 0, collisionBox.z, 0, 0, 0, 1, 1, 1, renderMatrix);
		renderer->SetActiveMatrix(renderMatrix);
		renderer->DrawIndexedVertexBuffer(vertexBuffer, indexBuffer, amountOfVertices, 12);

		delete[] vertices;
		delete vertexBuffer;
		delete[] indices;
		delete indexBuffer;
	}
}