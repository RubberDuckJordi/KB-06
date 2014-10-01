#include "Entity.h"
#include "PengineDefinitions.h"

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

void pengine::Entity::SetMass(float p_mass)
{
	mass = p_mass;
}

float pengine::Entity::GetMass()
{
	return mass;
}

void pengine::Entity::SetFriction(float p_friction)
{
	friction = p_friction;
}

void pengine::Entity::AddFriction(float p_friction)
{
	friction += p_friction;
}

float pengine::Entity::GetFriction()
{
	return friction;
}

Vector3* pengine::Entity::GetMovementVector()
{
	return &movementVector;
}

void pengine::Entity::SetMovementVector(Vector3* p_movementDirection)
{
	movementVector = *p_movementDirection;
}

void pengine::Entity::AddForce(Vector3* p_direction)
{
	// mass
	movementVector = *p_direction;
}


void pengine::Entity::UpdateLogic(float deltaTime, std::map<pengine::Input, long>* actions)
{

	float xDelta = (deltaTime * sin((M_PI / 180) *  movementVector.x));
	float zDelta = (deltaTime *  cos((M_PI / 180) * (movementVector.y))) * (cos((M_PI / 180) * movementVector.x));
	//TODO Y axis

	AddPosition(xDelta, 0.0f, zDelta);
}
