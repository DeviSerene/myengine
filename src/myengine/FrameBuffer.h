#pragma once
#include <string>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include <fstream>

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	GLuint GetBuffer() { return m_buffer; }

private:
	GLuint m_buffer;
	GLuint m_depth;
	GLuint m_texture;
};