#include "EntityManager.h"

void EntityManager::InitializeEntities()
{
	glm::vec3 lightDirection = glm::vec3(2.f, 1.f, 2.f);
	glm::vec3 ambientColor = glm::vec3(1.f, 1.f, 1.f);

	float ambientIntensity = 0.2f;
	float diffuseIntensity = 1.0f;

	Material shinyMaterial = Material(1.0f, 32);
	Material dullMaterial = Material(0.3f, 4);

	Camera* camera = new Camera(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.f, 2.f, -10.f), glm::vec3(0.f, 1.f, 0.f), -60.f, 0.f, 5.f, 0.25f);

	DirectionalLight* sceneLight = new DirectionalLight(
		ambientColor.x, ambientColor.y, ambientColor.z, 
		ambientIntensity, diffuseIntensity,
		lightDirection.x, lightDirection.y, lightDirection.z);

	entities.push_back(new GameObject(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 180.f, 0.f), glm::vec3(1.f), camera->GetCameraPosition(), MODELS.GetModel(0), shinyMaterial, *sceneLight, 0));

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