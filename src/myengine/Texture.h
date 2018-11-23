#pragma once
#include "Resource.h"
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*!
This resource loads an image from file. The image can be .png or .bmp.
.png will create a texture with alpha, while .bmp will not.
The initial width and height of the texture will be recorded when it is loaded, which can be useful for sprites.
*/

class Texture : public Resource
{
public:
	static std::shared_ptr<Texture> Create();
	static std::shared_ptr<Texture> Load(std::string _path);
	void LoadTexture(std::string filename);
	GLuint GetTexture() { return  m_texture; }
	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
	~Texture();
private:
	// OpenGL handle for the texture
	GLuint m_texture;
	int m_width;
	int m_height;
};