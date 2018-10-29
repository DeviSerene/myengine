#include "Gui.h"
#include "Core.h"
#include "VertexBuffer.h"

Gui::Gui()
{
}

void Gui::Init(std::shared_ptr<Core> _c)
{
	m_core = _c;
	LoadShaders("guiVert.txt", "guiFrag.txt");

	std::shared_ptr<VertexBuffer> positions = std::make_shared<VertexBuffer>();
	positions->Add(glm::vec3(0.0f, 0.0f, 0.0f));
	positions->Add(glm::vec3(1.0f, 1.0f, 0.0f));
	positions->Add(glm::vec3(0.0f, 1.0f, 0.0f));

	positions->Add(glm::vec3(1.0f, 1.0f, 0.0f));
	positions->Add(glm::vec3(0.0f, 0.0f, 0.0f));
	positions->Add(glm::vec3(1.0f, 0.0f, 0.0f));

	red = std::make_shared<VertexBuffer>();
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	red->Add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	
	green = std::make_shared<VertexBuffer>();
	green->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	green->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	green->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	green->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	green->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	green->Add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	blue = std::make_shared<VertexBuffer>();
	blue->Add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	blue->Add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	blue->Add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	blue->Add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	blue->Add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	blue->Add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));


	m_shape = std::make_shared<VertexArray>();
	m_shape->SetBuffer(IN_POSITION, positions);
	m_shape->SetBuffer(IN_COLOUR, red);
}

Gui::~Gui()
{

}

bool Gui::Button(glm::vec4 _pos, std::string _label)
{
	
	glm::vec4 screenPos;
	screenPos.x = (1+_pos.x) * (m_core.lock()->GetScreenSize().x /2);
	if (_pos.y > 0)
	{
		(_pos.y) * (m_core.lock()->GetScreenSize().y / 2);
	}
	else
	{
		screenPos.y = ((1+_pos.y) * (m_core.lock()->GetScreenSize().y / 2)) + (m_core.lock()->GetScreenSize().y / 2);
	}
	screenPos.z = screenPos.x + ((_pos.z / 2) * m_core.lock()->GetScreenSize().x);
	screenPos.w = screenPos.y +((_pos.w / 2) * m_core.lock()->GetScreenSize().y);
	//screenPos.y = screenPos.y - (screenPos.w/2);
	//screenPos.w = screenPos.y + (screenPos.w / 2);
	

	if (Intersect(screenPos, m_core.lock()->GetMouseLocation()))
	{
		if (m_core.lock()->IsMouseDown())
		{
			m_shape->SetBuffer(IN_COLOUR, green);

		}
		else
		{
			m_shape->SetBuffer(IN_COLOUR, blue);

		}
	}
	else
	{
		m_shape->SetBuffer(IN_COLOUR, red);
	}
	glUseProgram(_shaderProgram);
	//Update the projection matrix
	SetUniform(_shaderProjMatLocation, m_core.lock()->GetPM());
	//update the model matrix;
	glm::mat4 modelmat = glm::mat4(1.0f);
	modelmat = glm::translate(modelmat, glm::vec3(_pos.x, _pos.y, 0));
	modelmat = glm::scale(modelmat, glm::vec3(_pos.z, _pos.w, 1));
	SetUniform(_shaderModelMatLocation, modelmat);
	glBindVertexArray(m_shape->GetId());

	// Tell OpenGL to draw it
	// Must specify the type of geometry to draw and the number of vertices
	glDrawArrays(GL_TRIANGLES, 0, m_shape->GetVertexCount());

	// Unbind VAO
	glBindVertexArray(0);
	///

	if (Intersect(screenPos, m_core.lock()->GetMouseLocation()))
	{
		if (m_core.lock()->IsMouseDown())
		{
			return true;
		}
	}

	return false;
}

bool Gui::Intersect(glm::vec4 _pos, glm::vec2 _mouse)
{
	if (_mouse.x > _pos.x && _mouse.x < _pos.z && _mouse.y > _pos.y && _mouse.y < _pos.w)
	{
		return true;
	}
	return false;
}
























///////
bool Gui::LoadShaders(std::string vertFilename, std::string fragFilename)
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
	// This links the shader to the program
	glAttachShader(_shaderProgram, vShader);

	// Same for the fragment shader
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderText, NULL);
	// Delete buffer
	delete[] fShaderText;
	glCompileShader(fShader);
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
	_shaderModelMatLocation = glGetUniformLocation(_shaderProgram, "in_Model");
	_shaderProjMatLocation = glGetUniformLocation(_shaderProgram, "in_Projection");

	return true;
}

void Gui::SetUniform(int _location, glm::mat4 _set)
{
	glUniformMatrix4fv(_location, 1, GL_FALSE, glm::value_ptr(_set));
}