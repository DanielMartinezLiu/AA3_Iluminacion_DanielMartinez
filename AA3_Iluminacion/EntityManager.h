#pragma once
#include <vector>
#include "GameObject.h"
#include "Primitive.h"
#include "Camera.h"
#include "ModelManager.h"

#define ENTITIES EntityManager::Instance()

class EntityManager
{
public:
	inline static EntityManager& Instance()
	{
		static EntityManager manager;
		return manager;
	}

	void InitializeEntities();
	void EntitiesUpdate();

private:
	EntityManager() = default;
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator =(const EntityManager&) = delete;
	std::vector<Entity*> entities;
};

