#include "ModelManager.h"


void ModelManager::LoadAllModels()
{
	models.push_back(LoadOBJModel("Assets/Models/troll.obj"));
	models.push_back(LoadOBJModel("Assets/Models/rock.obj"));
}

Model ModelManager::LoadOBJModel(const std::string& filePath)
{
	//Verifico archivo y si no puedo abrirlo cierro aplicativo
	std::ifstream file(filePath);

	if (!file.is_open()) {
		std::cerr << "Unable to open file: " << filePath << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//Variables lectura fichero
	std::string line;
	std::stringstream ss;
	std::string prefix;
	glm::vec3 tmpVec3;
	glm::vec2 tmpVec2;

	//Variables elemento modelo
	std::vector<float> vertices;
	std::vector<float> vertexNormals;
	std::vector<float> textureCoordinates;

	//Variables temporales para algoritmos de sort
	std::vector<glm::vec3> tmpVertices;
	std::vector<glm::vec3> tmpNormals;
	std::vector<glm::vec2> tmpTextureCoordinates;

	//Index buffer para las caras 
	std::vector<unsigned int> indices;

	//Recorremos archivo linea por linea
	while (std::getline(file, line)) {

		//Por cada linea reviso el prefijo del archivo que me indica que estoy analizando
		ss.clear();
		ss.str(line);
		ss >> prefix;

		//Estoy leyendo un vertice
		if (prefix == "v") {

			//Asumo que solo trabajo 3D así que almaceno XYZ de forma consecutiva
			ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;

			//Almaceno en mi vector de vertices los valores
			tmpVertices.push_back(tmpVec3);
		}

		//Estoy leyendo una UV (texture coordinate)
		else if (prefix == "vt") {

			//Las UVs son siempre imagenes 2D asi que uso el tmpvec2 para almacenarlas
			ss >> tmpVec2.x >> tmpVec2.y;

			//Almaceno en mi vector temporal las UVs
			tmpTextureCoordinates.push_back(tmpVec2);
		}

		//Estoy leyendo una normal
		else if (prefix == "vn") {

			//Asumo que solo trabajo 3D así que almaceno XYZ de forma consecutiva
			ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;

			//Almaceno en mi vector temporal de normales las normales
			tmpNormals.push_back(tmpVec3);

		}

		//Estoy leyendo una cara
		else if (prefix == "f") {
			// Vectores para guardar los indices de los vertices, UVs y normales
			std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
			unsigned int vertexIndex, uvIndex, normalIndex;
			char slash;

			// Bucle para leer las caras
			while (ss >> vertexIndex >> slash >> uvIndex >> slash >> normalIndex) {
				// Guarda los indicies para los vertices, UVs y normales
				vertexIndices.push_back(vertexIndex - 1);
				uvIndices.push_back(uvIndex - 1);
				normalIndices.push_back(normalIndex - 1);
			}

			// Bucle entre todo los indicies
			for (size_t i = 0; i < vertexIndices.size(); ++i) {
				// Añadimos la posicion de los vertices al vector de vertices.
				vertices.push_back(tmpVertices[vertexIndices[i]].x);
				vertices.push_back(tmpVertices[vertexIndices[i]].y);
				vertices.push_back(tmpVertices[vertexIndices[i]].z);

				// Si las texturas estan, añadimos al vector de cordenadas de texturas
				if (!tmpTextureCoordinates.empty()) {
					textureCoordinates.push_back(tmpTextureCoordinates[uvIndices[i]].x);
					textureCoordinates.push_back(tmpTextureCoordinates[uvIndices[i]].y);
				}

				// Si las normales estan, añadimos al vector de normales
				if (!tmpNormals.empty()) {
					vertexNormals.push_back(tmpNormals[normalIndices[i]].x);
					vertexNormals.push_back(tmpNormals[normalIndices[i]].y);
					vertexNormals.push_back(tmpNormals[normalIndices[i]].z);
				}

				// Añadimos los indicies al vector de indicies.
				indices.push_back(static_cast<unsigned int>(indices.size()));
			}
		}
	}
	file.close();

	if (vertexNormals.empty()) {
		vertexNormals.resize(vertices.size(), 0.0f);
		CalculateAverageNormals(indices.data(), static_cast<unsigned int>(indices.size()), vertices.data(), static_cast<unsigned int>(vertices.size()), 3, 0);
	}

	return Model(vertices, textureCoordinates, vertexNormals);
}

void ModelManager::CalculateAverageNormals(unsigned int* indices, unsigned int indiceCount, float* vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;

		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);

		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0] += normal.x;
		vertices[in0 + 1] += normal.y;
		vertices[in0 + 2] += normal.z;

		vertices[in1] += normal.x;
		vertices[in1 + 1] += normal.y;
		vertices[in1 + 2] += normal.z;

		vertices[in2] += normal.x;
		vertices[in2 + 1] += normal.y;
		vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);

		vertices[nOffset] = vec.x;
		vertices[nOffset + 1] = vec.y;
		vertices[nOffset + 2] = vec.z;
	}
}
