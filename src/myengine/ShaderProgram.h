#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <fstream>
#include <iostream>
#include <string>

class VertexArray;

class ShaderProgram
{
public:
	ShaderProgram(std::string vert, std::string frag);
	void Draw(VertexArray& vertexArray);
	void SetUniform(std::string uniform, glm::vec4 value);
	void SetUniform(std::string uniform, float value);
	void SetUniform(std::string uniform, glm::mat4 value);

	GLuint GetId() { return m_id; }

private:
	GLuint m_id;
};