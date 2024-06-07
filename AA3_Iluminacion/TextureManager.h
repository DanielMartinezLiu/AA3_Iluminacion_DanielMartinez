#pragma once
#include <vector>
#include "Texture.h"

#define TEXTURES TextureManager::Instance()

class TextureManager
{
public:
	inline static TextureManager& Instance()
	{
		static TextureManager manager;
		return manager;
	}

	void InitTextures();
	void LoadTextures();

private:
	TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator =(const TextureManager&) = delete;

	std::vector<Texture> textures;

};

