#pragma once
#include "Component.h" //inherits from component (as it is something that can be slot into an entity)
#include <memory>
#include <iostream>
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <GLM/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Texture.h"

class MeshRenderer : public Component
{
public:
	void OnInit(); //this will override the Components
	void OnDisplay();

private:

	// The actual model geometry
	std::shared_ptr<VertexArray> m_shape;
	// The material contains the shader
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Texture> m_texture;
	//std::shared_ptr <ShaderProgram> m_shader1;
	// Matrix for the position and orientation of the game object
	glm::mat4 m_modelMatrix;
	glm::mat4 m_invModelMatrix;

	//	std::shared_ptr<ShaderProgram> m_shader;

};
