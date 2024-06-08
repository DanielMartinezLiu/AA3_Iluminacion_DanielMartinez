#include "EntityManager.h"

void EntityManager::InitializeEntities()
{
	InitializeSpawnPoints();

	pointLights.push_back(new PointLight(
		1.f, 1.f, 1.f,							//Color
		7.5f, 3.5f,								//Intensity
		0.f, 0.2f, 0.f,							//Position
		0.3f, 0.2f, 0.1f,						//Lights constants
		7.5f, glm::two_pi<float>() / 20.0f, 0.f // Orbit
	));

	spotLights.push_back(new SpotLight(
		1.f, 1.f, 1.f,							//Color
		3.f, 1.f,								//Intensity
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

	GameObject* troll = new GameObject(
		PROGRAMS.GetCompiledPrograms()[0], 
		GetRandomUnusedPosition(),
		glm::vec3(0.f, 180.f, 0.f), 
		glm::vec3(1.f), 
		camera->GetCameraPosition(), 
		MODELS.GetModel(0), 
		shinyMaterial, 
		0
	);

	troll->SetDirectionalLights(*directionalLights.data(), directionalLights.size());
	troll->SetPointLights(*pointLights.data(), pointLights.size());
	troll->SetSpotLights(*spotLights.data(), spotLights.size());

	entities.push_back(troll);

	GameObject* stone = new GameObject(
		PROGRAMS.GetCompiledPrograms()[0],
		GetRandomUnusedPosition(),
		glm::vec3(0.f, 180.f, 0.f),
		glm::vec3(0.5f),
		camera->GetCameraPosition(),
		MODELS.GetModel(1),
		shinyMaterial,
		1
	);

	stone->SetDirectionalLights(*directionalLights.data(), directionalLights.size());
	stone->SetPointLights(*pointLights.data(), pointLights.size());
	stone->SetSpotLights(*spotLights.data(), spotLights.size());

	entities.push_back(stone);

	GameObject* house = new GameObject(
		PROGRAMS.GetCompiledPrograms()[0],
		GetRandomUnusedPosition(),
		glm::vec3(0.f, 180.f, 0.f),
		glm::vec3(0.5f),
		camera->GetCameraPosition(),
		MODELS.GetModel(2),
		shinyMaterial,
		2
	);

	house->SetDirectionalLights(*directionalLights.data(), directionalLights.size());
	house->SetPointLights(*pointLights.data(), pointLights.size());
	house->SetSpotLights(*spotLights.data(), spotLights.size());

	entities.push_back(house);

	Primitive* ground = new Primitive(
		PROGRAMS.GetCompiledPrograms()[0], 
		glm::vec3(0.f, -0.5f, 0.f), 
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
		glm::vec3(0.5f, 0.5f, 0.5f),
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
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec4(1.f, 1.f, 1.f, 1.f),
		camera->GetCameraPosition(),
		shinyMaterial,
		7.5f, glm::two_pi<float>() / 20.0f, glm::pi<float>(), true
	);

	entities.push_back(moon);

	entities.push_back(camera);
}
void EntityManager::InitializeSpawnPoints()
{
	spawnPoints.push_back(glm::vec3(4.f, 0.5f, -1.f));
	spawnPoints.push_back(glm::vec3(2.f, 0.5f, -1.f));
	spawnPoints.push_back(glm::vec3(-4.f, 0.5f, 7.f));
	spawnPoints.push_back(glm::vec3(-1.f, 0.5f, -1.f));
	spawnPoints.push_back(glm::vec3(0.f, 0.5f, 0.f));
	spawnPoints.push_back(glm::vec3(1.f, 0.5f, 1.f));
	spawnPoints.push_back(glm::vec3(-2.f, 0.5f, 2.f));
	spawnPoints.push_back(glm::vec3(3.f, 0.5f, -6.f));
	spawnPoints.push_back(glm::vec3(-7.f, 0.5f, -1.f));

	for (int i = 0; i < spawnPoints.size(); i++)
	{
		usedSpawnPoint.push_back(false);
	}
}
glm::vec3 EntityManager::GetRandomUnusedPosition()
{
	int randomPosId = rand() % spawnPoints.size();
	glm::vec3 randomPos;

	if (usedSpawnPoint[randomPosId])
		randomPos = GetRandomUnusedPosition();
	else
	{
		randomPos = spawnPoints[randomPosId];
		usedSpawnPoint[randomPosId] = true;
	}

	return randomPos;
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

