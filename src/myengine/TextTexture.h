#pragma once
#include "Resource.h"
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Texture.h"
#include <SDL2/SDL_ttf.h>

class TextTexture : public Resource
{
public:
	static std::shared_ptr<TextTexture> Create();
	static std::shared_ptr<TextTexture> Load(std::string _path);
	void SetText(SDL_Color _colour, int _textsize);
	GLuint GetTexture() { return  m_texture; }
private:
	// OpenGL handle for the texture
	GLuint m_texture;
};