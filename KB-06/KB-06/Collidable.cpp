#include "Collidable.h"

namespace pengine
{
	RECTANGLE* Collidable::GetCollisionBox()
	{
		return &collisionBox;
	}

	bool Collidable::CheckCollision(Collidable* collidable)
	{
		RECTANGLE* other = collidable->GetCollisionBox();

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
		amountOfIndices = 36;

		if (vertices != NULL)
		{
			delete[] vertices;
		}
		if (vertexBuffer != NULL)
		{
			delete vertexBuffer;
		}

		vertices = new D3DCustomVertex[amountOfIndices];

		vertices[0].x = collisionBox.x;
		vertices[0].y = collisionBox.y + collisionBox.height;
		vertices[0].z = collisionBox.z + collisionBox.depth;
		vertices[0].tu = 0.0f;
		vertices[0].tv = 0.0f;

		vertices[1].x = collisionBox.x;
		vertices[1].y = collisionBox.y + collisionBox.height;
		vertices[1].z = collisionBox.z;
		vertices[1].tu = 0.2f;
		vertices[1].tv = 0.0f;

		vertices[2].x = collisionBox.x;
		vertices[2].y = collisionBox.y;
		vertices[2].z = collisionBox.z + collisionBox.depth;
		vertices[2].tu = 0.0f;
		vertices[2].tv = 1.0f;

		//Left down
		vertices[3].x = collisionBox.x;
		vertices[3].y = collisionBox.y + collisionBox.height;
		vertices[3].z = collisionBox.z;
		vertices[3].tu = 0.2f;
		vertices[3].tv = 0.0f;

		vertices[4].x = collisionBox.x;
		vertices[4].y = collisionBox.y;
		vertices[4].z = collisionBox.z;
		vertices[4].tu = 0.2f;
		vertices[4].tv = 1.0f;

		vertices[5].x = collisionBox.x;
		vertices[5].y = collisionBox.y;
		vertices[5].z = collisionBox.z + collisionBox.depth;
		vertices[5].tu = 0.0f;
		vertices[5].tv = 1.0f;

		//Front up
		vertices[6].x = collisionBox.x;
		vertices[6].y = collisionBox.y + collisionBox.height;
		vertices[6].z = collisionBox.z;
		vertices[6].tu = 0.2f;
		vertices[6].tv = 0.0f;

		vertices[7].x = collisionBox.x + collisionBox.width;
		vertices[7].y = collisionBox.y + collisionBox.height;
		vertices[7].z = collisionBox.z;
		vertices[7].tu = 0.4f;
		vertices[7].tv = 0.0f;

		vertices[8].x = collisionBox.x;
		vertices[8].y = collisionBox.y;
		vertices[8].z = collisionBox.z;
		vertices[8].tu = 0.2f;
		vertices[8].tv = 1.0f;

		//Front down
		vertices[9].x = collisionBox.x + collisionBox.width;
		vertices[9].y = collisionBox.y + collisionBox.height;
		vertices[9].z = collisionBox.z;
		vertices[9].tu = 0.4f;
		vertices[9].tv = 0.0f;

		vertices[10].x = collisionBox.x + collisionBox.width;
		vertices[10].y = collisionBox.y;
		vertices[10].z = collisionBox.z;
		vertices[10].tu = 0.4f;
		vertices[10].tv = 1.0f;

		vertices[11].x = collisionBox.x;
		vertices[11].y = collisionBox.y;
		vertices[11].z = collisionBox.z;
		vertices[11].tu = 0.2f;
		vertices[11].tv = 1.0f;

		//Right up
		vertices[12].x = collisionBox.x + collisionBox.width;
		vertices[12].y = collisionBox.y + collisionBox.height;
		vertices[12].z = collisionBox.z;
		vertices[12].tu = 0.4f;
		vertices[12].tv = 0.0f;

		vertices[13].x = collisionBox.x + collisionBox.width;
		vertices[13].y = collisionBox.y + collisionBox.height;
		vertices[13].z = collisionBox.z + collisionBox.depth;
		vertices[13].tu = 0.6f;
		vertices[13].tv = 0.0f;

		vertices[14].x = collisionBox.x + collisionBox.width;
		vertices[14].y = collisionBox.y;
		vertices[14].z = collisionBox.z;
		vertices[14].tu = 0.4f;
		vertices[14].tv = 1.0f;

		//Right down
		vertices[15].x = collisionBox.x + collisionBox.width;
		vertices[15].y = collisionBox.y + collisionBox.height;
		vertices[15].z = collisionBox.z + collisionBox.depth;
		vertices[15].tu = 0.6f;
		vertices[15].tv = 0.0f;

		vertices[16].x = collisionBox.x + collisionBox.width;
		vertices[16].y = collisionBox.y;
		vertices[16].z = collisionBox.z + collisionBox.depth;
		vertices[16].tu = 0.6f;
		vertices[16].tv = 1.0f;

		vertices[17].x = collisionBox.x + collisionBox.width;
		vertices[17].y = collisionBox.y;
		vertices[17].z = collisionBox.z;
		vertices[17].tu = 0.4f;
		vertices[17].tv = 1.0f;

		//Back up
		vertices[18].x = collisionBox.x + collisionBox.width;
		vertices[18].y = collisionBox.y + collisionBox.height;
		vertices[18].z = collisionBox.z + collisionBox.depth;
		vertices[18].tu = 0.6f;
		vertices[18].tv = 0.0f;

		vertices[19].x = collisionBox.x;
		vertices[19].y = collisionBox.y + collisionBox.height;
		vertices[19].z = collisionBox.z + collisionBox.depth;
		vertices[19].tu = 0.8f;
		vertices[19].tv = 0.0f;

		vertices[20].x = collisionBox.x + collisionBox.width;
		vertices[20].y = collisionBox.y;
		vertices[20].z = collisionBox.z + collisionBox.depth;
		vertices[20].tu = 0.6f;
		vertices[20].tv = 1.0f;

		//Back down
		vertices[21].x = collisionBox.x;
		vertices[21].y = collisionBox.y + collisionBox.height;
		vertices[21].z = collisionBox.z + collisionBox.depth;
		vertices[21].tu = 0.8f;
		vertices[21].tv = 0.0f;

		vertices[22].x = collisionBox.x;
		vertices[22].y = collisionBox.y;
		vertices[22].z = collisionBox.z + collisionBox.depth;
		vertices[22].tu = 0.8f;
		vertices[22].tv = 1.0f;

		vertices[23].x = collisionBox.x + collisionBox.width;
		vertices[23].y = collisionBox.y;
		vertices[23].z = collisionBox.z + collisionBox.depth;
		vertices[23].tu = 0.6f;
		vertices[23].tv = 1.0f;

		//Top up
		vertices[24].x = collisionBox.x;
		vertices[24].y = collisionBox.y + collisionBox.height;
		vertices[24].z = collisionBox.z + collisionBox.depth;
		vertices[24].tu = 0.8f;
		vertices[24].tv = 0.0f;

		vertices[25].x = collisionBox.x + collisionBox.width;
		vertices[25].y = collisionBox.y + collisionBox.height;
		vertices[25].z = collisionBox.z + collisionBox.depth;
		vertices[25].tu = 1.0f;
		vertices[25].tv = 0.0f;

		vertices[26].x = collisionBox.x;
		vertices[26].y = collisionBox.y + collisionBox.height;
		vertices[26].z = collisionBox.z;
		vertices[26].tu = 0.8f;
		vertices[26].tv = 1.0f;

		//Top down
		vertices[27].x = collisionBox.x + collisionBox.width;
		vertices[27].y = collisionBox.y + collisionBox.height;
		vertices[27].z = collisionBox.z + collisionBox.depth;
		vertices[27].tu = 1.0f;
		vertices[27].tv = 0.0f;

		vertices[28].x = collisionBox.x + collisionBox.width;
		vertices[28].y = collisionBox.y + collisionBox.height;
		vertices[28].z = collisionBox.z;
		vertices[28].tu = 1.0f;
		vertices[28].tv = 1.0f;

		vertices[29].x = collisionBox.x;
		vertices[29].y = collisionBox.y + collisionBox.height;
		vertices[29].z = collisionBox.z;
		vertices[29].tu = 0.8f;
		vertices[29].tv = 1.0f;

		//Down up
		vertices[30].x = collisionBox.x;
		vertices[30].y = collisionBox.y;
		vertices[30].z = collisionBox.z;
		vertices[30].tu = 0.3f;
		vertices[30].tv = 1.0f;

		vertices[31].x = collisionBox.x + collisionBox.width;
		vertices[31].y = collisionBox.y;
		vertices[31].z = collisionBox.z;
		vertices[31].tu = 0.3f;
		vertices[31].tv = 1.0f;

		vertices[32].x = collisionBox.x;
		vertices[32].y = collisionBox.y;
		vertices[32].z = collisionBox.z + collisionBox.depth;
		vertices[32].tu = 0.3f;
		vertices[32].tv = 1.0f;

		//Down down
		vertices[33].x = collisionBox.x + collisionBox.width;
		vertices[33].y = collisionBox.y;
		vertices[33].z = collisionBox.z;
		vertices[33].tu = 0.3f;
		vertices[33].tv = 1.0f;

		vertices[34].x = collisionBox.x + collisionBox.width;
		vertices[34].y = collisionBox.y;
		vertices[34].z = collisionBox.z + collisionBox.depth;
		vertices[34].tu = 0.3f;
		vertices[34].tv = 1.0f;

		vertices[35].x = collisionBox.x;
		vertices[35].y = collisionBox.y;
		vertices[35].z = collisionBox.z + collisionBox.depth;
		vertices[35].tu = 0.3f;
		vertices[35].tv = 1.0f;

		vertexBuffer = renderer->CreateVertexBuffer(vertices, amountOfIndices, D3DCustomVertexFVF);
		
		RenderMatrix* renderMatrix = new RenderMatrix();
		renderer->SetActiveMatrix(renderMatrix->theMatrix);
		renderer->DrawVertexBuffer(vertexBuffer, amountOfIndices);
	}
}