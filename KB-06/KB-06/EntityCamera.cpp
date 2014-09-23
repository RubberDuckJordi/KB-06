#include "EntityCamera.h"
#include "Vector3.h"

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
	if (useInput)
	{
		typedef std::map<Input::Input, long>::iterator it_type;
		for (it_type iterator = (*actions).begin(); iterator != (*actions).end(); iterator++) {
			//logger->Log(Logger::Logger::INFO, "changing camera view");
			float speed = static_cast<float>(iterator->second);

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
		/*if ((*actions).size() > 0){
		logger->Log(Logger::Logger::INFO, "Camera");
		logger->Log(Logger::Logger::INFO, std::to_string(rotation.x));
		logger->Log(Logger::Logger::INFO, std::to_string(rotation.y));
		logger->Log(Logger::Logger::INFO, std::to_string(rotation.z));
		}*/
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
			//renderer->SetWorldMatrix(&position, &rotation, &scale, p_position, p_rotation);
			renderer->SetActiveMatrix(lookAt->theMatrix);//should be called every frame
			renderer->Draw(myMesh);

			RenderMatrix* cameraM = new RenderMatrix();//should be global
			cameraM->CreateMatrix(position.x, position.y, position.z, 0, 0, 0, 0.75f, 0.75f, 0.75f, cameraM->theMatrix);//should only be called when needed (when any value has updated)
			cameraM->MultiplyMatrices(rotationMatrix, cameraM->theMatrix, cameraM->theMatrix);

			//RenderMatrix* rot1 = new RenderMatrix();

			/*//Custom multiplying of Matrices
			D3DXMATRIXA16 rot1;
			D3DXMatrixRotationYawPitchRoll(&rot1, RADIANS(rotation.x), 0.0f, 0.0f);
			//rot1->CreateMatrix(0, 0, 0, rotation.x, 0, 0, 1, 1, 1, rot1->theMatrix);
			D3DXMATRIXA16 rot2;
			D3DXMatrixRotationYawPitchRoll(&rot2, 0.0f, RADIANS(rotation.y), 0.0f);
			D3DXMATRIXA16 rotationMatrix;
			D3DXMatrixMultiply(&rotationMatrix, &rot1, &rot2);
			cameraM->MultiplyMatrices((PEngineMatrix*)&rotationMatrix, cameraM->theMatrix, cameraM->theMatrix);

			/*D3DXVECTOR3 vEyePt(position.x, position.y, position.z);
			D3DXVECTOR3 vLookatPt(lookAtPosition.x, lookAtPosition.y, lookAtPosition.z);
			D3DXVECTOR3 vUpVec(0, 1, 0);
			D3DXMatrixLookAtLH((D3DXMATRIX*) cameraM->theMatrix, &vEyePt, &vLookatPt, &vUpVec);*/

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
	/*float deltaX = position.x - x;
	float deltaY = position.y - y;
	float deltaZ = position.z - z;

	float result = DEGREES(atan2f(deltaX, deltaZ));
	float result2 = -DEGREES(atan2f(deltaY, deltaZ));

	logger->Log(3, "result is " + std::to_string(result) + ", deltaX" + std::to_string(deltaX) + ", deltaZ" + std::to_string(deltaZ));
	logger->Log(3, "result2 is " + std::to_string(result2) + ", deltaZ" + std::to_string(deltaZ) + ", deltaY" + std::to_string(deltaY));



	rotation.x = result + 90;
	rotation.y = result2;*/

	//Entity::SetRotation(result, result2, rollDegrees);

	/*Vector3 vz = lookat - pos;
	vz.normalize();
	Vector3 vx = Vector3::cross(Vector3(0, 1, 0), vz);
	vx.normalize();
	Vector3 vy = Vector3::cross(vz, vx);

	Matrix4 rotation(vx.x, vy.x, vz.x, 0,
	vx.y, vy.y, vz.y, 0,
	vx.z, vy.z, vz.z, 0,
	0, 0, 0, 1);*/


	Vector3 lookat = { lookAtPosition.x, lookAtPosition.y, lookAtPosition.z };
	Vector3 pos = { position.x, position.y, position.z };
	Vector3 cameraUpVector = { 0, 1, 0 };

	Vector3 zaxis = (lookat - pos);
	zaxis.normalize();
	Vector3 xaxis = cameraUpVector.cross(zaxis);
	xaxis.normalize();
	Vector3 yaxis = zaxis.cross(xaxis);

	PEngineMatrix pm = {
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		0, 0, 0, 1

	};
	rotationMatrix = &pm;

	/*zaxis = normal(cameraTarget - cameraPosition)
		xaxis = normal(cross(cameraUpVector, zaxis))
		yaxis = cross(zaxis, xaxis)

		xaxis.x           yaxis.x           zaxis.x          0
		xaxis.y           yaxis.y           zaxis.y          0
		xaxis.z           yaxis.z           zaxis.z          0
		- dot(xaxis, cameraPosition) - dot(yaxis, cameraPosition) - dot(zaxis, cameraPosition)  1*/

	/*Vector3 vz = lookat - pos;
	vz.Normalize();
	Vector3 vx = Vector3(0, 1, 0).Cross(vz);
	vx.Normalize();
	Vector3 vy = Vector3::cross(vz, vx);

	Matrix4 rotation(vx.x, vy.x, vz.x, 0,
	vx.y, vy.y, vz.y, 0,
	vx.z, vy.z, vz.z, 0,
	0, 0, 0, 1);*/

	lookAtPosition = { x, y, z };
}