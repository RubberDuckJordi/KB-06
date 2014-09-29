#include "Entity.h"

pengine::Entity::Entity()
{
	logger = LoggerPool::GetInstance().GetLogger();
	myCachedMatrix = new RenderMatrix();
}

pengine::Entity::~Entity()
{
	LoggerPool::GetInstance().ReturnLogger(logger);
	delete myCachedMatrix;
}

void pengine::Entity::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}

void pengine::Entity::SetRotation(float yaw, float pitch, float roll)
{
	rotation.x = yaw;
	rotation.y = pitch;
	rotation.z = roll;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}

void pengine::Entity::SetScale(float scaleX, float scaleY, float scaleZ)
{
	scale.x = scaleX;
	scale.y = scaleY;
	scale.z = scaleZ;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}

void pengine::Entity::SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ)
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

pengine::Vertex* pengine::Entity::GetPosition()
{
	return &position;
}

pengine::Vertex* pengine::Entity::GetRotation()
{
	return &rotation;
}

pengine::Vertex* pengine::Entity::GetScale()
{
	return &scale;
}

void pengine::Entity::AddPosition(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}

void pengine::Entity::AddRotation(float yaw, float pitch, float roll)
{
	rotation.x += yaw;
	rotation.y += pitch;
	rotation.z += roll;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}

void pengine::Entity::AddScale(float scaleX, float scaleY, float scaleZ)
{
	scale.x += scaleX;
	scale.y += scaleY;
	scale.z += scaleZ;
	myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix->theMatrix);
}

void pengine::Entity::AddAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ)
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

void pengine::Entity::SetVelocity(float p_velocity)
{
	velocity = p_velocity;
}

void pengine::Entity::SetForce(float p_force)
{
	force = p_force;
}

void pengine::Entity::SetMass(float p_mass)
{
	mass = p_mass;
}

float pengine::Entity::GetVelocity()
{
	return velocity;
}

float pengine::Entity::GetForce()
{
	return force;
}

float pengine::Entity::GetMass()
{
	return mass;
}
