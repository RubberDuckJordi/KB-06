#include "EntityCamera.h"

Scene::EntityCamera::EntityCamera()
{

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

		switch (iterator->first)
		{
		case Input::MOUSE_X:
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
			break;
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


// Camera's worden niet getekend
void Scene::EntityCamera::Draw(Renderer::Renderer* renderer)
{
	bool debug = false;
	if (debug)
	{
		//teken een wireframe ofzo
	}
}

Resource::Vertex* Scene::EntityCamera::GetPosition()
{
	return &position;
}

CameraData Scene::EntityCamera::GetCameraData()
{
	CameraData d = { position.x, position.y, position.z, position.x, position.y, position.z-0.5f, 0.0f, 0.5f, 0.0f };
	return d;
}