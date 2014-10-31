#include "Entity.h"
#include "PengineDefinitions.h"

namespace pengine
{
	Entity::Entity()
	{
		logger = LoggerPool::GetInstance().GetLogger();
		myCachedMatrix = new Matrix();

		movementVector.x = 0;
		movementVector.y = 0;
		movementVector.z = 0;
		mass = 1.0f;
		friction = 0.5f;
		defaultRadius = 1.0f;
	}

	Entity::~Entity()
	{
		delete myCachedMatrix;
	}

	void Entity::SetPosition(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
		myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix);
	}

	void Entity::SetRotation(float yaw, float pitch, float roll)
	{
		rotation.x = yaw;
		rotation.y = pitch;
		rotation.z = roll;
		myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix);
	}

	void Entity::SetScale(float scaleX, float scaleY, float scaleZ)
	{
		scale.x = scaleX;
		scale.y = scaleY;
		scale.z = scaleZ;
		myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix);
	}

	void Entity::SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ)
	{
		SetScale(scaleX, scaleY, scaleZ);
		SetPosition(x, y, z);
		SetRotation(yaw, pitch, roll);
	}

	Vector3* Entity::GetPosition()
	{
		return &position;
	}

	Vector3* Entity::GetRotation()
	{
		return &rotation;
	}

	Vector3* Entity::GetScale()
	{
		return &scale;
	}

	void Entity::AddPosition(float x, float y, float z)
	{
		position.x += x;
		position.y += y;
		position.z += z;
		myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix);
	}

	void Entity::AddRotation(float yaw, float pitch, float roll)
	{
		rotation.x += yaw;
		rotation.y += pitch;
		rotation.z += roll;
		myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix);
	}

	void Entity::AddAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ)
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
		myCachedMatrix->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCachedMatrix);
	}

	void Entity::SetMass(float p_mass)
	{
		mass = p_mass;
	}

	float Entity::GetMass()
	{
		return mass;
	}

	void Entity::SetFriction(float p_friction)
	{
		friction = p_friction;
	}

	void Entity::AddFriction(float p_friction)
	{
		friction += p_friction;
	}

	float Entity::GetFriction()
	{
		return friction;
	}

	Vector3* Entity::GetMovementVector()
	{
		return &movementVector;
	}

	void Entity::SetMovementVector(Vector3* p_movementDirection)
	{
		movementVector = *p_movementDirection;
	}

	void Entity::AddForce(Vector3* p_direction)
	{
		// Inertia calculation
		// Acceleration = force / mass
		p_direction->x = p_direction->x / mass;
		p_direction->y = p_direction->y / mass;
		p_direction->z = p_direction->z / mass;

		movementVector = movementVector + *p_direction;
	}

	void Entity::AddForce(Vector3* p_direction, float mass)
	{
		Vector3 modifiedVector;

		modifiedVector.x = p_direction->x * mass;
		modifiedVector.y = p_direction->y * mass;
		modifiedVector.z = p_direction->z * mass;

		AddForce(&modifiedVector);
	}

	void Entity::UpdateLogic(float deltaTime, std::map<pengine::Input, long>* actions)
	{
		// Ground friction
		ApplyFriction(friction);
		// Air friction
		ApplyFriction(friction * 0.05f * movementVector.GetMagnitude()); 

		float xDelta = (deltaTime * movementVector.x);
		float zDelta = (deltaTime * movementVector.z);
		float yDelta = (deltaTime * movementVector.y);

		AddPosition(xDelta, yDelta, zDelta);

		previousRotation.x = rotation.x;
		previousRotation.y = rotation.y;
		previousRotation.z = rotation.z;

		previousPosition.x = position.x;
		previousPosition.y = position.y;
		previousPosition.z = position.z;
	}

	void Entity::RevertPreviousMovementStep()
	{
		rotation = previousRotation;
		position = previousPosition;
	}

	void Entity::AddRelativeForce(Vector3* p_vector)
	{
		Vector3 relativeVector;

		// Z Axis
		relativeVector.x += -p_vector->z * sin((M_PI / 180)*+rotation.x);
		relativeVector.z += -p_vector->z * cos((M_PI / 180)*rotation.x);

		// X Axis
		relativeVector.z += -p_vector->x * sin((M_PI / 180)*-rotation.x);
		relativeVector.x += -p_vector->x * cos((M_PI / 180)*rotation.x);

		//TODO: Y AXIS, PITCH, ROLL

		AddForce(&relativeVector);
	}

	// This function could contain bugs and might require fixes.
	// It's currently being used to determine if the entity is moving forward or backwards
	Vector3* Entity::GetRelativeForce()
	{
		Vector3* relativeVector = new Vector3();

		// Z Axis
		relativeVector->x += -movementVector.z * sin((M_PI / 180)*-rotation.x);
		relativeVector->z += -movementVector.z * cos((M_PI / 180)*rotation.x);

		// X Axis
		relativeVector->z += -movementVector.x * sin((M_PI / 180)*+rotation.x);
		relativeVector->x += -movementVector.x * cos((M_PI / 180)*rotation.x);

		//TODO: Y AXIS, PITCH, ROLL

		return relativeVector;
	}

	void Entity::ApplyFriction(float p_friction)
	{
		Vector3 inverted;

		inverted.x = movementVector.x * (-p_friction);
		inverted.y = movementVector.y * (-p_friction);
		inverted.z = movementVector.z * (-p_friction);

		AddForce(&inverted);
	}

	void Entity::SetRadius(float radius)
	{
		this->defaultRadius = radius;
	}

	float Entity::GetRadius()
	{
		return defaultRadius;
	}
}
