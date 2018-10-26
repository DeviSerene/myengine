#include "Shader.h"
#include <iostream>
#include <fstream>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>

bool Shader::LoadShaders(std::string vertFilename, std::string fragFilename)
{
	// OpenGL doesn't provide any functions for loading shaders from file


	std::ifstream vertFile(vertFilename);
	char *vShaderText = NULL;

	if (vertFile.is_open())
	{
		// Find out how many characters are in the file
		vertFile.seekg(0, vertFile.end);
		int length = (int)vertFile.tellg();
		vertFile.seekg(0, vertFile.beg);

		// Create our buffer
		vShaderText = new char[length];

		// Transfer data from file to buffer
		vertFile.read(vShaderText, length);

		// Check it reached the end of the file
		if (!vertFile.eof())
		{
			vertFile.close();
			std::cerr << "WARNING: could not read vertex shader from file: " << vertFilename << std::endl;
			return false;
		}

		// Find out how many characters were actually read
		length = (int)vertFile.gcount();

		// Needs to be NULL-terminated
		vShaderText[length - 1] = 0;

		vertFile.close();
	}
	else
	{
		std::cerr << "WARNING: could not open vertex shader from file: " << vertFilename << std::endl;
		return false;
	}


	std::ifstream fragFile(fragFilename);
	char *fShaderText = NULL;

	if (fragFile.is_open())
	{
		// Find out how many characters are in the file
		fragFile.seekg(0, fragFile.end);
		int length = (int)fragFile.tellg();
		fragFile.seekg(0, fragFile.beg);

		// Create our buffer
		fShaderText = new char[length];

		// Transfer data from file to buffer
		fragFile.read(fShaderText, length);

		// Check it reached the end of the file
		if (!fragFile.eof())
		{
			fragFile.close();
			std::cerr << "WARNING: could not read fragment shader from file: " << fragFilename << std::endl;
			return false;
		}

		// Find out how many characters were actually read
		length = (int)fragFile.gcount();

		// Needs to be NULL-terminated
		fShaderText[length - 1] = 0;

		fragFile.close();
	}
	else
	{
		std::cerr << "WARNING: could not open fragment shader from file: " << fragFilename << std::endl;
		return false;
	}



	// The 'program' stores the shaders
	_shaderProgram = glCreateProgram();

	// Create the vertex shader
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	// Give GL the source for it
	glShaderSource(vShader, 1, &vShaderText, NULL);
	// Delete buffer
	delete[] vShaderText;
	// Compile the shader
	glCompileShader(vShader);
	// Check it compiled and give useful output if it didn't work!
	if (!CheckShaderCompiled(vShader))
	{
		std::cerr << "ERROR: failed to compile vertex shader" << std::endl;
		return false;
	}
	// This links the shader to the program
	glAttachShader(_shaderProgram, vShader);

	// Same for the fragment shader
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderText, NULL);
	// Delete buffer
	delete[] fShaderText;
	glCompileShader(fShader);
	if (!CheckShaderCompiled(fShader))
	{
		std::cerr << "ERROR: failed to compile fragment shader" << std::endl;
		return false;
	}
	glAttachShader(_shaderProgram, fShader);

	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram(_shaderProgram);
	// Check this worked
	GLint linked;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(_shaderProgram, len, &len, log);
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete[] log;

		return false;
	}


	// We will define matrices which we will send to the shader
	// To do this we need to retrieve the locations of the shader's matrix uniform variables
	glUseProgram(_shaderProgram);

	return true;
}

bool Shader::CheckShaderCompiled(GLint shader)
{
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLsizei len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		// OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(shader, len, &len, log);
		std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete[] log;

		return false;
	}
	return true;
}


void Shader::AddUniform(std::string _uniform)
{
	if (m_uniforms.empty())
	{
		for (unsigned int i = 0; i < m_uniforms.size(); i++)
		{
			if (m_uniforms[i]->m_ID == _uniform) return;
		}
	}

	//add the uniform
	std::shared_ptr<Uniform> uni = std::shared_ptr<Uniform>(new Uniform());
	uni->m_ID = _uniform;
	uni->m_location = glGetUniformLocation(_shaderProgram, _uniform.c_str());
	m_uniforms.push_back(uni);
}

void Shader::SetMatrices(glm::mat4 modelMatrix, glm::mat4 invModelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	glUseProgram(_shaderProgram);
	// Send matrices and uniforms
	if (m_uniforms.empty())
	{
		for (unsigned int i = 0; i < m_uniforms.size(); i++)
		{
			if (m_uniforms[i]->m_ID == "modelMat")
			{
				glUniformMatrix4fv(m_uniforms[i]->m_location, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			}
			else if (m_uniforms[i]->m_ID == "invModelMat")
			{
				glUniformMatrix4fv(m_uniforms[i]->m_location, 1, GL_FALSE, glm::value_ptr(invModelMatrix));
			}
			else if (m_uniforms[i]->m_ID == "viewMat")
			{
				glUniformMatrix4fv(m_uniforms[i]->m_location, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			}
			else if (m_uniforms[i]->m_ID == "projMat")
			{
				glUniformMatrix4fv(m_uniforms[i]->m_location, 1, GL_FALSE, glm::value_ptr(projMatrix));
			}
		}
	}
}

void Shader::AddTexture(std::shared_ptr<Texture> _tex, std::string _type)
{
	if (m_uniforms.empty())
	{
		for (unsigned int i = 0; i < m_uniforms.size(); i++)
		{
			if (m_uniforms[i]->m_ID == _type)
			{
				//it is already here, lets replace it
				m_uniforms[i]->m_texture = _tex->GetTexture();
			}
		}
	}

	//add the uniform
	std::shared_ptr<Uniform> uni = std::shared_ptr<Uniform>(new Uniform());
	uni->m_ID = _type;
	uni->m_texture = _tex->GetTexture();
	uni->m_location = glGetUniformLocation(_shaderProgram, _type.c_str());
	m_uniforms.push_back(uni);
}

void Shader::Apply()
{
	glUseProgram(_shaderProgram);

	//apply textures
	if (m_uniforms.empty())
	{
		for (unsigned int i = 0; i < m_uniforms.size(); i++)
		{
			if (m_uniforms[i]->m_ID == "texture")
			{
				glActiveTexture(GL_TEXTURE0);
				glUniform1i(m_uniforms[i]->m_location, 0);
				glBindTexture(GL_TEXTURE_2D, m_uniforms[i]->m_texture);
			}
			else if (m_uniforms[i]->m_ID == "normalTexture")
			{
				glActiveTexture(GL_TEXTURE1);
				glUniform1i(m_uniforms[i]->m_location, 1);
				glBindTexture(GL_TEXTURE_2D, m_uniforms[i]->m_texture);
			}
			else if (m_uniforms[i]->m_ID == "heightTexture")
			{
				glActiveTexture(GL_TEXTURE2);
				glUniform1i(m_uniforms[i]->m_location, 2);
				glBindTexture(GL_TEXTURE_2D, m_uniforms[i]->m_texture);
			}
		}
	}

}