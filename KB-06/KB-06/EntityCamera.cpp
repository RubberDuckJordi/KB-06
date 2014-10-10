#include "EntityCamera.h"
#include "Vector3.h"
#include <sstream>

namespace pengine
{
	EntityCamera::EntityCamera()
	{
		RenderMatrix* temp = new RenderMatrix();
		temp->CreateMatrix(0, 0, 0, 0, 0, 0, 1, 1, 1, temp->theMatrix);
		rotationMatrix = temp->theMatrix;
		upVec = new Vector3(0, 1);
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
		Vector3 lookat = { lookAtPosition.x, lookAtPosition.y, lookAtPosition.z };
		Vector3 pos = { position.x, position.y, position.z };
		Vector3 objectUpVector = { 0.0f, 1.0f, 0.0f };

		Vector3 zaxis = Vector3::normalize(lookat - pos);
		Vector3 xaxis = Vector3::normalize(Vector3::cross(objectUpVector, zaxis));
		Vector3 yaxis = Vector3::cross(zaxis, xaxis);

		rotationMatrix->_11 = xaxis.x;
		rotationMatrix->_12 = xaxis.y;
		rotationMatrix->_13 = xaxis.z;
		rotationMatrix->_14 = 0.0f;

		rotationMatrix->_21 = yaxis.x;
		rotationMatrix->_22 = yaxis.y;
		rotationMatrix->_23 = yaxis.z;
		rotationMatrix->_24 = 0.0f;

		rotationMatrix->_31 = zaxis.x;
		rotationMatrix->_32 = zaxis.y;
		rotationMatrix->_33 = zaxis.z;
		rotationMatrix->_34 = 0.0f;

		rotationMatrix->_41 = 0.0f;
		rotationMatrix->_42 = 0.0f;
		rotationMatrix->_43 = 0.0f;
		rotationMatrix->_44 = 1.0f;

		if (lookAtPosition.z < position.z)
		{
			upVec->x = cos(RADIANS(rollDegrees + 90));
			upVec->y = sin(RADIANS(rollDegrees + 90));
		}
		else
		{
			upVec->x = cos(RADIANS(-rollDegrees + 90));
			upVec->y = sin(RADIANS(-rollDegrees + 90));
		}

		lookAtPosition = { x, y, z };
	}
}