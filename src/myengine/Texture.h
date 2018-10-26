#pragma once
#include "Resource.h"
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>

class Texture : public Resource
{
public:
	static std::shared_ptr<Texture> Load(std::string _path);
	void LoadTexture(std::string filename);
	GLuint GetTexture() { return  m_texture; }
private:
	// OpenGL handle for the texture
	GLuint m_texture;
};