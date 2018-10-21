#include "ShaderProgram.h"
#include "Mesh.h"

ShaderProgram::ShaderProgram(std::string vert, std::string frag)
{
	//Open the VertShader file
	std::ifstream file(vert);
	if (!file.is_open())
	{
		std::cout << "Could not open vertshader file!" << '\n'; //something has gone wrong!
		throw std::exception();
	}

	//Go through the file, line by line, copying it into a string 
	std::string vertSrc;
	std::streampos current = file.tellg();
	std::streampos end = -1;
	for (int i = 0; current != end; i++) //keep going until we reach the end
	{
		std::string line;
		std::getline(file, line);
		vertSrc += line + "\n";
		current = file.tellg();
	}

	file.close(); //we need to close the file before we open another one
	file.open(frag); //open the fragshader and copy that into another string
	std::string fragSrc;

	if (!file.is_open())
	{
		std::cout << "Could not open frag file!" << '\n'; //something has gone wrong!
		throw std::exception();
	}
	current = file.tellg();
	end = -1;
	for (int i = 0; current != end; i++) //keep going until we reach the end
	{
		std::string line;
		std::getline(file, line);
		fragSrc += line + "\n";
		current = file.tellg();
	}
	file.close();
	//now we have the shaders in strings, we can use the PGG code to get it working

	const GLchar *vs = vertSrc.c_str();
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vs, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	const GLchar *fs = fragSrc.c_str();
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fs, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShaderId);
	glAttachShader(m_id, fragmentShaderId);
	glBindAttribLocation(m_id, 0, "in_Position");
	glBindAttribLocation(m_id, 1, "in_Color");

	if (glGetError() != GL_NO_ERROR)
	{
		throw std::exception();
	}

	glLinkProgram(m_id);
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	glDetachShader(m_id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(m_id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

void ShaderProgram::SetUniform(std::string uniform, glm::vec4 value)
{
	GLint uniformId = glGetUniformLocation(m_id, uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(m_id);
	glUniform4f(uniformId, value.x, value.y, value.z, value.w);
	glUseProgram(0);
}

void ShaderProgram::SetUniform(std::string uniform, float value)
{
	GLint uniformId = glGetUniformLocation(m_id, uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(m_id);
	glUniform1f(uniformId, value);
	glUseProgram(0);
}

void ShaderProgram::SetUniform(std::string uniform, glm::mat4 value)
{
	if (m_id)
	{
		GLint uniformId = glGetUniformLocation(m_id, uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_id);
		glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(value));
		glUseProgram(0);
	}
}

unsigned int ShaderProgram::LoadTexture(std::string filename)
{
	// Load SDL surface
	SDL_Surface *image = SDL_LoadBMP(filename.c_str());

	if (!image) // Check it worked
	{
		std::cerr << "WARNING: could not load BMP image: " << filename << std::endl;
		return 0;
	}

	// Create OpenGL texture
	unsigned int texName = 0;
	glGenTextures(1, &texName);


	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// By default, OpenGL mag filter is linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// By default, OpenGL min filter will use mipmaps
	// We therefore either need to tell it to use linear or generate a mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// SDL loads images in BGR order
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);

	//glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(image);

	//glBindTexture(GL_TEXTURE_2D, 0);


	return texName;
}

void ShaderProgram::Draw(std::shared_ptr<Mesh> _mesh)
{
	glUseProgram(m_id);
//	glBindVertexArray(_mesh->GetVAO());

//	glDrawArrays(GL_TRIANGLES, 0, _mesh->GetVertices());

	glBindVertexArray(0);
	glUseProgram(0);
}

void ShaderProgram::Apply()
{
	glUseProgram(m_id);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(m_id, "tex1"), 0);
	glBindTexture(GL_TEXTURE_2D, _texture1);

	glActiveTexture(GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(m_id, "normalMap"), 1);
	glBindTexture(GL_TEXTURE_2D, _normalTexture);

	glActiveTexture(GL_TEXTURE2);
	glUniform1i(glGetUniformLocation(m_id, "heightMap"), 2);
	glBindTexture(GL_TEXTURE_2D, _heightTexture);
}
