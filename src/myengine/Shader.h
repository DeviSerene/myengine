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

class Shader : public Resource
{
public:
	static std::shared_ptr<Shader> Load(std::string _path);

	GLuint GetShader() { return _shaderProgram; }
	GLuint GetUniformLocation(std::string _id);
	bool LoadShaders(std::string vertFilename, std::string fragFilename);
	void AddUniform(std::string _uniform);
	void SetUniform(GLuint _location, glm::mat4 _set){glUniformMatrix4fv(_location, 1, GL_FALSE, glm::value_ptr(_set));}
	void SetUniform(GLuint _location, glm::vec4 _set) { glUniform4fv(_location, 1, glm::value_ptr(_set)); }
	void SetUniform(GLuint _location, glm::vec2 _set) { glUniform2fv(_location, 1, glm::value_ptr(_set)); }
	void SetUniform(GLuint _location, glm::vec3 _set) { glUniform3fv(_location, 1, glm::value_ptr(_set)); }
	void SetUniform(GLuint _location, bool _set) { glUniform1f(_location, _set); }


	void SetMatrices(glm::mat4 modelMatrix, glm::mat4 invModelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix);
	void AddTexture(std::shared_ptr<Texture> _tex, std::string _type);
	void Apply();
private:
	GLuint _shaderProgram;
	bool CheckShaderCompiled(GLint shader);
	std::vector <std::shared_ptr<Uniform>> m_uniforms;
	bool loaded;
};
