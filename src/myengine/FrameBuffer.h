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
	GLuint GetTexture() { return m_texture; }
	GLuint GetDepth() { return m_depth; }

	void Update(int x, int y);

private:
	GLuint m_buffer;
	GLuint m_texture;
	GLuint m_depth;

	int m_x;
	int m_y;
};