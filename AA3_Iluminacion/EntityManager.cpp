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

	// Inicializamos la camara
	Camera* camera = new Camera(
		PROGRAMS.GetCompiledPrograms()[0], 
		glm::vec3(0.f, 5.f, 0.f), 
		glm::vec3(0.f, 1.f, 0.f), 
		-60.f, 0.f, 5.f, 0.25f
	);

	// Ponemos la camara en la spotlight para que le siga la posicion
	spotLights[0]->SetCamera(camera);

	// Inicializamos el troll
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

	// Ponemos que le afecten todas las luces en el troll
	troll->SetDirectionalLights(*directionalLights.data(), directionalLights.size());
	troll->SetPointLights(*pointLights.data(), pointLights.size());
	troll->SetSpotLights(*spotLights.data(), spotLights.size());

	// Ponemos el troll dentro del vector de entidades
	entities.push_back(troll);

	// Inicializamos la piedra
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

	// Ponemos que le afecten todas las luces en la piedra
	stone->SetDirectionalLights(*directionalLights.data(), directionalLights.size());
	stone->SetPointLights(*pointLights.data(), pointLights.size());
	stone->SetSpotLights(*spotLights.data(), spotLights.size());

	// Ponemos la piedra dentro del vector de entidades
	entities.push_back(stone);

	// Inicializamos la casa
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

	// Ponemos que le afecten todas las luces en la casa
	house->SetDirectionalLights(*directionalLights.data(), directionalLights.size());
	house->SetPointLights(*pointLights.data(), pointLights.size());
	house->SetSpotLights(*spotLights.data(), spotLights.size());

	// Ponemos la casa dentro del vector de entidades
	entities.push_back(house);

	// Inicializamos la primitiva del suelo
	Primitive* ground = new Primitive(
		PROGRAMS.GetCompiledPrograms()[0], 
		glm::vec3(0.f, -0.5f, 0.f), 
		glm::vec3(0.f, 1.f, 0.f), 
		glm::vec3(10.f, 1.f, 10.f), 
		glm::vec4(0.2f, 0.1f, 0.f, 1.f), 
		camera->GetCameraPosition(),
		shinyMaterial
	);

	// Ponemos que le afecten todas las luces en el suelo
	ground->SetDirectionalLights(*directionalLights.data(), directionalLights.size());
	ground->SetPointLights(*pointLights.data(), pointLights.size());
	ground->SetSpotLights(*spotLights.data(), spotLights.size());

	// Ponemos el suelo dentro del vector de entidades
	entities.push_back(ground);

	// Inicializamos la primitiva del sol
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

	// Ponemos el sol dentro del vector de entidades
	entities.push_back(sun);

	// Inicializamos la primitiva la luna
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

	// Ponemos la luna dentro del vector de entidades
	entities.push_back(moon);

	// Ponemos la camara dentro del vector de entidades
	entities.push_back(camera);
}
void EntityManager::InitializeSpawnPoints()
{
	// Variedad de spawnpoints para el random
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
	// Pillamos una posicion random
	int randomPosId = rand() % spawnPoints.size();
	glm::vec3 randomPos;

	// Iteramos para coger una posicion aleatoria
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
	// Actualizamos el Time manager
	TIME_MANAGER.Update();
	float deltaTime = TIME_MANAGER.GetDeltaTime();

	// Hacemos un update para todas las entidades
	for (Entity* item : entities)
	{
		item->Update();
		item->Render();
	}

	// Hacemos un update para todas los puntos de luz
	for (PointLight* light : pointLights) {
		light->Update();
	}

	// Hacemos un update para todas los focos de luz
	for (SpotLight* light : spotLights) {
		light->Update();
	}
}

