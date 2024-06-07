#include "TextureManager.h"

void TextureManager::InitTextures()
{
	textures.push_back(Texture());
	textures[0].InitTexture("Assets/Textures/troll.png");
	textures.push_back(Texture());
	textures[1].InitTexture("Assets/Textures/rock.png");
}

void TextureManager::LoadTextures()
{
	textures[0].LoadTexture(GL_TEXTURE0);
	textures[1].LoadTexture(GL_TEXTURE1);
}
