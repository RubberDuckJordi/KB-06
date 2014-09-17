#include "Entity.h"

Scene::Entity::Entity()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
}

Scene::Entity::~Entity()
{
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
}

void Scene::Entity::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Scene::Entity::SetRotation(float yaw, float pitch, float roll)
{
	rotation.x = yaw;
	rotation.y = pitch;
	rotation.z = roll;
}

void Scene::Entity::SetScale(float scaleX, float scaleY, float scaleZ)
{
	scale.x = scaleX;
	scale.y = scaleY;
	scale.z = scaleZ;
}

void Scene::Entity::AddPosition(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

void Scene::Entity::AddRotation(float yaw, float pitch, float roll)
{
	rotation.x += yaw;
	rotation.y += pitch;
	rotation.z += roll;
	FixDegrees(&rotation);
}

void Scene::Entity::AddScale(float scaleX, float scaleY, float scaleZ)
{
	scale.x += scaleX;
	scale.y += scaleY;
	scale.z += scaleZ;
}

void Scene::Entity::FixDegrees(Resource::Vertex* vertex)
{
	if (vertex->x > 360)
	{
		vertex->x -= 360;
	}
	if (vertex->x < 0)
	{
		vertex->x + 360;
	}
	if (vertex->y > 360)
	{
		vertex->y -= 360;
	}
	if (vertex->y < 0)
	{
		vertex->y + 360;
	}
	if (vertex->z > 360)
	{
		vertex->z -= 360;
	}
	if (vertex->z < 0)
	{
		vertex->z + 360;
	}
}

Resource::Vertex* Scene::Entity::GetPosition()
{
	return &position;
}

Resource::Vertex* Scene::Entity::GetRotation()
{
	return &rotation;
}

Resource::Vertex* Scene::Entity::GetScale()
{
	return &scale;
}

void Scene::Entity::Draw(Renderer::Renderer* renderer, Resource::Vertex* p_position, Resource::Vertex* p_rotation)
{
	if (mesh != NULL)
	{
		//renderer->SetWorldMatrix(&position, &rotation, &scale, p_position, p_rotation);
		renderer->Draw(mesh);
	}
	else
	{
		logger->Log(Logger::Logger::WARNING, "No mesh for entity!");
	}
}

void Scene::Entity::SetMesh(Resource::Mesh* p_mesh)
{
	mesh = p_mesh;
}