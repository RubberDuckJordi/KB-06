#include "Entity.h"

Scene::Entity::Entity()
{

}

Scene::Entity::~Entity()
{

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
}

void Scene::Entity::AddScale(float scaleX, float scaleY, float scaleZ)
{
	scale.x += scaleX;
	scale.y += scaleY;
	scale.z += scaleZ;
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
		renderer->SetWorldMatrix(&position, &rotation, &scale, p_position, p_rotation);
		renderer->Draw(mesh);
	}
}

void Scene::Entity::SetMesh(Resource::Mesh* p_mesh)
{
	mesh = p_mesh;
}