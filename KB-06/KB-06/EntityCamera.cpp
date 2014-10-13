#include "EntityCamera.h"
#include "Vector3.h"
#include <sstream>

namespace pengine
{
	EntityCamera::EntityCamera()
	{
		viewMatrix = new PEngineMatrix();
		upVec = new Vector3(0, 1);
		SetProjectionMatrix();
	}

	EntityCamera::~EntityCamera()
	{

	}

	void EntityCamera::UpdateLogic(float deltaTime, std::map<Input, long>* actions)
	{
		for (std::map<Input, long>::iterator iterator = (*actions).begin(); iterator != (*actions).end(); iterator++)
		{
			float speed = static_cast<float>(iterator->second);
			switch (iterator->first)
			{
			case Input::KEY_S:
				this->AddPosition(0.0f, 0.0f, 0.5f);
				break;
			case Input::KEY_W:
				this->AddPosition(0.0f, 0.0f, -0.5f);
				break;
			case Input::KEY_D:
				this->AddPosition(-0.5f, 0.0f, 0.0f);
				break;
			case Input::KEY_A:
				this->AddPosition(0.5f, 0.0f, 0.0f);
				break;
			case Input::KEY_SPACE:
				this->AddPosition(0.0f, 0.5f, 0.0f);
				break;
			case Input::KEY_LSHIFT:
				this->AddPosition(0.0f, -0.5f, 0.0f);
				break;
			case Input::KEY_DOWN:
				SetLookAtPosition(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z + 0.1f, rollDegrees);
				break;
			case Input::KEY_UP:
				SetLookAtPosition(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z - 0.1f, rollDegrees);
				break;
			case Input::KEY_LEFT:
				SetLookAtPosition(lookAtPosition.x + 0.1f, lookAtPosition.y, lookAtPosition.z, rollDegrees);
				break;
			case Input::KEY_RIGHT:
				SetLookAtPosition(lookAtPosition.x - 0.1f, lookAtPosition.y, lookAtPosition.z, rollDegrees);
				break;
			case Input::KEY_BACK:
				SetLookAtPosition(lookAtPosition.x, lookAtPosition.y + 0.1f, lookAtPosition.z, rollDegrees);
				break;
			case Input::KEY_RETURN:
				SetLookAtPosition(lookAtPosition.x, lookAtPosition.y - 0.1f, lookAtPosition.z, rollDegrees);
				break;
			case Input::KEY_G:
				this->AddPosition(0.0f, 0.0f, 0.5f);
				this->SetLookAtPosition(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z + 0.5f, rollDegrees);
				break;
			case Input::KEY_T:
				this->AddPosition(0.0f, 0.0f, -0.5f);
				this->SetLookAtPosition(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z - 0.5f, rollDegrees);
				break;
			case Input::KEY_H:
				this->AddPosition(-0.5f, 0.0f, 0.0f);
				this->SetLookAtPosition(lookAtPosition.x - 0.5f, lookAtPosition.y, lookAtPosition.z, rollDegrees);
				break;
			case Input::KEY_F:
				this->AddPosition(0.5f, 0.0f, 0.0f);
				this->SetLookAtPosition(lookAtPosition.x + 0.5f, lookAtPosition.y, lookAtPosition.z, rollDegrees);
				break;
			case Input::KEY_Y:
				this->AddPosition(0.0f, 0.5f, 0.0f);
				this->SetLookAtPosition(lookAtPosition.x, lookAtPosition.y + 0.5f, lookAtPosition.z, rollDegrees);
				break;
			case Input::KEY_R:
				this->AddPosition(0.0f, -0.5f, 0.0f);
				this->SetLookAtPosition(lookAtPosition.x, lookAtPosition.y - 0.5f, lookAtPosition.z, rollDegrees);
				break;
			case Input::KEY_U:
				++rollDegrees;
				this->SetLookAtPosition(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z, rollDegrees);
				break;
			case Input::KEY_E:
				--rollDegrees;
				this->SetLookAtPosition(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z, rollDegrees);
				break;
			default:
				break;
			}
		}
	}

	// Camera's worden niet getekend
	void EntityCamera::Draw(Renderer* renderer)
	{
		bool debug = false;
		if (debug)
		{
			//could draw a hardcoded wireframe... (old code was old xloader based and stuff...)
		}
	}

	Vertex* EntityCamera::GetPosition()
	{
		return &position;
	}

	CameraData EntityCamera::GetCameraData()
	{
		CameraData d = { position.x, position.y, position.z, lookAtPosition.x, lookAtPosition.y, lookAtPosition.z, upVec->x, upVec->y, upVec->z };
		return d;
	}

	void EntityCamera::SetLookAtEntity(Entity* entity)
	{
		Vertex* position = entity->GetPosition();
		SetLookAtPosition(position->x, position->y, position->z, 0.0f);
	}

	void EntityCamera::SetThirdPersonEntity(Entity* entity, float distance, float height)
	{
		//rotationMatrix = new PEngineMatrix();
		// TODO: rotation & calculate axis
		Vertex* entityPosition = entity->GetPosition();
		Vertex* cameraPosition = new Vertex();

		SetPosition(entityPosition->x, entityPosition->y, entityPosition->z);

		float xDelta = (distance * sin((M_PI / 180)* +entity->GetRotation()->x));
		float yDelta = (distance * sin((M_PI / 180)*(entity->GetRotation()->y))) * (cos((M_PI / 180)* entity->GetRotation()->x));
		float zDelta = (distance * cos((M_PI / 180)*(entity->GetRotation()->y))) * (cos((M_PI / 180)* entity->GetRotation()->x));

		AddPosition(xDelta, yDelta + height, zDelta);

		SetLookAtEntity(entity);
	}

