#include "SpriteRenderer.h"
#include "Environment.h"
#include "Keyboard.h"
#include "Core.h"
#include "Resources.h"
#include "Entity.h"
#include "Transform.h"


void SpriteRenderer::OnInit()
{

	m_modelMatrix = glm::mat4(1.0f);
	m_invModelMatrix = glm::mat4(1.0f);
	m_shape = GetCore()->GetResources()->Load<VertexArray>("Square");

	m_texture = GetCore()->GetResources()->Load<Texture>("ability_0.png");
	m_shader = GetCore()->GetResources()->Load<Shader>("SpriteShader");
	m_shader->LoadShaders("SpriteVert.txt", "SpriteFrag.txt");
	m_shader->AddUniform("in_Model");
	m_shader->AddUniform("in_Projection");
	m_shader->AddUniform("in_View");
	m_shader->AddUniform("in_invModel");
	m_shader->AddUniform("in_Texture");
}

void SpriteRenderer::OnDisplay()
{
	std::shared_ptr<Transform> myTransform = GetEntity()->GetComponent<Transform>();
	if (myTransform)
	{

		glUseProgram(m_shader->GetShader());
		m_modelMatrix = glm::rotate(m_modelMatrix, myTransform->GetRotation().y, glm::vec3(0, 1, 0));
		m_modelMatrix = glm::rotate(m_modelMatrix, myTransform->GetRotation().z, glm::vec3(0, 0, 1));
		m_modelMatrix = glm::rotate(m_modelMatrix, myTransform->GetRotation().x, glm::vec3(1, 0, 0));
		m_modelMatrix = glm::scale(m_modelMatrix, myTransform->GetScale());
		m_modelMatrix = glm::translate(glm::mat4(1.0f), myTransform->GetPosition());

		m_invModelMatrix = glm::rotate(glm::mat4(1.0f), -0.0f, glm::vec3(0, 1, 0));

		//Set the uniforms
		m_shader->SetUniform(m_shader->GetUniformLocation("in_Proj"), GetCore()->GetPM());
		m_shader->SetUniform(m_shader->GetUniformLocation("in_View"), GetCore()->GetVM());
		m_shader->SetUniform(m_shader->GetUniformLocation("in_Model"), m_modelMatrix);
		m_shader->SetUniform(m_shader->GetUniformLocation("in_invModel"), m_invModelMatrix);
		// Apply the texture
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(m_shader->GetUniformLocation("in_Texture"), 0);
		glBindTexture(GL_TEXTURE_2D, m_texture->GetTexture());

		glBindVertexArray(m_shape->GetId());

		// Tell OpenGL to draw it
		// Must specify the type of geometry to draw and the number of vertices
		glDrawArrays(GL_TRIANGLES, 0, m_shape->GetVertexCount());

		// Unbind VAO
		glBindVertexArray(0);
		///

	}
	else
	{

	}


}
