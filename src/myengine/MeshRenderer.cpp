#include "MeshRenderer.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "Mesh.h"
#include "Environment.h"
#include "Keyboard.h"
#include "Core.h"
#include "Resources.h"
#include "Entity.h"
#include "Transform.h"


void MeshRenderer::OnInit()
{
	m_modelMatrix = glm::mat4(1.0f);
	m_invModelMatrix = glm::mat4(1.0f);

	m_cam = std::shared_ptr<glm::vec3>(new glm::vec3(0.0f, 0.0f, 0.0f));

	m_mesh = GetCore()->GetResources()->Load<Mesh>("Card.obj");
	m_texture = GetCore()->GetResources()->Load<Texture>("Card.bmp");
	m_normal = GetCore()->GetResources()->Load<Texture>("Card_normal.bmp");
	m_height = GetCore()->GetResources()->Load<Texture>("Card_height.bmp");
	m_mat = GetCore()->GetResources()->Create<Material>();
	m_mat->LoadShaders("VertShader.txt", "FragShader.txt");
	m_mat->SetMatrices(m_modelMatrix, m_invModelMatrix, glm::mat4(1.0f), glm::mat4(1.0f));
	m_mat->SetLightPosition({ 1.0f, 0.0f, 0.0f });
}

void MeshRenderer::OnDisplay()
{
	std::shared_ptr<Transform> myTransform = GetEntity()->GetComponent<Transform>();
	if (myTransform)
	{
		std::shared_ptr<Entity> ent = GetEntity();

		m_modelMatrix = glm::scale(glm::mat4(1.0f), myTransform->GetScale());
		m_modelMatrix = glm::rotate(m_modelMatrix, myTransform->GetRotation().y, glm::vec3(0, 1, 0));
		m_modelMatrix = glm::rotate(m_modelMatrix, myTransform->GetRotation().z, glm::vec3(0, 0, 1));
		m_modelMatrix = glm::rotate(m_modelMatrix, myTransform->GetRotation().x, glm::vec3(1, 0, 0));
		m_modelMatrix = glm::translate(m_modelMatrix, myTransform->GetPosition());

		if (ent->m_parent != nullptr)
		{
			m_modelMatrix = ent->m_parent->GetComponent<MeshRenderer>()->GetModelMatrix() * m_modelMatrix;

		}

		
		m_invModelMatrix = glm::rotate(glm::mat4(1.0f), -0.0f, glm::vec3(0, 1, 0));
		
		//needs a transform to proceed
		m_mat->SetMatrices(m_modelMatrix, m_invModelMatrix, GetCore()->GetVM(), GetCore()->GetPM());
		m_mat->SetCameraPosition(&GetCore()->GetCamera());
		// This activates the shader
		m_mat->SetTex(0, m_texture->GetTexture());
		m_mat->SetTex(1, m_normal->GetTexture());
		m_mat->SetTex(2, m_height->GetTexture());
		m_mat->Apply();
		m_mesh->Draw();
	}
	else
	{
		m_mat->Apply();
		m_mesh->Draw();
	}
	

}
