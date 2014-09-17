#include "EntityCamera.h"

Scene::EntityCamera::EntityCamera()
{

}


Scene::EntityCamera::~EntityCamera()
{

}

void Scene::EntityCamera::Update(std::map<Input::Input, long>* actions)
{
	typedef std::map<Input::Input, long>::iterator it_type;
	for (it_type iterator = (*actions).begin(); iterator != (*actions).end(); iterator++) {
		logger->Log(Logger::Logger::INFO, "changing camera view");
		float speed = static_cast<float>(iterator->second);
		if (iterator->first == Input::MOUSE_X)
		{
			if (speed < 0)
			{
				this->AddRotation(0.0f, 1.0f, 0.0f);
			}
			else
			{
				this->AddRotation(0.0f, -1.0f, 0.0f);
			}
		}
		if (iterator->first == Input::MOUSE_Y)
		{
			if (speed > 0)
			{
				this->AddRotation(1.0f, 0.0f, 0.0f);
			}
			else
			{
				this->AddRotation(-1.0f, 0.0f, 0.0f);
			}
		}
	}
	if ((*actions).size() > 0){
		logger->Log(Logger::Logger::INFO, "Camera");
		logger->Log(Logger::Logger::INFO, std::to_string(rotation.x));
		logger->Log(Logger::Logger::INFO, std::to_string(rotation.y));
		logger->Log(Logger::Logger::INFO, std::to_string(rotation.z));
	}
}

void Scene::EntityCamera::Move()
{
	
};

// Camera's worden niet getekend
void Scene::EntityCamera::Draw(Renderer::Renderer* renderer, Resource::Vertex* position, Resource::Vertex* rotation)
{

}