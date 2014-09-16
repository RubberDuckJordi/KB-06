#include "Entity.h"

#include "Entity.h"

void Scene::Entity::SetPosition(float x, float y, float z)
{

}

void Scene::Entity::SetRotation(float yaw, float pitch, float roll)
{

}

void Scene::Entity::SetScale(float scaleX, float scaleY, float scaleZ)
{

}

void Scene::Entity::AddPosition(float x, float y, float z)
{

}

void Scene::Entity::AddRotation(float yaw, float pitch, float roll)
{

}

void Scene::Entity::AddScale(float scaleX, float scaleY, float scaleZ)
{

}

Resource::Vertex Scene::Entity::GetPosition()
{

}

Resource::Vertex Scene::Entity::GetRotation()
{

}

Resource::Vertex Scene::Entity::GetScale()
{

}

void Scene::Entity::Draw(Renderer::Renderer* renderer)
{
	renderer->SetWorldMatrix(position, rotation, scale);
	renderer->Draw(mesh);
}

void Scene::Entity::SetMesh(Resource::Mesh* p_mesh)
{
	mesh = p_mesh;
}