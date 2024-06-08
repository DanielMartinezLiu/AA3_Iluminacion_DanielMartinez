#include "EntityManager.h"

void EntityManager::InitializeEntities()
{
	pointLights.push_back(new PointLight(
		0.f, 0.f, 0.f,			/*Color*/
		0.f, 0.5f,				/*Intensity*/
		0.f, 1.f, 0.f,			/*Position*/
		0.3f, 0.2f, 0.1f		/*Lights constants*/
	));

	spotLights.push_back(new SpotLight(
		1.f, 1.f, 1.f,			/*Color*/
		0.5f, 1.f,				/*Intensity*/
		0.f, 0.f, 0.f,			/*Position*/
		0.f, -1.f, 0.f,			/*Direction*/
		1.f, 0.2f, 0.032f,		/*Lights constants*/
		15.f					/*Radius*/
	));

	directionalLights.push_back(new DirectionalLight(
		1.f, 1.f, 1.f,			/*Color*/
		0.2f, 0.5f,				/*Intensity*/
		1.f, 1.f, 0.f			/*Direction*/
	));

	Material shinyMaterial = Material(1.0f, 32);
	Material dullMaterial = Material(0.3f, 4);

	Camera* camera = new Camera(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.f, 2.f, -10.f), glm::vec3(0.f, 1.f, 0.f), -60.f, 0.f, 5.f, 0.25f);

	spotLights[0]->SetCamera(camera);

	GameObject* modelOne = new GameObject(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 180.f, 0.f), glm::vec3(1.f), camera->GetCameraPosition(), MODELS.GetModel(0), shinyMaterial, 0);
	modelOne->SetDirectionalLights(*directionalLights.data(), directionalLights.size());
	modelOne->SetSpotLights(*spotLights.data(), spotLights.size());
	modelOne->SetPointLights(*pointLights.data(), pointLights.size());

	entities.push_back(modelOne);

	Primitive* groud = new Primitive(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.f, -1.f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(10.f, 1.f, 10.f), glm::vec4(0.7f, 0.5f, 0.f, 1.f));

	entities.push_back(groud);

	entities.push_back(camera);
}

void EntityManager::EntitiesUpdate()
{
	for (Entity* item : entities)
	{
		item->Update();
		item->Render();
	}
	for (PointLight* light : pointLights) {
		light->Update();
	}

	for (SpotLight* light : spotLights) {
		light->Update();
	}
}

