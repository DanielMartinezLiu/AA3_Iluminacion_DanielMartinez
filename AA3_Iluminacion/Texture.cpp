#include "Texture.h"

void Texture::InitTexture(const char* path)
{
	//Leer textura
	textureInfo = stbi_load(path, &width, &height, &nrChanels, 4);
}

void Texture::LoadTexture(GLuint textureChannel)
{
	//Definimos canal de textura activo
	glActiveTexture(textureChannel);
	
	//Genero Textura
	GLuint textureID;
	glGenTextures(1, &textureID);

	//Vinculo textura con el canal de textura
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Configurar textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Cargar datos de la imagen a la textura
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureInfo);


	//Generar mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	//Liberar Recursos
	stbi_image_free(textureInfo);
}
