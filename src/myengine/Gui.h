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
	void SetTexture(std::shared_ptr<Texture> _texture) { texture = _texture; }
	void SetHighlight(std::shared_ptr<Texture> _texture) { highlight = _texture; }
	void SetPressed(std::shared_ptr<Texture> _texture) { pressed = _texture; }

	glm::vec4 GetPos(glm::vec4 _pos);

private:

	bool Intersect(glm::vec4 _pos, glm::vec2 _mouse);

	std::weak_ptr<Core> m_core;

	std::shared_ptr<VertexArray> m_shape;
	std::shared_ptr<VertexBuffer> red;
	std::shared_ptr<VertexBuffer> blue;
	std::shared_ptr<VertexBuffer> green;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Texture> highlight;
	std::shared_ptr<Texture> pressed;


	std::shared_ptr<Shader> m_shader;

};
