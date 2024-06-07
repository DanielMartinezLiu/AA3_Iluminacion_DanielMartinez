#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Program
{
public: 
	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;

	Program(std::string vertexPath, std::string geometryPath, std::string fragmentPath)
	{
		vertexShader = LoadVertexShader(vertexPath);
		geometryShader = LoadGeometryShader(geometryPath);
		fragmentShader = LoadFragmentShader(fragmentPath);
	}

	//Cargar Archivo
	std::string Load_File(const std::string& filePath);

	//Cargar Shaders
	GLuint LoadFragmentShader(const std::string& filePath);
	GLuint LoadGeometryShader(const std::string& filePath);
	GLuint LoadVertexShader(const std::string& filePath);
};

