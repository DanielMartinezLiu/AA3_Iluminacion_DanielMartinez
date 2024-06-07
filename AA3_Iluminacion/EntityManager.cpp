#include "EntityManager.h"

void EntityManager::InitializeEntities()
{
	glm::vec3 lightDirection = glm::vec3(2.f, 1.f, 2.f);
	glm::vec4 ambientColor = glm::vec4(1.f, 1.f, 1.f, 0.2f);

	Material shinyMaterial = Material(1.0f, 32);
	Material dullMaterial = Material(0.3f, 4);

	Camera* camera = new Camera(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.f, 2.f, -10.f), glm::vec3(0.f, 1.f, 0.f), -60.f, 0.f, 5.f, 0.25f);

	glm::vec3 eyePosition = camera->GetCameraPosition();

	Light* sceneLight = new Light(eyePosition.x, eyePosition.y, eyePosition.z,
		ambientColor.x, ambientColor.y, ambientColor.z, ambientColor.w,
		lightDirection.x, lightDirection.y, lightDirection.z,
		1.0f, shinyMaterial);

	entities.push_back(new GameObject(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 180.f, 0.f), glm::vec3(1.f), MODELS.GetModel(0), *sceneLight, 0));

	entities.push_back(new Primitive(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.f, -1.f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(10.f, 1.f, 10.f), glm::vec4(0.7f, 0.5f, 0.f, 1.f), *sceneLight));
	
	entities.push_back(camera);
}

void EntityManager::EntitiesUpdate()
{
	for (Entity* item : entities)
	{
		item->Update();
		item->Render();
	}

}