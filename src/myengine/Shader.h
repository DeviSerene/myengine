#pragma once
#include "resource.h"
#include <string>
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "Resource.h"
#include "Texture.h"

struct Uniform
{
	GLuint m_texture;
	GLuint m_location;
	std::string m_ID;
};

class Shader : Resource
{
public:
	bool LoadShaders(std::string vertFilename, std::string fragFilename);
	void AddUniform(std::string _uniform);
	void SetMatrices(glm::mat4 modelMatrix, glm::mat4 invModelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix);
	void AddTexture(std::shared_ptr<Texture> _tex, std::string _type);
	void Apply();
private:
	GLuint _shaderProgram;
	bool CheckShaderCompiled(GLint shader);
	std::vector <std::shared_ptr<Uniform>> m_uniforms;
};
