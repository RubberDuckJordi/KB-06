#include "EntityCamera.h"
#include "Vector3.h"
#include <sstream>

Scene::EntityCamera::EntityCamera()
{
	RenderMatrix* temp = new RenderMatrix();
	temp->CreateMatrix(0, 0, 0, 0, 0, 0, 1, 1, 1, temp->theMatrix);
	rotationMatrix = temp->theMatrix;
}


Scene::EntityCamera::~EntityCamera()
{

}

void Scene::EntityCamera::UpdateLogic(std::map<Input::Input, long>* actions)
{

	typedef std::map<Input::Input, long>::iterator it_type;
	for (it_type iterator = (*actions).begin(); iterator != (*actions).end(); iterator++) {
		//logger->Log(Logger::Logger::INFO, "changing camera view");
		float speed = static_cast<float>(iterator->second);

		if (useInput)
		{
			switch (iterator->first)
			{
				/*case Input::MOUSE_X:
				if (speed < 0)
				{
				this->AddRotation(0.0f, 1.0f, 0.0f);
				}
				else
				{
				this->AddRotation(0.0f, -1.0f, 0.0f);
				}
				break;
				case Input::MOUSE_Y:
				if (speed > 0)
				{
				this->AddRotation(1.0f, 0.0f, 0.0f);
				}
				else
				{
				this->AddRotation(-1.0f, 0.0f, 0.0f);
				}
				break;*/
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
void Scene::EntityCamera::Draw(Renderer::Renderer* renderer)
{
	bool debug = true;
	if (debug)
	{
		//teken een wireframe ofzo
		if (myMesh != NULL)
		{
			RenderMatrix* lookAt = new RenderMatrix();//should be global
			lookAt->CreateMatrix(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z, 0.0f, 0.0f, 0.0f, 0.75f, 0.75f, 0.75f, lookAt->theMatrix);//should only be called when needed (when any value has updated)

			renderer->SetActiveMatrix(lookAt->theMatrix);//should be called every frame
			renderer->Draw(myMesh);

			RenderMatrix* cameraM = new RenderMatrix();//should be global
			cameraM->CreateMatrix(position.x, position.y, position.z, 0, 0, 0, 0.75f, 0.75f, 0.75f, cameraM->theMatrix);//should only be called when needed (when any value has updated)
			cameraM->MultiplyMatrices(rotationMatrix, cameraM->theMatrix, cameraM->theMatrix);

			renderer->SetActiveMatrix(cameraM->theMatrix);//should be called every frame
			renderer->Draw(myMesh2);
		}
		else
		{
			logger->Log(Logger::Logger::WARNING, "No mesh for entity!");
		}
	}
}

Resource::Vertex* Scene::EntityCamera::GetPosition()
{
	return &position;
}

CameraData Scene::EntityCamera::GetCameraData()
{
	CameraData d = { position.x, position.y, position.z, lookAtPosition.x, lookAtPosition.y, lookAtPosition.z, 0.0f, 1.0f, 0.0f };
	return d;
}

void Scene::EntityCamera::SetLookAtPosition(float x, float y, float z, float rollDegrees)
{
	Vector3 lookat = { lookAtPosition.x, lookAtPosition.y, lookAtPosition.z };
	Vector3 pos = { position.x, position.y, position.z };
	Vector3 objectUpVector = { 0.0f, 1.0f, 0.0f };

	Vector3 zaxis = Vector3::normalize(lookat - pos);
	Vector3 xaxis = Vector3::normalize(Vector3::cross(objectUpVector, zaxis));
	Vector3 yaxis = Vector3::cross(zaxis, xaxis);

	PEngineMatrix pm = {
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		0, 0, 0, 1
	};
	rotationMatrix->_11 = pm._11;
	rotationMatrix->_12 = pm._12;
	rotationMatrix->_13 = pm._13;
	rotationMatrix->_14 = pm._14;

	rotationMatrix->_21 = pm._21;
	rotationMatrix->_22 = pm._22;
	rotationMatrix->_23 = pm._23;
	rotationMatrix->_24 = pm._24;

	rotationMatrix->_31 = pm._31;
	rotationMatrix->_32 = pm._32;
	rotationMatrix->_33 = pm._33;
	rotationMatrix->_34 = pm._34;

	rotationMatrix->_41 = pm._41;
	rotationMatrix->_42 = pm._42;
	rotationMatrix->_43 = pm._43;
	rotationMatrix->_44 = pm._44;

	/*std::ostringstream oss;
	oss << "\nDirectX:\n"
	<< "[" << rotationMatrix->_11 << ",\t" << rotationMatrix->_12 << ",\t" << rotationMatrix->_13 << ",\t" << rotationMatrix->_14 << "]\n"
	<< "[" << rotationMatrix->_21 << ",\t" << rotationMatrix->_22 << ",\t" << rotationMatrix->_23 << ",\t" << rotationMatrix->_24 << "]\n"
	<< "[" << rotationMatrix->_31 << ",\t" << rotationMatrix->_32 << ",\t" << rotationMatrix->_33 << ",\t" << rotationMatrix->_34 << "]\n"
	<< "[" << rotationMatrix->_41 << ",\t" << rotationMatrix->_42 << ",\t" << rotationMatrix->_43 << ",\t" << rotationMatrix->_44 << "]\n"
	<< "Die van mij:\n"
	<< "[" << pm._11 << ",\t" << pm._12 << ",\t" << pm._13 << ",\t" << pm._14 << "]\n"
	<< "[" << pm._21 << ",\t" << pm._22 << ",\t" << pm._23 << ",\t" << pm._24 << "]\n"
	<< "[" << pm._31 << ",\t" << pm._32 << ",\t" << pm._33 << ",\t" << pm._34 << "]\n"
	<< "[" << pm._41 << ",\t" << pm._42 << ",\t" << pm._43 << ",\t" << pm._44 << "]\n"
	;
	logger->Log(1, oss.str());*/

	lookAtPosition = { x, y, z };
}