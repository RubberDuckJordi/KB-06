#ifndef __SCENE_ENTITY_H__
#define __SCENE_ENTITY_H__

#include <d3dx9.h>
#include "Normal.h"

namespace Scene{
	class Entity {
	public:
		virtual void Update() = 0;
		void SetPosition(float x, float y, float z);
		void SetRotation(float yaw, float pitch, float roll);
		void SetScale(float scaleX, float scaleY, float scaleZ);
		Resource::Normal GetPosition();
		Resource::Normal GetRotation();
		Resource::Normal GetScale();

		D3DXMATRIXA16 finalMatrix;
		D3DXMATRIXA16 rotationMatrix;

	protected:
		float x, y, z;
		float yaw, pitch, roll;
		float scaleX, scaleY, scaleZ;
		D3DXMATRIXA16 positionMatrix, scaleMatrix;

		void MultiplyMatrices();

	private:
	};
}

#endif
