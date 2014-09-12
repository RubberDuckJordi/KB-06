#include "Camera.h"

Scene::Camera::Camera()
{
	speed = 0.0f;
	xMovement = yMovement = zMovement = 0.0f;
	yawMovement = pitchMovement = rollMovement = 0.0f;
	moveForward = moveBackward = moveLeft = moveRight = moveUp = moveDown = speedUp = false;
}


Scene::Camera::~Camera()
{
}

void Scene::Camera::Update()
{
	Move();

	Resource::Normal tf = GetPosition();
	tf.x += xMovement;
	tf.y += yMovement;
	tf.z += zMovement;
	SetPosition(tf.x, tf.y, tf.z);
}

void Scene::Camera::Move()
{
	Resource::Normal rot = GetRotation();
	float yaw = rot.x;
	float pitch = rot.y;

	if (speedUp)
	{
		speed = SPEED * 3;
	}
	else
	{
		speed = SPEED;
	}

	if (moveBackward || moveLeft || moveDown)
	{
		speed = -speed;
	}

	if (moveForward || moveBackward)
	{
		xMovement = speed * sinf(yaw) * cosf(pitch);
		if (sinf(yaw) < 0)
		{
			yMovement = 2 * speed * sinf(yaw) * sinf(pitch);
		}
		else if (sinf(yaw) > 0)
		{
			yMovement = 2 * -speed * sinf(yaw) * sinf(pitch);
		}
		zMovement = speed * cosf(yaw);
	}
	else if (moveLeft || moveRight)
	{
		xMovement = speed * sinf(yaw - 80) * cosf(pitch);
		zMovement = speed * cosf(yaw - 80);
	}
	else if (moveUp || moveDown)
	{
		yMovement = speed;
	}
	else
	{
		xMovement = 0.0f;
		yMovement = 0.0f;
		zMovement = 0.0f;
	}
};

void Scene::Camera::MultiplyMatrices()
{
	finalMatrix = positionMatrix;

	if (yaw != 0 || pitch != 0 || roll != 0) {
		D3DXMatrixMultiply(&finalMatrix, &positionMatrix, &rotationMatrix);
	}

	if (scaleX != 1 || scaleY != 1 || scaleZ != 1) {
		D3DXMatrixMultiply(&finalMatrix, &finalMatrix, &scaleMatrix);
	}
};

void Scene::Camera::UseKeyboardInput()
{
	
};

void Scene::Camera::UseMouseInput()
{
	
};

void Scene::Camera::SetPosition(float x, float y, float z)
{
	this->x = -x;
	this->y = -y;
	this->z = -z;
	D3DXMatrixTranslation(&positionMatrix, this->x, this->y, this->z);
	MultiplyMatrices();
}

void Scene::Camera::SetRotation(float yaw, float pitch, float roll)
{
	this->yaw = -yaw;
	this->pitch = -pitch;
	this->roll = -roll;

	D3DXMATRIXA16 rot1;
	D3DXMatrixRotationYawPitchRoll(&rot1, yaw, 0.0f, 0.0f);
	D3DXMATRIXA16 rot2;
	D3DXMatrixRotationYawPitchRoll(&rot2, 0.0f, pitch, 0.0f);
	D3DXMatrixMultiply(&rotationMatrix, &rot1, &rot2);
}

void Scene::Camera::SetScale(float scaleX, float scaleY, float scaleZ)
{
	this->scaleX = -scaleX;
	this->scaleY = -scaleY;
	this->scaleZ = -scaleZ;
	D3DXMatrixScaling(&scaleMatrix, scaleX, scaleY, scaleZ);
	MultiplyMatrices();
}

Resource::Normal Scene::Camera::GetPosition()
{
	return{ -x, -y, -z };
}

Resource::Normal Scene::Camera::GetRotation()
{
	return{ -yaw, -pitch, -roll };
}

Resource::Normal Scene::Camera::GetScale()
{
	return{ -scaleX, -scaleY, -scaleZ };
}
