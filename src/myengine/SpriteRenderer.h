#pragma once
#include "Component.h" //inherits from component (as it is something that can be slot into an entity)
#include <memory>
#include <iostream>
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <GLM/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

/*!
SpriteRenderer is a Component that can be added to GameObjects (Entities).
SpriteRenderer has a simple square which is then applied a 2D texture. This allows sprites to be set in 2D space, however they will need to be rotated to face the camera to be seen.
*/

class SpriteRenderer : public Component
{
public:
	void OnInit(); //this will override the Components
	void OnDisplay();

private:

	// The actual model geometry
	std::shared_ptr<VertexArray> m_shape;
	// Shader applied and the texture
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Texture> m_texture;

	// Matrix for the position and orientation of the game object
	glm::mat4 m_modelMatrix;
	glm::mat4 m_invModelMatrix;


};
