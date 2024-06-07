#include "Primitive.h"

Primitive::Primitive(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec4 _color, DirectionalLight _light)
{
	program = _program;
	transform = Transform(_position, _rotation, _scale);
	light = _light;
	color = _color;

	points = {
				-1.f, +1.f, -1.f,
				+1.f, +1.f, -1.f,
				-1.f, -1.f, -1.f,
				+1.f, -1.f, -1.f,
				+1.f, -1.f, +1.f,
				+1.f, +1.f, -1.f,
				+1.f, +1.f, +1.f,
				-1.f, +1.f, -1.f,
				-1.f, +1.f, +1.f,
				-1.f, -1.f, -1.f,
				-1.f, -1.f, +1.f,
				+1.f, -1.f, +1.f,
				-1.f, +1.f, +1.f,
				+1.f, +1.f, +1.f
	};

	InitPrimitive();
}

void Primitive::InitPrimitive()
{
	//Definimos cantidad de vao a crear y donde almacenarlos 
	glGenVertexArrays(1, &vao);

	//Indico que el VAO activo de la GPU es el que acabo de crear
	glBindVertexArray(vao);

	//Definimos cantidad de vbo a crear y donde almacenarlos
	glGenBuffers(1, &vbo);

	//Indico que el VBO activo es el que acabo de crear y que almacenará un array. Todos los VBO que genere se asignaran al último VAO que he hecho glBindVertexArray
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Definimos modo de dibujo para cada cara
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Ponemos los valores en el VBO creado
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * points.size(), points.data(), GL_STATIC_DRAW);

	//Indicamos donde almacenar y como esta distribuida la información
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	//Indicamos que la tarjeta gráfica puede usar el atributo 0
	glEnableVertexAttribArray(0);

	//Desvinculamos VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Desvinculamos VAO
	glBindVertexArray(0);
}

void Primitive::Update()
{
	glUseProgram(program);

	glm::mat4 translationMatrix = Transform::GenerateTranslationMatrix(transform.position);
	glm::mat4 rotationMatrix = Transform::GenerateRotationMatrix(transform.rotation, transform.rotation.x);
	rotationMatrix *= Transform::GenerateRotationMatrix(transform.rotation, transform.rotation.y);
	rotationMatrix *= Transform::GenerateRotationMatrix(transform.rotation, transform.rotation.z);
	glm::mat4 scaleMatrix = Transform::GenerateScaleMatrix(transform.scale);


	//Asignar valores iniciales al programa
	glUniform2f(glGetUniformLocation(program, "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

	// Pasar las matrices
	glUniformMatrix4fv(glGetUniformLocation(program, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));

	glUniform4f(glGetUniformLocation(program, "baseColor"), color.x, color.y, color.z, color.w);
	glUniform1i(glGetUniformLocation(program, "usingTexture"), 0);

	light.UseDirectionalLight(program);
}

void Primitive::Render()
{
	//Vinculo su VAO para ser usado
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, points.size() / 3);

	//Desvinculamos VAO
	glBindVertexArray(0);
}

void Primitive::SetPointLights(PointLight* pLight, unsigned int lightCount)
{
	pointLights = pLight;
	pointLightCount = lightCount;

	if (lightCount > MAX_POINT_LIGHTS)
		lightCount = MAX_POINT_LIGHTS;

	glUniform1i(glGetUniformLocation(program, "pointLightCount"), lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		pLight[i].UsePointLight(program, i);
	}
}

void Primitive::SetSpotLights(SpotLight* sLight, unsigned int lightCount)
{
	spotLights = sLight;
	spotLightCount = lightCount;

	if (lightCount > MAX_SPOT_LIGHTS)
		lightCount = MAX_SPOT_LIGHTS;

	glUniform1i(glGetUniformLocation(program, "spotLightCount"), lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		sLight[i].UseSpotLight(program, i);
	}
}