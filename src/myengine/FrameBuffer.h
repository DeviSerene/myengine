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

/*!
A framebuffer is attached to a Camera and PostProcessing classes, and could be attached to any user's Components.
It is able to contain a texture, which can be used for shaders.
*/

class FrameBuffer
{
public:
	FrameBuffer(bool _depth = true);
	~FrameBuffer();

	GLuint GetBuffer() { return m_buffer; }
	GLuint GetTexture() { return m_texture; }
	GLuint GetDepth() { return m_depth; }

	void Update(int x, int y);

private:
	GLuint m_buffer;
	GLuint m_texture;
	GLuint m_depth;

	bool m_useD;
	int m_x;
	int m_y;
};