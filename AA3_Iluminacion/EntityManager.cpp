#include "EntityManager.h"

void EntityManager::InitializeEntities()
{
	
	pointLights.push_back(new PointLight(
		1.f, 1.f, 1.f,							//Color
		7.5f, 3.5f,								//Intensity
		0.f, 0.2f, 0.f,							//Position
		0.3f, 0.2f, 0.1f,						//Lights constants
		7.5f, glm::two_pi<float>() / 20.0f, 0.f // Orbit
	));

	spotLights.push_back(new SpotLight(
		1.f, 1.f, 1.f,							//Color
		1.0f, 1.f,								//Intensity
		0.f, 0.f, 0.f,							//Position
		0.f, -1.f, 0.f,							//Direction
		1.f, 0.2f, 0.032f,						//Lights constants
		15.f									//Radius
	));

	directionalLights.push_back(new DirectionalLight(
		1.f, 1.f, 1.f,							//Color
		0.2f, 0.5f,								//Intensity
		1.f, 1.f, 0.f							//Direction
	));

	Material shinyMaterial = Material(1.0f, 32);
	Material dullMaterial = Material(0.3f, 4);

	Camera* camera = new Camera(
		PROGRAMS.GetCompiledPrograms()[0], 
		glm::vec3(0.f, 5.f, 0.f), 
		glm::vec3(0.f, 1.f, 0.f), 
		-60.f, 0.f, 5.f, 0.25f
	);

	spotLights[0]->SetCamera(camera);

	GameObject* modelOne = new GameObject(
		PROGRAMS.GetCompiledPrograms()[0], 
		glm::vec3(0.f, 0.f, 0.f), 
		glm::vec3(0.f, 180.f, 0.f), 
		glm::vec3(1.f), 
		camera->GetCameraPosition(), 
		MODELS.GetModel(0), 
		shinyMaterial, 
		0
	);

	modelOne->SetDirectionalLights(*directionalLights.data(), directionalLights.size());
	modelOne->SetPointLights(*pointLights.data(), pointLights.size());
	modelOne->SetSpotLights(*spotLights.data(), spotLights.size());

	entities.push_back(modelOne);

	Primitive* ground = new Primitive(
		PROGRAMS.GetCompiledPrograms()[0], 
		glm::vec3(0.f, -1.f, 0.f), 
		glm::vec3(0.f, 1.f, 0.f), 
		glm::vec3(10.f, 1.f, 10.f), 
		glm::vec4(0.2f, 0.1f, 0.f, 1.f), 
		camera->GetCameraPosition(),
		shinyMaterial
	);
	ground->SetDirectionalLights(*directionalLights.data(), directionalLights.size());
	ground->SetPointLights(*pointLights.data(), pointLights.size());
	ground->SetSpotLights(*spotLights.data(), spotLights.size());

	entities.push_back(ground);

	Primitive* sun = new Primitive(
		PROGRAMS.GetCompiledPrograms()[0],
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(1.f, 1.f, 1.f),
		glm::vec4(1.f, 1.f, 0.f, 1.f),
		camera->GetCameraPosition(),
		shinyMaterial,
		7.5f, glm::two_pi<float>() / 20.0f, 0.f, true
	);
	entities.push_back(sun);

	Primitive* moon = new Primitive(
		PROGRAMS.GetCompiledPrograms()[0],
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(1.f, 1.f, 1.f),
		glm::vec4(1.f, 1.f, 1.f, 1.f),
		camera->GetCameraPosition(),
		shinyMaterial,
		7.5f, glm::two_pi<float>() / 20.0f, 180.f, true
	);

	entities.push_back(moon);

	entities.push_back(camera);
}

void EntityManager::EntitiesUpdate()
{
	TIME_MANAGER.Update();
	float deltaTime = TIME_MANAGER.GetDeltaTime();

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

