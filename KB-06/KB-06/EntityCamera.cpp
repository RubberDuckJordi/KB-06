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
	}

	EntityCamera::~EntityCamera()
	{

	}

	void EntityCamera::UpdateLogic(float deltaTime, std::map<Input, long>* actions)
	{
		for (auto iterator = (*actions).begin(); iterator != (*actions).end(); iterator++)
		{
			float speed = static_cast<float>(iterator->second);

			if (useInput)
			{
				switch (iterator->first)
				{
				case Input::KEY_S:
					this->AddPosition(0.0f, 0.0f, 0.5f);
					//SetLookAtPosition(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z - 1.0f, 0.0f);
					break;
				case Input::KEY_W:
					this->AddPosition(0.0f, 0.0f, -0.5f);
					//SetLookAtPosition(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z + 1.0f, 0.0f);
					break;
				case Input::KEY_D:
					this->AddPosition(-0.5f, 0.0f, 0.0f);
					//SetLookAtPosition(lookAtPosition.x - 1.0f, lookAtPosition.y, lookAtPosition.z, 0.0f);
					break;
				case Input::KEY_A:
					this->AddPosition(0.5f, 0.0f, 0.0f);
					//SetLookAtPosition(lookAtPosition.x + 1.0f, lookAtPosition.y, lookAtPosition.z, 0.0f);
					break;

				case Input::KEY_SPACE:
					this->AddPosition(0.0f, 0.5f, 0.0f);
					//SetLookAtPosition(lookAtPosition.x, lookAtPosition.y + 1.0f, lookAtPosition.z, 0.0f);
					break;

				case Input::KEY_LSHIFT:
					this->AddPosition(0.0f, -0.5f, 0.0f);
					//SetLookAtPosition(lookAtPosition.x, lookAtPosition.y - 1.0f, lookAtPosition.z, 0.0f);
					break;

				case Input::KEY_DOWN:
					//this->AddPosition(0.0f, 0.0f, 0.5f);
					SetLookAtPosition(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z + 0.1f, 0.0f);
					break;
				case Input::KEY_UP:
					//this->AddPosition(0.0f, 0.0f, -0.5f);
					SetLookAtPosition(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z - 0.1f, 0.0f);
					break;
				case Input::KEY_LEFT:
					//this->AddPosition(-0.5f, 0.0f, 0.0f);
					SetLookAtPosition(lookAtPosition.x + 0.1f, lookAtPosition.y, lookAtPosition.z, 0.0f);
					break;
				case Input::KEY_RIGHT:
					//this->AddPosition(0.5f, 0.0f, 0.0f);
					SetLookAtPosition(lookAtPosition.x - 0.1f, lookAtPosition.y, lookAtPosition.z, 0.0f);
					break;

				case Input::KEY_BACK:
					//this->AddPosition(0.5f, 0.0f, 0.0f);
					SetLookAtPosition(lookAtPosition.x, lookAtPosition.y + 0.1f, lookAtPosition.z, 0.0f);
					break;

				case Input::KEY_RETURN:
					//this->AddPosition(0.5f, 0.0f, 0.0f);
					SetLookAtPosition(lookAtPosition.x, lookAtPosition.y - 0.1f, lookAtPosition.z, 0.0f);
					break;
				default:
					break;
				}
			}
			else
			{
				switch (iterator->first)
				{
				case Input::KEY_G:
					this->AddPosition(0.0f, 0.0f, 0.5f);
					this->SetLookAtPosition(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z + 0.5f, 0.0f);
					break;
				case Input::KEY_T:
					this->AddPosition(0.0f, 0.0f, -0.5f);
					this->SetLookAtPosition(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z - 0.5f, 0.0f);
					break;
				case Input::KEY_H:
					this->AddPosition(-0.5f, 0.0f, 0.0f);
					this->SetLookAtPosition(lookAtPosition.x - 0.5f, lookAtPosition.y, lookAtPosition.z, 0.0f);
					break;
				case Input::KEY_F:
					this->AddPosition(0.5f, 0.0f, 0.0f);
					this->SetLookAtPosition(lookAtPosition.x + 0.5f, lookAtPosition.y, lookAtPosition.z, 0.0f);
					break;

				case Input::KEY_Y:
					this->AddPosition(0.0f, 0.5f, 0.0f);
					this->SetLookAtPosition(lookAtPosition.x, lookAtPosition.y + 0.5f, lookAtPosition.z, 0.0f);
					break;

				case Input::KEY_R:
					this->AddPosition(0.0f, -0.5f, 0.0f);
					this->SetLookAtPosition(lookAtPosition.x, lookAtPosition.y - 0.5f, lookAtPosition.z, 0.0f);
					break;
				default:
					break;
				}
			}
		}
	}

	// Camera's worden niet getekend
	void EntityCamera::Draw(Renderer* renderer)
	{
		bool debug = false;
		if (debug)
		{
			if (xModel != NULL)
			{
				RenderMatrix* lookAt = new RenderMatrix();//should be global
				lookAt->CreateMatrix(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, lookAt->theMatrix);//should only be called when needed (when any value has updated)
				renderer->SetActiveMatrix(lookAt->theMatrix);//should be called every frame
				//renderer->Draw(myMesh);

				RenderMatrix* cameraM = new RenderMatrix();//should be global
				cameraM->CreateMatrix(position.x, position.y, position.z, 0, 0, 0, 0.1f, 0.1f, 0.1f, cameraM->theMatrix);//should only be called when needed (when any value has updated)
				cameraM->MultiplyMatrices(rotationMatrix, cameraM->theMatrix, cameraM->theMatrix);

				renderer->SetActiveMatrix(cameraM->theMatrix);//should be called every frame

				MaterialWrapper* materialWrapper;
				int materialCount;
				xModel->GetMaterials(materialWrapper, materialCount);

				TextureWrapper* textureWrapper;
				int textureCount;


				renderer->SetMaterialWrapper(materialWrapper);
				xModel->GetTextures(textureWrapper, textureCount);
				renderer->SetTexture(textureWrapper);
				renderer->DrawSubset(xModel->GetMesh(), 0);
				xModel->GetTextures(textureWrapper, textureCount);

				LPDIRECT3DTEXTURE9* textureArray = textureWrapper->GetTexture();

				TextureWrapper* textureWrapperIndex = new TextureWrapper(&textureWrapper->GetTexture()[1]);
				MaterialWrapper* materialWrapperIndex = new MaterialWrapper(&materialWrapper->GetMaterial()[1]);

				renderer->SetTexture(textureWrapperIndex);//how do I get the second texture?
				renderer->SetMaterialWrapper(materialWrapperIndex);
				renderer->DrawSubset(xModel->GetMesh(), 1);
			}
			else
			{
				logger->Log(Logger::WARNING, "No xModel for entity!");
			}
		}
	}

	Vertex* EntityCamera::GetPosition()
	{
		return &position;
	}

	CameraData EntityCamera::GetCameraData()
	{
		CameraData d = { position.x, position.y, position.z, lookAtPosition.x, lookAtPosition.y, lookAtPosition.z, 0.0f, 1.0f, 0.0f };
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

		//RenderMatrix::PrintMatrix(rotationMatrix);

		lookAtPosition = { x, y, z };
	}

	void EntityCamera::SetXModel(XModel* p_xmodel)
	{
		xModel = p_xmodel;
	}
}