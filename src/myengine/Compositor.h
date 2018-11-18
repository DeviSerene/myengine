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
#include "Shader.h"
#include "FrameBuffer.h"
#include "VertexArray.h"

class Core;

enum COMPOSITION_TYPE
{
	COMP_2_SPLIT_H
};

class Compositor
{
public:
	Compositor(std::shared_ptr<Core> _c);
	~Compositor();

	void Composition(std::vector<std::shared_ptr<FrameBuffer>> _fbs, COMPOSITION_TYPE _ct);
	GLuint GetBuffer() { return m_buffer; }
	GLuint GetTexture() { return m_texture; }

	void Update(int x, int y);

private:
	GLuint m_buffer;
	GLuint m_texture;
	GLuint m_depth;
	void Creation();
	std::shared_ptr<Shader> m_shader;
	std::weak_ptr<Core> m_core;
	std::shared_ptr<VertexArray> m_shape;

	int m_x;
	int m_y;
};