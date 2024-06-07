#pragma once
#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <fstream>
#include <vector>
#include <sstream>

#include "Model.h"

#define MODELS ModelManager::Instance()

class ModelManager
{
private:

	ModelManager() = default;
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator =(const ModelManager&) = delete;

	std::vector<Model> models;
public:
	inline static ModelManager& Instance()
	{
		static ModelManager manager;
		return manager;
	}
	
	void LoadAllModels();
	static Model LoadOBJModel(const std::string& filePath);


	inline Model GetModel(int _modelId) { return models[_modelId]; }

};

