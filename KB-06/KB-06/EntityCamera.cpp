#include "EntityCamera.h"

Scene::EntityCamera::EntityCamera()
{

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
			cameraM->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, 0.75f, 0.75f, 0.75f, cameraM->theMatrix);//should only be called when needed (when any value has updated)
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
	float deltaX = position.x - x;
	float deltaY = position.y - y;
	float deltaZ = position.z - z;
	
	float result = DEGREES(atan2f(deltaX, deltaZ));
	float result2 = -DEGREES(atan2f(deltaY, deltaX));

	logger->Log(3, "result is " + std::to_string(result) + ", deltaX" + std::to_string(deltaX) + ", deltaZ" + std::to_string(deltaZ));
	logger->Log(3, "result2 is " + std::to_string(result2) + ", deltaZ" + std::to_string(deltaZ) + ", deltaY" + std::to_string(deltaY));

	rotation.x = result;
	//rotation.y = result2;
	//Entity::SetRotation(result, result2, rollDegrees);
	lookAtPosition = { x, y, z };
}