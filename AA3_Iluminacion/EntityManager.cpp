#include "EntityManager.h"

void EntityManager::InitializeEntities()
{
	glm::vec3 lightDirection(2.f, 1.f, 2.f);

	entities.push_back(new GameObject(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 180.f, 0.f), glm::vec3(1.f), MODELS.GetModel(0), Light(1.f, 1.f, 1.f, 0.2f, lightDirection.x, lightDirection.y, lightDirection.z, 1.f), 0));

	entities.push_back(new Primitive(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.f, -1.f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(10.f, 1.f, 10.f), glm::vec4(0.7f, 0.5f, 0.f, 1.f), Light(0.3f, 0.3f, 0.3f, 1.f, lightDirection.x, lightDirection.y, lightDirection.z, 1.f))); //Suelo
	
	entities.push_back(new Camera(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.f, 2.f, -10.f), glm::vec3(0.f, 1.f, 0.f), -60.f, 0.f, 5.f, 0.25f));
}

void EntityManager::EntitiesUpdate()
{
	for (Entity* item : entities)
	{
		item->Update();
		item->Render();
	}

}