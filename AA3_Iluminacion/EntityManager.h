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

	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;

	void InitializeEntities();
	void EntitiesUpdate();

private:
	EntityManager() = default;
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator =(const EntityManager&) = delete;
	std::vector<Entity*> entities;
};

