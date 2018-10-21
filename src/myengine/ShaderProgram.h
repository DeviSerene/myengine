#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Mesh;

class ShaderProgram
{
public:
	ShaderProgram(std::string vert, std::string frag);
	void Draw(std::shared_ptr<Mesh> _mesh);
	void SetUniform(std::string uniform, glm::vec4 value);
	void SetUniform(std::string uniform, float value);
	void SetUniform(std::string uniform, glm::mat4 value); 

	bool SetTexture(std::string filename) { _texture1 = LoadTexture(filename); return _texture1 > 0; }
	bool SetNormal(std::string filename) { _normalTexture = LoadTexture(filename); return _normalTexture > 0; }
	bool SetHeightMap(std::string filename) { _heightTexture = LoadTexture(filename); return _heightTexture > 0; }

	void Apply();

	GLuint GetId() { return m_id; }

private:
	GLuint m_id;

	GLuint _texture1;
	GLuint _normalTexture;
	GLuint _heightTexture;

	unsigned int LoadTexture(std::string filename);
};