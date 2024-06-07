#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "GLManager.h"
#include "TimeManager.h"
#include "Entity.h"


class Camera : public Entity
{
public:
    Camera();
    Camera(GLuint _program, glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

    void KeyControl(bool* keys, GLfloat deltaTime);
    void MouseControl(GLfloat xChange, GLfloat yChange);

    glm::vec3 GetCameraPosition();
    glm::vec3 GetCameraDirection();

    glm::mat4 CalculateViewMatrix();

    void Update() override;
    void Render() override;

    ~Camera();
private:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float fFov = 45.f;
    float fNear = 0.1f;
    float fFar = 100.f;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat moveSpeed;
    GLfloat turnSpeed;
};