	void EntityCamera::SetLookAtPosition(float x, float y, float z, float rollDegrees)
	{
		lookAtPosition =  { x, y, z };
		Vector3 pos = { position.x, position.y, position.z };

		Vector3 zaxis = Vector3::normalize(lookAtPosition - pos);
		Vector3 xaxis = Vector3::normalize(Vector3::cross(*upVec, zaxis));
		Vector3 yaxis = Vector3::cross(zaxis, xaxis);

		viewMatrix->_11 = xaxis.x;
		viewMatrix->_21 = xaxis.y;
		viewMatrix->_31 = xaxis.z;
		viewMatrix->_41 = -Vector3::dot(xaxis, pos);

		viewMatrix->_12 = yaxis.x;
		viewMatrix->_22 = yaxis.y;
		viewMatrix->_32 = yaxis.z;
		viewMatrix->_42 = -Vector3::dot(yaxis, pos);

		viewMatrix->_13 = zaxis.x;
		viewMatrix->_23 = zaxis.y;
		viewMatrix->_33 = zaxis.z;
		viewMatrix->_43 = -Vector3::dot(zaxis, pos);

		viewMatrix->_14 = 0.0f;
		viewMatrix->_24 = 0.0f;
		viewMatrix->_34 = 0.0f;
		viewMatrix->_44 = 1.0f;

		BuildViewFrustum();
	}

	bool EntityCamera::SphereInFrustum(Vertex* position, float radius)
	{
		for (int i = 0; i < 6; i++)
		{
			//manual D3DXPlaneDotCoord()
			if ((frustrumPlane[i].a * position->x +
				frustrumPlane[i].b * position->y +
				frustrumPlane[i].c * position->z +
				frustrumPlane[i].d * 1
				) + radius < 0)
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	void EntityCamera::SetProjectionMatrix(){
		projectionMatrix._11 = 2.41421342;
		projectionMatrix._12 = 0;
		projectionMatrix._13 = 0;
		projectionMatrix._14 = 0;
		projectionMatrix._21 = 0;
		projectionMatrix._22 = 2.41421342;
		projectionMatrix._23 = 0;
		projectionMatrix._24 = 0;
		projectionMatrix._31 = 0;
		projectionMatrix._32 = 0;
		projectionMatrix._33 = 1.00100100;
		projectionMatrix._34 = 1;
		projectionMatrix._41 = 0;
		projectionMatrix._42 = 0;
		projectionMatrix._43 = -1.00100100;
		projectionMatrix._44 = 0;
	}

	void EntityCamera::BuildViewFrustum()
	{
		// Left plane
		PEngineMatrix newMatrix;
		RenderMatrix::MultiplyMatrices(viewMatrix, &projectionMatrix, &newMatrix);
		frustrumPlane[0].a = newMatrix._14 + newMatrix._11;
		frustrumPlane[0].b = newMatrix._24 + newMatrix._21;
		frustrumPlane[0].c = newMatrix._34 + newMatrix._31;
		frustrumPlane[0].d = newMatrix._44 + newMatrix._41;
		// Right plane
		frustrumPlane[1].a = newMatrix._14 - newMatrix._11;
		frustrumPlane[1].b = newMatrix._24 - newMatrix._21;
		frustrumPlane[1].c = newMatrix._34 - newMatrix._31;
		frustrumPlane[1].d = newMatrix._44 - newMatrix._41;
		// Top plane
		frustrumPlane[2].a = newMatrix._14 - newMatrix._12;
		frustrumPlane[2].b = newMatrix._24 - newMatrix._22;
		frustrumPlane[2].c = newMatrix._34 - newMatrix._32;
		frustrumPlane[2].d = newMatrix._44 - newMatrix._42;
		// Bottom plane
		frustrumPlane[3].a = newMatrix._14 + newMatrix._12;
		frustrumPlane[3].b = newMatrix._24 + newMatrix._22;
		frustrumPlane[3].c = newMatrix._34 + newMatrix._32;
		frustrumPlane[3].d = newMatrix._44 + newMatrix._42;
		// Near plane
		frustrumPlane[4].a = newMatrix._13;
		frustrumPlane[4].b = newMatrix._23;
		frustrumPlane[4].c = newMatrix._33;
		frustrumPlane[4].d = newMatrix._43;
		// Far plane
		frustrumPlane[5].a = newMatrix._14 - newMatrix._13;
		frustrumPlane[5].b = newMatrix._24 - newMatrix._23;
		frustrumPlane[5].c = newMatrix._34 - newMatrix._33;
		frustrumPlane[5].d = newMatrix._44 - newMatrix._43;

		// Normalize planes
		for (int i = 0; i < 6; i++)
		{
			//manual D3DXPlaneNormalize()
			float LengthSq = frustrumPlane[i].a * frustrumPlane[i].a +
				frustrumPlane[i].b * frustrumPlane[i].b +
				frustrumPlane[i].c * frustrumPlane[i].c;

			float ReciprocalLength = 1.0f / sqrt(LengthSq);
			frustrumPlane[i].a = frustrumPlane[i].a * ReciprocalLength;
			frustrumPlane[i].b = frustrumPlane[i].b * ReciprocalLength;
			frustrumPlane[i].c = frustrumPlane[i].c * ReciprocalLength;
			frustrumPlane[i].d = frustrumPlane[i].d * ReciprocalLength;
		};
	}
}