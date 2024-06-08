#include "Camera.h"
Camera::Camera() {}

Camera::Camera(GLuint _program, glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	transform.position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	Update();
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		transform.position += front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		transform.position -= front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		transform.position -= right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		transform.position += right * velocity;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(transform.position, transform.position + front, up);
}

glm::vec3 Camera::GetCameraPosition()
{
	return transform.position;
}
glm::vec3 Camera::GetCameraDirection()
{
	return glm::normalize(front);
}

void Camera::Update()
{
	// Actualizamos los controles
	KeyControl(GLM.GetsKeys(), TIME_MANAGER.GetDeltaTime());
	MouseControl(GLM.GetXChange(), GLM.GetYChange());

	// Calcula las componentes de la dirección 'front' utilizando los ángulos 'yaw' y 'pitch'
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	// Normalizo el vector para asegurar que tenga una longitud de 1
	front = glm::normalize(front);

	// Calcula el vector como el producto cruzado entre 'front' y 'worldUp'.
	right = glm::normalize(glm::cross(front, worldUp));

	// Calcula el vector como el producto cruzado entre 'right' y 'front'.
	up = glm::normalize(glm::cross(right, front));

	Render();
}

void Camera::Render()
{
	// Calcula la matriz de vista utilizando la posición actual de la cámara 
	glm::mat4 viewMatrix = glm::lookAt(transform.position, transform.position + front, up);

	// Calcula la matriz de proyección de perspectiva con el campo de visión, la relación de aspecto de la ventana
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(fFov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, fNear, fFar);

	// Itera sobre todos los programas compilados
	for (GLuint program : PROGRAMS.GetCompiledPrograms())
	{
		glUseProgram(program);
		glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	}
}

Camera::~Camera()
{
}