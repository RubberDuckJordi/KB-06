#include "EntityCamera.h"
#include "Vector3.h"
#include <sstream>

namespace pengine
{
	EntityCamera::EntityCamera()
	{
		viewMatrix = new Matrix();
		SetProjectionMatrix(M_PI / 4, 1.0f, 1.0f, 1000.0f);
		upVec = new Vector3(0, 1);
		lastKnownRotation = new Vector3();
		lastKnownRotation->x = 0;//yaw
		lastKnownRotation->y = 0;//pitch
		lastKnownRotation->z = 0;//roll
	}

	EntityCamera::~EntityCamera()
	{

	}

	void EntityCamera::UpdateLogic(float deltaTime, std::map<Input, long>* actions)
	{
		for (std::map<Input, long>::iterator iterator = (*actions).begin(); iterator != (*actions).end(); iterator++)
		{
			//float speed = static_cast<float>(iterator->second);
			switch (iterator->first)
			{
			case Input::KEY_S:
			{
				float deltaX = -sin(RADIANS(lastKnownRotation->x)) * deltaTime * 1.0f;
				float deltaZ = -cos(RADIANS(lastKnownRotation->x)) * deltaTime * 1.0f;
				this->AddPosition(deltaX, 0.0f, deltaZ);
				this->SetLookAtPosition(lookAtPosition.x + deltaX, lookAtPosition.y, lookAtPosition.z + deltaZ, rollDegrees);
				break;
			}
			case Input::KEY_W:
			{
				float deltaX = sin(RADIANS(lastKnownRotation->x)) * deltaTime * 1.0f;
				float deltaZ = cos(RADIANS(lastKnownRotation->x)) * deltaTime * 1.0f;
				this->AddPosition(deltaX, 0.0f, deltaZ);
				this->SetLookAtPosition(lookAtPosition.x + deltaX, lookAtPosition.y, lookAtPosition.z + deltaZ, rollDegrees);
				break;
			}
			case Input::KEY_D:
			{
				float deltaX = sin(RADIANS(lastKnownRotation->x + 90)) * deltaTime * 1.0f;
				float deltaZ = cos(RADIANS(lastKnownRotation->x + 90)) * deltaTime * 1.0f;
				this->AddPosition(deltaX, 0.0f, deltaZ);
				this->SetLookAtPosition(lookAtPosition.x + deltaX, lookAtPosition.y, lookAtPosition.z + deltaZ, rollDegrees);
				break;
			}
			case Input::KEY_A:
			{
				float deltaX = sin(RADIANS(lastKnownRotation->x - 90)) * deltaTime * 1.0f;
				float deltaZ = cos(RADIANS(lastKnownRotation->x - 90)) * deltaTime * 1.0f;
				this->AddPosition(deltaX, 0.0f, deltaZ);
				this->SetLookAtPosition(lookAtPosition.x + deltaX, lookAtPosition.y, lookAtPosition.z + deltaZ, rollDegrees);
				break;
			}
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
			case Input::MOUSE_X:
				lastKnownRotation->x += iterator->second / 10.0f;
				this->SetRotation(lastKnownRotation->x, 0, 0);
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

	Vector3* EntityCamera::GetPosition()
	{
		return &position;
	}

	Vector3* EntityCamera::GetLookAtPosition()
	{
		return &lookAtPosition;
	}

	CameraData EntityCamera::GetCameraData()
	{
		CameraData d = { position.x, position.y, position.z, lookAtPosition.x, lookAtPosition.y, lookAtPosition.z, upVec->x, upVec->y, upVec->z };
		return d;
	}

	void EntityCamera::SetLookAtEntity(Entity* entity)
	{
		Vector3* position = entity->GetPosition();
		SetLookAtPosition(position->x, position->y, position->z, 0.0f);
	}

	void EntityCamera::SetThirdPersonEntity(Entity* entity, float distance, float height)
	{
		//rotationMatrix = new PEngineMatrix();
		// TODO: rotation & calculate axis
		Vector3* entityPosition = entity->GetPosition();
		Vector3* cameraPosition = new Vector3();

		SetPosition(entityPosition->x, entityPosition->y, entityPosition->z);

		float xDelta = (distance * sin((M_PI / 180)* +entity->GetRotation()->x));
		float yDelta = (distance * sin((M_PI / 180)*(entity->GetRotation()->y))) * (cos((M_PI / 180)* entity->GetRotation()->x));
		float zDelta = (distance * cos((M_PI / 180)*(entity->GetRotation()->y))) * (cos((M_PI / 180)* entity->GetRotation()->x));

		AddPosition(xDelta, yDelta + height, zDelta);

		SetLookAtEntity(entity);
	}

	void EntityCamera::SetRotation(float yawDegrees, float pitchDegrees, float rollDegrees)
	{
		float lookAtX = sin(RADIANS(yawDegrees)) * 5.0f;
		float lookAtZ = cos(RADIANS(yawDegrees)) * 5.0f;
		float lookAtY = 0.0f;//not sure how to do y rotation yet sin(RADIANS(pitchDegrees)) * 5.0f;
		SetLookAtPosition(position.x + lookAtX, position.y + lookAtY, position.z + lookAtZ, rollDegrees);
	}

	void EntityCamera::SetLookAtPosition(float x, float y, float z, float rollDegrees)
	{
		lookAtPosition = { x, y, z };
		Vector3 pos = { position.x, position.y, position.z };

		Matrix::CreateLookAtMatrix(pos, lookAtPosition, { 0, 1, 0 }, viewMatrix);

		BuildViewFrustum();
	}

	bool EntityCamera::SphereInFrustum(Vector3* position, float radius)
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

	void EntityCamera::SetProjectionMatrix(float fovY, float aspectRatio, float nearClippingPlane, float farClippingPlane)
	{
		float yScale = (1 / tan(fovY / 2));
		float xScale = aspectRatio * yScale;

		projectionMatrix[0] = xScale;
		projectionMatrix[1] = 0;
		projectionMatrix[2] = 0;
		projectionMatrix[3] = 0;

		projectionMatrix[4] = 0;
		projectionMatrix[5] = yScale;
		projectionMatrix[6] = 0;
		projectionMatrix[7] = 0;

		projectionMatrix[8] = 0;
		projectionMatrix[9] = 0;
		projectionMatrix[10] = farClippingPlane / (farClippingPlane - nearClippingPlane);
		projectionMatrix[11] = 1;

		projectionMatrix[12] = 0;
		projectionMatrix[13] = 0;
		projectionMatrix[14] = -nearClippingPlane * farClippingPlane / (farClippingPlane - nearClippingPlane);
		projectionMatrix[15] = 0;
	}

	void EntityCamera::BuildViewFrustum()
	{
		Matrix newMatrix;
		newMatrix = *viewMatrix * projectionMatrix;

		// Left plane
		frustrumPlane[0].a = newMatrix[3] + newMatrix[0];
		frustrumPlane[0].b = newMatrix[7] + newMatrix[4];
		frustrumPlane[0].c = newMatrix[11] + newMatrix[8];
		frustrumPlane[0].d = newMatrix[15] + newMatrix[12];
		// Right plane
		frustrumPlane[1].a = newMatrix[3] - newMatrix[0];
		frustrumPlane[1].b = newMatrix[7] - newMatrix[4];
		frustrumPlane[1].c = newMatrix[11] - newMatrix[8];
		frustrumPlane[1].d = newMatrix[15] - newMatrix[12];
		// Top plane
		frustrumPlane[2].a = newMatrix[3] - newMatrix[1];
		frustrumPlane[2].b = newMatrix[7] - newMatrix[5];
		frustrumPlane[2].c = newMatrix[11] - newMatrix[9];
		frustrumPlane[2].d = newMatrix[15] - newMatrix[13];
		// Bottom plane
		frustrumPlane[3].a = newMatrix[3] + newMatrix[1];
		frustrumPlane[3].b = newMatrix[7] + newMatrix[5];
		frustrumPlane[3].c = newMatrix[11] + newMatrix[9];
		frustrumPlane[3].d = newMatrix[15] + newMatrix[13];
		// Near plane
		frustrumPlane[4].a = newMatrix[2];
		frustrumPlane[4].b = newMatrix[6];
		frustrumPlane[4].c = newMatrix[10];
		frustrumPlane[4].d = newMatrix[14];
		// Far plane
		frustrumPlane[5].a = newMatrix[3] - newMatrix[2];
		frustrumPlane[5].b = newMatrix[7] - newMatrix[6];
		frustrumPlane[5].c = newMatrix[11] - newMatrix[10];
		frustrumPlane[5].d = newMatrix[15] - newMatrix[14];

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

	Matrix* EntityCamera::GetProjectionMatrix(){
		return &projectionMatrix;
	}
	Matrix* EntityCamera::GetViewMatrix(){
		return viewMatrix;
	}
}