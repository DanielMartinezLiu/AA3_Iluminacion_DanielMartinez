#include "Primitive.h"

Primitive::Primitive(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec4 _color, glm::vec3 _eyePosition, Material _material)
{
	program = _program;
	transform = Transform(_position, _rotation, _scale);
	color = _color;
	eyePosition = _eyePosition;
	material = _material;

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

	directionalLight = nullptr;
	pointLight = nullptr;
	spotLight = nullptr;

	orbitObject = false;
	angle = 0.f;
	center = glm::vec3(0.f);
	radius = 7.5f;
	speed = glm::two_pi<float>() / 20.0f;

	InitPrimitive();
}

Primitive::Primitive(GLuint _program, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec4 _color, glm::vec3 _eyePosition, Material _material, GLfloat _radius, GLfloat _speed, GLfloat _angle, bool _orbitObject)
{
	program = _program;
	transform = Transform(_position, _rotation, _scale);
	color = _color;
	eyePosition = _eyePosition;
	material = _material;

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

	directionalLight = nullptr;
	pointLight = nullptr;
	spotLight = nullptr;

	center = glm::vec3(0.f);
	radius = _radius;
	speed = _speed;
	angle = _angle;
	orbitObject = _orbitObject;

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

	//Indico que el VBO activo es el que acabo de crear y que almacenar� un array. Todos los VBO que genere se asignaran al �ltimo VAO que he hecho glBindVertexArray
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Definimos modo de dibujo para cada cara
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Ponemos los valores en el VBO creado
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * points.size(), points.data(), GL_STATIC_DRAW);

	//Indicamos donde almacenar y como esta distribuida la informaci�n
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	//Indicamos que la tarjeta gr�fica puede usar el atributo 0
	glEnableVertexAttribArray(0);

	//Desvinculamos VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Desvinculamos VAO
	glBindVertexArray(0);
}

void Primitive::Update()
{
	glUseProgram(program);

	// Actualizaci�n de la �rbita
	if (orbitObject)
	{
		UpdateOrbit();
	}

	// Generaci�n de matrices de transformaci�n
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

	glUniform3f(glGetUniformLocation(program, "eyePosition"), eyePosition.x, eyePosition.y, eyePosition.z);

	// Usar el material del objeto
	material.UseMaterial(program);

	// Pasar la luz direccional
	if (directionalLight != nullptr)
	{
		directionalLight->UseDirectionalLight(program);
	}
	// Pasar la point light
	if (pointLight != nullptr)
	{
		pointLight->UsePointLight(program);
	}
	// Pasar la spot light
	if (spotLight != nullptr)
	{
		spotLight->UseSpotLight(program);
	}
}

void Primitive::Render()
{
	//Vinculo su VAO para ser usado
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, points.size() / 3);

	//Desvinculamos VAO
	glBindVertexArray(0);
}

void Primitive::UpdateOrbit()
{
	// Actualizaci�n del �ngulo
	angle += speed * TIME_MANAGER.GetDeltaTime();

	// Correcci�n del �ngulo si supera un ciclo completo
	if (angle > glm::two_pi<float>()) {
		angle -= glm::two_pi<float>();
	}

	// Actualizaci�n de la posici�n del objeto en la �rbita
	transform.position.x = center.x + radius * cos(angle);
	transform.position.y = center.y + radius * sin(angle);
	transform.position.z = 0;
}

void Primitive::SetLights(DirectionalLight* dLight, PointLight* pLight, SpotLight* sLight)
{
	directionalLight = dLight;
	pointLight = pLight;
	spotLight = sLight;
}
