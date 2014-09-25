#include "Entity.h"

Scene::Entity::Entity()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
	myCachedMatrix = new Renderer::RenderMatrix();
}

Scene::Entity::~Entity()
{
	Logger::LoggerPool::GetInstance().ReturnLogger(logger);
	delete myCachedMatrix;
}

void Scene::Entity::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}

void Scene::Entity::SetRotation(float yaw, float pitch, float roll)
{
	rotation.x = yaw;
	rotation.y = pitch;
	rotation.z = roll;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}

void Scene::Entity::SetScale(float scaleX, float scaleY, float scaleZ)
{
	scale.x = scaleX;
	scale.y = scaleY;
	scale.z = scaleZ;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}

void Scene::Entity::SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotation.x = yaw;
	rotation.y = pitch;
	rotation.z = roll;
	scale.x = scaleX;
	scale.y = scaleY;
	scale.z = scaleZ;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);//should only be called when needed (when any value has updated)
}

void Scene::Entity::AddPosition(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}

void Scene::Entity::AddRotation(float yaw, float pitch, float roll)
{
	rotation.x += yaw;
	rotation.y += pitch;
	rotation.z += roll;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}

void Scene::Entity::AddScale(float scaleX, float scaleY, float scaleZ)
{
	scale.x += scaleX;
	scale.y += scaleY;
	scale.z += scaleZ;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}

void Scene::Entity::AddAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ)
{
	position.x += x;
	position.y += y;
	position.z += z;
	rotation.x += yaw;
	rotation.y += pitch;
	rotation.z += roll;
	scale.x += scaleX;
	scale.y += scaleY;
	scale.z += scaleZ;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}