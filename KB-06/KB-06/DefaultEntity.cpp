#include "DefaultEntity.h"
#include "Logger.h"
#include "LoggerPool.h"
#include <iostream>

namespace pengine
{
	DefaultEntity::DefaultEntity()
	{
	}

	DefaultEntity::~DefaultEntity()
	{
	}

	void DefaultEntity::UpdateLogic(float deltaTime, std::map<Input, long>* actions)
	{
		AddRotation(rotationMod, rotationMod, rotationMod);
		Entity::UpdateLogic(deltaTime, actions);
	}

	void DefaultEntity::Draw(Renderer* renderer)
	{
		
	}
}