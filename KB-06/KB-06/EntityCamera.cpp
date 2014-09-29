#include "EntityCamera.h"
#include "Vector3.h"
#include <sstream>

pengine::EntityCamera::EntityCamera()
{
	RenderMatrix* temp = new RenderMatrix();
	temp->CreateMatrix(0, 0, 0, 0, 0, 0, 1, 1, 1, temp->theMatrix);
	rotationMatrix = temp->theMatrix;
}

pengine::EntityCamera::~EntityCamera()
{

}

void pengine::EntityCamera::UpdateLogic(float deltaTime, std::map<Input, long>* actions)
{
	typedef std::map<Input, long>::iterator it_type;
	for (it_type iterator = (*actions).begin(); iterator != (*actions).end(); iterator++)
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
			case Input::KEY_NUMPAD2:
				this->AddPosition(0.0f, 0.0f, 0.5f);
				break;
			case Input::KEY_NUMPAD8:
				this->AddPosition(0.0f, 0.0f, -0.5f);
				break;
			case Input::KEY_NUMPAD6:
				this->AddPosition(-0.5f, 0.0f, 0.0f);
				break;
			case Input::KEY_NUMPAD4:
				this->AddPosition(0.5f, 0.0f, 0.0f);
				break;

			case Input::KEY_NUMPAD7:
				this->AddPosition(0.0f, 0.5f, 0.0f);
				break;

			case Input::KEY_NUMPAD1:
				this->AddPosition(0.0f, -0.5f, 0.0f);
				break;
			default:
				break;
			}
		}
	}
}

// Camera's worden niet getekend
void pengine::EntityCamera::Draw(pengine::Renderer* renderer)
{
	bool debug = true;
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


			renderer->SetMaterial(materialWrapper);
			xModel->GetTextures(textureWrapper, textureCount);
			renderer->SetTexture(textureWrapper);
			renderer->DrawSubset(xModel->GetMesh(), 0);
			xModel->GetTextures(textureWrapper, textureCount);

			LPDIRECT3DTEXTURE9* textureArray = textureWrapper->GetTexture();

			TextureWrapper* textureWrapperIndex = new TextureWrapper(&textureWrapper->GetTexture()[1]);
			MaterialWrapper* materialWrapperIndex = new MaterialWrapper(&materialWrapper->GetMaterial()[1]);

			renderer->SetTexture(textureWrapperIndex);//how do I get the second texture?
			renderer->SetMaterial(materialWrapperIndex);
			renderer->DrawSubset(xModel->GetMesh(), 1);
		}
		else
		{
			logger->Log(Logger::WARNING, "No xModel for entity!");
		}
	}
}

pengine::Vertex* pengine::EntityCamera::GetPosition()
{
	return &position;
}

pengine::CameraData pengine::EntityCamera::GetCameraData()
{
	CameraData d = { position.x, position.y, position.z, lookAtPosition.x, lookAtPosition.y, lookAtPosition.z, 0.0f, 1.0f, 0.0f };
	return d;
}

void pengine::EntityCamera::SetLookAtEntity(Entity* entity)
{
	Vertex* position = entity->GetPosition();
	SetLookAtPosition(position->x, position->y, position->z, 0.0f);
}

void pengine::EntityCamera::SetThirdPersonEntity(Entity* entity, float distance, float height)
{
	// TODO: rotation & calculate axis
	Vertex* entityPosition = entity->GetPosition();
	Vertex* cameraPosition = new Vertex();

	SetPosition(entityPosition->x, entityPosition->y, entityPosition->z);
	AddPosition(0.0f, height, distance);

	SetLookAtEntity(entity);
}

void pengine::EntityCamera::SetLookAtPosition(float x, float y, float z, float rollDegrees)
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

void pengine::EntityCamera::SetXModel(pengine::XModel* p_xmodel)
{
	xModel = p_xmodel;
}