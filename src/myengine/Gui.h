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
#include "VertexArray.h"

class Core;

class Gui
{
public:
	Gui();
	~Gui();

	bool Button(glm::vec4 _pos, std::string _label);

private:

	void SetUniform(int _location, glm::mat4 _set);

	bool Intersect(glm::vec4 _pos, glm::vec2 _mouse);
	bool LoadShaders(std::string vertFilename, std::string fragFilename);

	std::weak_ptr<Core> m_core;

	// The OpenGL shader program handle
	int _shaderProgram;
	// Locations of Uniforms in the vertex shader
	int _shaderModelMatLocation;
	int _shaderProjMatLocation;
	std::shared_ptr<VertexArray> m_shape;
};
