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
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"

class Core;

/*!
This handles the gui
*/
class Gui
{
public:
	Gui();
	~Gui();

	void Init(std::shared_ptr<Core> _c);
	bool Button(glm::vec4 _pos, std::string _label);
	void Sprite(glm::vec4 _pos);
	void SetTexture(GLuint _texture) { texture = _texture; }
	void SetHighlight(GLuint _texture) { highlight = _texture; }
	void SetPressed(GLuint _texture) { pressed = _texture; }
	void SetFrameInfo(glm::vec4 _frameInfo) { m_frameInfo = _frameInfo; }

	glm::vec4 GetPos(glm::vec4 _pos);

private:

	bool Intersect(glm::vec4 _pos, glm::vec2 _mouse);

	std::weak_ptr<Core> m_core;

	std::shared_ptr<VertexArray> m_shape;
	std::shared_ptr<VertexBuffer> red;
	std::shared_ptr<VertexBuffer> blue;
	std::shared_ptr<VertexBuffer> green;
	GLuint texture;
	GLuint highlight;
	GLuint pressed;
	glm::vec4 m_frameInfo;

	std::shared_ptr<Shader> m_shader;

};
