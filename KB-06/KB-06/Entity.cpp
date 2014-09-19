#include "Entity.h"

Scene::Entity::Entity()
{
	logger = Logger::LoggerPool::GetInstance().GetLogger();
	myCachedMatrix = new RenderMatrix();
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

/*Resource::Vertex* Scene::Entity::GetPosition()
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
}*/

/*void Scene::Entity::Draw(Renderer::Renderer* renderer)
{
	if (mesh != NULL)
	{
		RenderMatrix* myCache = new RenderMatrix();//should be global
		renderer->CreateMatrix(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z, myCache);//should only be called when needed (when any value has updated)
		//renderer->SetWorldMatrix(&position, &rotation, &scale, p_position, p_rotation);
		renderer->SetActiveMatrix(myCache);//should be called every frame
		renderer->Draw(mesh);
	}
	else
	{
		logger->Log(Logger::Logger::WARNING, "No mesh for entity!");
	}
}*/

/*void Scene::Entity::UpdateLogic(std::map<Input::Input, long>* actions)
{
	typedef std::map<Input::Input, long>::iterator it_type;
	for (it_type iterator = (*actions).begin(); iterator != (*actions).end(); iterator++) {
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
}*/